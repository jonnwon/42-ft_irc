#ifndef SERVER_HPP
#define SERVER_HPP

#include <iostream>
#include <map>
#include <vector>
#include <sys/socket.h>
#include <netinet/in.h>
#include <poll.h>
#include <unistd.h>
#include <fcntl.h>
#include <cstring>
#include <exception>
#include <ctime>
#include <sstream>
#include <fstream>
#include <cstdlib>
#include <cstdio>
#include <cerrno>

#include "Message.hpp"
#include "Client.hpp"
#include "Channel.hpp"
#include "Util.hpp"
#include "print.hpp"

#define BUFFER_SIZE 2
#define WELCOME_FILE_PATH "welcome/what_is_man"

enum e_Bot
{
    HELP,
    LIBFT,
    PIPEX,
    MINISHELL,
    CUB3D,
    INCEPTION,
    B_ERROR,
};

enum e_cmd
{
    C_CAP = 0,
    C_PASS,
    C_NICK,
    C_USER,
    C_JOIN,
    C_PING,
    C_PART,
    C_PRIVMSG,
    C_QUIT,
    C_MODE,
    C_TOPIC,
    C_KICK,
    C_INVITE,
    C_ERROR,
};


class Server
{
private:
    int _serverFd;
    int _portNumber;
    std::string _password;
    std::string _buffer;
    std::vector<pollfd> pollFds;
    std::map<int, Client> _clientBook;
    std::vector<Message> _messages;
    std::map<std::string, Channel> _channelBook;

    Server();
    Server(const Server &other);
    Server &operator=(const Server &other);

public:
    Server(const int portNumber, const std::string &password);
    ~Server();

    /** getter **/
    std::string &getPassWord() { return _password; }
    int getPortNumber() { return _portNumber; }
    std::vector<Message> &getMessages() { return _messages; }
    Client *getClient(const std::string nick_name)
    {
        for (std::map<int, Client>::iterator it = _clientBook.begin(); it != _clientBook.end(); ++it)
        {
            if ((*it).second.getNick() == nick_name)
                return &(*it).second;
        }
        return NULL;
    }

    /*** Server.cpp ***/
    void runServer();
    void makeClient();
    void serverLoop();
    bool isClient(const std::string &nick_name);
    Channel &getChannel(const std::string &channelName);
    bool isChannel(const std::string &channelName);
    void addChannel(std::string &channelName);
    void eraseChannel(const std::string &channel_name);

    /*** Server_Util.cpp ***/
    void sendMessage(int fd, std::string message);
    void receiveData(int fd);
    void clearBuffer(char *_buffer);
    void makeMessages(int fd, std::string buffer);
    void makeMessages(std::string &buffer);
    void exeCommand(int _from_fd);

    /** Server_Cmd.cpp **/
    void sendQuitMessage(Client &executor, const std::string &buffer_to_channel);
    void quitClient(Client &client);
};

e_cmd getTargetCmd(const std::string &cmd);

namespace Command
{
    void CAP(Server &server, Client &executor);
    void PASS(Server &server, Client &executor, Message &message);
    void NICK(Server &server, Client &executor, Message &message);
    void USER(Server &server, Client &executor, Message &message);
    void JOIN(Server &server, Client &executor, Message &message);
    void PING(Server &server, Client &executor, Message &message);
    void PART(Server &server, Client &executor, Message &message);
    void PRIVMSG(Server &server, Client &executor, Message &message);
    void QUIT(int client_fd, Server &server, Client &executor, Message &message);
    void MODE(Server &server, Client &executor, Message &message);
    void TOPIC(Server &server, Client &executor, Message &message);
    void KICK(Server &server, Client &executor, Message &message);
    void INVITE(Server &server, Client &executor, Message &message);

    void execMODE_pI(Channel &channel, Client &executor, std::string &buffer);
    void execMODE_mI(Channel &channel, Client &executor, std::string &buffer);
    void execMODE_pT(Channel &channel, Client &executor, std::string &buffer);
    void execMODE_mT(Channel &channel, Client &executor, std::string &buffer);
    void execMODE_pK(Channel &channel, Client &executor, std::string &buffer, Message &message);
    void execMODE_mK(Channel &channel, Client &executor, std::string &buffer, Message &message);
    void execMODE_pO(Channel &channel, Client &executor, std::string &buffer, Message &message);
    void execMODE_mO(Channel &channel, Client &executor, std::string &buffer, Message &message);
    void execMODE_pL(Channel &channel, Client &executor, std::string &buffer, Message &message);
    void execMODE_mL(Channel &channel, Client &executor, std::string &buffer, Message &message);
}

#endif
