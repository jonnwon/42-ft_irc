#ifndef CHANNEL_HPP
#define CHANNEL_HPP

#include <iostream>
#include <vector>
#include <map>
#include <algorithm>

#include "Client.hpp"

enum e_auth
{
    OPERATOR = 0,
    REGULAR,
    ERROR,
};

enum e_Mode
{
    MODE_I = 1,
    MODE_T = 2,
    MODE_K = 4,
    MODE_O = 8,
    MODE_L = 16,
};

class Channel
{
private:
    std::map<std::string, std::pair<Client *, e_auth> > _client_list;
    std::vector<std::string> _invited_list;
    std::string _name, _topic, _password;
    char _mode;
    int _maxClient;

    Channel &operator=(const Channel &other);
public:
    Channel();
    Channel(const std::string &name);
    Channel(const Channel &other);
    ~Channel();

    /** getter **/
    std::map<std::string, std::pair<Client *, e_auth> > &getClientList();
    int getClientNum();
    std::vector<std::string> &getInvitedList();
    const std::string &getName() const;
    const std::string &getTopic() const;
    const std::string &getPassword() const;
    char getMode() const;
    int getMaxClient();
    e_auth getAuthority(const std::string &nick_name);
    std::string getClientListStr();

    /** setter **/
    void setMaxClient(const std::string &number);
    void setMode(e_Mode mode);
    void unsetMode(e_Mode mode);
    bool checkMode(e_Mode mode);
    void setPassword(const std::string &password);
    void unsetPassword();
    void setInvitedList(const std::string &nick_name);
    void unsetInvitedList(const std::string &nick_name);
    void setTopic(std::string &topic);


    /** Channel util **/
    void setOperator(const std::string &nick_name);
    void unsetOperator(const std::string &nick_name);
    void joinChannel(Client &client, e_auth lev);
    void exitChannel(Client &client);
    bool isClient(const std::string &nick_name);
    void toAllSetOutBuffer(std::string &buffer, const std::string &my_nick);
};

#endif
