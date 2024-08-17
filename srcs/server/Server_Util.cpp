#include "Server.hpp"

void Server::sendMessage(int fd, std::string message)
{
    ssize_t byteSent = send(fd, message.c_str(), message.size(), 0);
    if (byteSent == -1)
    {
        perror("send");
        exit(1);
    }
    std::cout << "[" << _portNumber << "]SERVER ︻デ┳═ー[" << fd << "]CLIENT⏭ " << message << std::endl;
}
 
void Server::clearBuffer(char *buffer)
{
    for (int i = 0; i < BUFFER_SIZE; i++)
        buffer[i] = '\0';
}

void Server::receiveData(int fd)
{
    if (fcntl(fd, F_SETFL, O_NONBLOCK) == -1)
        throw std::logic_error("fcntl");

    char buffer[BUFFER_SIZE];
    clearBuffer(buffer);

    Client &client = _clientBook[fd];
    ssize_t bytes;

    while ((bytes = recv(fd, buffer, BUFFER_SIZE - 1, 0)))
    {
        if (bytes < 0)
            break;
        else
            client.setInBuffer(buffer);
        clearBuffer(buffer);
    }
    if (bytes == 0)
        throw std::logic_error("Client disconnected");
    std::cout << "Received: " << client.getInBuffer() << std::endl;
}

void Server::makeMessages(int fd, std::string buffer)
{
    std::vector<std::string> lines;

    Parsing::splitByCRLF(buffer, lines);

    for (std::vector<Message>::size_type i = 0; i < lines.size(); i++)
    {
        Message msg(fd, lines[i]);
        _messages.push_back(msg);
    }
}

void Server::makeMessages(std::string &client_in_buffer)
{
    std::vector<std::string> lines;

    Parsing::splitByCRLF(client_in_buffer, lines);

    for (std::vector<std::string>::size_type i = 0; i < lines.size(); i++)
    {
        Message msg(lines[i]);
        _messages.push_back(msg);
    }
}

e_cmd getTargetCmd(const std::string &cmd)
{
    if (cmd == "CAP")
        return C_CAP;
    if (cmd == "PASS")
        return C_PASS;
    if (cmd == "NICK")
        return C_NICK;
    if (cmd == "USER")
        return C_USER;
    if (cmd == "JOIN")
        return C_JOIN;
    if (cmd == "PING")
        return C_PING;
    if (cmd == "PART")
        return C_PART;
    if (cmd == "PRIVMSG")
        return C_PRIVMSG;
    if (cmd == "QUIT")
        return C_QUIT;
    if (cmd == "MODE")
        return C_MODE;
    if (cmd == "TOPIC")
        return C_TOPIC;
    if (cmd == "KICK")
        return C_KICK;
    if (cmd == "INVITE")
        return C_INVITE;
    return C_ERROR;
}

void Server::exeCommand(int _from_fd)
{
    Client &executor = _clientBook[_from_fd];

    for (size_t i = 0; i < _messages.size(); i++)
    {
        if ((_messages[i].getParams().size() >= 1 && _messages[i].getParam(0) == "#bot") || \
            (_messages[i].getParams().size() >= 2 && _messages[i].getParam(1) == "#bot"))
        {
            switch (getTargetCmd(_messages[i].getCmd()))
            {
            case C_JOIN:
                Command::JOIN(*this, executor, _messages[i]);
                break;
            case C_PART:
                Command::PART(*this, executor, _messages[i]);
                break;
            case C_PRIVMSG:
                Command::PRIVMSG(*this, executor, _messages[i]);
                break;
            default:
                executor.setOutBuffer(RPL::ERR_421(executor, _messages[i]));
                break;
            }
            continue;
        }
        switch (getTargetCmd(_messages[i].getCmd()))
        {
        case C_CAP:
            Command::CAP(*this, executor);
            break;
        case C_PASS:
            Command::PASS(*this, executor, _messages[i]);
            break;
        case C_NICK:
            Command::NICK(*this, executor, _messages[i]);
            break;
        case C_USER:
            Command::USER(*this, executor, _messages[i]);
            break;
        case C_JOIN:
            Command::JOIN(*this, executor, _messages[i]);
            break;
        case C_PING:
            Command::PING(*this, executor, _messages[i]);
            break;
        case C_PART:
            Command::PART(*this, executor, _messages[i]);
            break;
        case C_PRIVMSG:
            Command::PRIVMSG(*this, executor, _messages[i]);
            break;
        case C_QUIT:
            Command::QUIT(_from_fd, *this, executor, _messages[i]);
            throw(std::logic_error("Client execute quit command"));
            break;
        case C_MODE:
            Command::MODE(*this, executor, _messages[i]);
            break;
        case C_TOPIC:
            Command::TOPIC(*this, executor, _messages[i]);
            break;
        case C_KICK:
            Command::KICK(*this, executor, _messages[i]);
            break;
        case C_INVITE:
            Command::INVITE(*this, executor, _messages[i]);
            break;
        default:
            executor.setOutBuffer(RPL::ERR_421(executor, _messages[i]));
            break;
        }
    }    
}

void Server::sendQuitMessage(Client &executor, const std::string &buffer_to_channel)
{
    std::vector<std::string> send_list;
    send_list.push_back(executor.getNick());
    for (std::map<std::string, Channel>::iterator it = _channelBook.begin(); it != _channelBook.end(); ++it)
    {
        Channel &channel = (*it).second;
        if (channel.isClient(executor.getNick()))
        {
            std::map<std::string, std::pair<Client *, e_auth> > &_client_list = channel.getClientList();
            for (std::map<std::string, std::pair<Client *, e_auth> >::iterator it = _client_list.begin(); it != _client_list.end(); ++it)
            {
                const std::string &nick_name = (*it).first;
                if (std::find(send_list.begin(), send_list.end(), nick_name) == send_list.end())
                {
                    Client *client = getClient(nick_name);
                    if (channel.getName() != "#bot")
                        client->setOutBuffer(buffer_to_channel);
                    send_list.push_back(nick_name);
                }
            }
        }
    }
}

void Server::quitClient(Client &client)
{
    std::vector<std::string> erase_list;
    for (std::map<std::string, Channel>::iterator it = _channelBook.begin(); it != _channelBook.end(); ++it)
    {
        Channel &channel = (*it).second;
        channel.exitChannel(client);
        if (channel.getClientNum() == 0)
            erase_list.push_back(channel.getName());
    }

    for (std::vector<std::string>::iterator it = erase_list.begin(); it != erase_list.end(); ++it)
        eraseChannel((*it));

    for (std::map<int, Client>::iterator it = _clientBook.begin(); it != _clientBook.end(); ++it)
    {
        if ((*it).second.getNick() == client.getNick())
        {
            _clientBook.erase(it);
            return;
        }
    }
}

