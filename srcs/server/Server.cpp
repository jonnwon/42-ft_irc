#include "Server.hpp"

Server::Server(const int portNumber, const std::string &password) : _portNumber(portNumber), _password(password) {}
Server::~Server() {}

void Server::runServer()
{
    _serverFd = socket(AF_INET, SOCK_STREAM, 0);
    if (_serverFd == -1)
        throw(std::logic_error("serverFd"));

    struct sockaddr_in server_addr;

    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    server_addr.sin_port = htons(_portNumber);

    int option = 1;
    setsockopt(_serverFd, SOL_SOCKET, SO_REUSEADDR, &option, sizeof(option));

    if (bind(_serverFd, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1)
        throw(std::logic_error("bind"));
    if (listen(_serverFd, 5) == -1)
        throw(std::logic_error("listen"));
}

void Server::makeClient()
{
    struct sockaddr_in client_addr;

    socklen_t addr_len = sizeof(client_addr);
    int new_socket = accept(_serverFd, (struct sockaddr *)&client_addr, &addr_len);
    if (new_socket == -1)
        throw(std::logic_error("accept"));
    struct pollfd poll_client;
    poll_client.fd = new_socket;
    poll_client.events = POLLIN | POLLOUT;
    pollFds.push_back(poll_client);

    Client newClient;
    _clientBook.insert(std::pair<int, Client>(new_socket, newClient));
}

void welcomeMessage(Client &client)
{
    client.setOutBuffer(RPL::WELCOME::STR0(client));
    client.setOutBuffer(RPL::WELCOME::STR1(client));
    client.setOutBuffer(RPL::WELCOME::STR2(client));
    client.setOutBuffer(RPL::WELCOME::STR3(client));
    client.setOutBuffer(RPL::WELCOME::STR4(client));
    client.setOutBuffer(RPL::WELCOME::STR5(client));
    client.setOutBuffer(RPL::WELCOME::STR5_1(client));
    client.setOutBuffer(RPL::WELCOME::STR5_2(client));
    client.setOutBuffer(RPL::WELCOME::STR6(client));
}

void Server::serverLoop()
{
    struct pollfd poll_serv;

    poll_serv.fd = _serverFd;
    poll_serv.events = POLLIN;
    pollFds.push_back(poll_serv);

    while (1)
    {
        if (poll(pollFds.data(), pollFds.size(), -1) == -1)
            throw(std::logic_error(strerror(errno)));
        if (pollFds[0].revents & POLLIN)
            makeClient();
        for (size_t i = 1; i < pollFds.size(); ++i)
        {
            Client &client = _clientBook[pollFds[i].fd];
            if (pollFds[i].revents & POLLIN)
            {
                std::cout << "[fd:" <<pollFds[i].fd << "/nick:" << client.getNick() << "] ";
                try
                {
                    receiveData(pollFds[i].fd);
                }
                catch(const std::exception& e)
                {
                    const std::string buffer = RPL::QUIT::DIS_CONNECTION(client);
                    sendQuitMessage(client, buffer);
                    std::cerr << e.what() << '\n';
                    quitClient(client);
                    close(pollFds[i].fd);
                    pollFds.erase(pollFds.begin() + i);
                    continue ;
                }
                makeMessages(client.getInBuffer());
                try
                {
                    exeCommand(pollFds[i].fd);
                    _messages.clear();
                }
                catch (const std::exception &e)
                {
                    std::cerr << e.what() << std::endl;
                    quitClient(client);
                    close(pollFds[i].fd);
                    pollFds.erase(pollFds.begin() + i);

                    _messages.clear();
                    continue;
                }
                if (!client.getIsRegister())
                {
                    if (client.checkInfoSet())
                    {
                        welcomeMessage(client);
                        client.setIsRegister(true);
                    }
                }
            }
            else if (pollFds[i].revents & POLLOUT)
            {
                if (client.getOutBuffer() != "")
                {
                    sendMessage(pollFds[i].fd, client.getOutBuffer());
                    client.clearOutBuffer();
                }
            }
        }
    }
}

/* Channel */
Channel &Server::getChannel(const std::string &channelName)
{
    return _channelBook[channelName];
}

bool Server::isChannel(const std::string &channelName)
{
    if (!_channelBook.empty() && _channelBook.find(channelName) != _channelBook.end())
        return true;
    return false;
}
void Server::addChannel(std::string &channelName)
{
    _channelBook.insert(std::pair<std::string, Channel>(channelName, Channel(channelName)));
}

void Server::eraseChannel(const std::string &channel_name)
{
	std::cout << "Erase channel name: " << channel_name << std::endl;
    _channelBook.erase(_channelBook.find(channel_name));
}

bool Server::isClient(const std::string &nick_name)
{
    for (std::map<int, Client>::iterator it = _clientBook.begin(); it != _clientBook.end(); ++it)
    {
        if ((*it).second.getNick() == nick_name)
            return true;
    }
    return false;
}
