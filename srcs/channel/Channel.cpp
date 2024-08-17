#include "Channel.hpp"

Channel::Channel() : _name(""), _topic(""), _password(""), _mode(0), _maxClient(0) { }

Channel::Channel(const std::string &name) : _name(name), _topic(""), _password(""), _mode(0), _maxClient(0) { }

Channel::Channel(const Channel &other) : _name(other._name), _topic(other._topic), _password(other._password), _mode(other._mode), _maxClient(other._maxClient) { }

Channel::~Channel() { }

/** getter **/
std::map<std::string, std::pair<Client *, e_auth> >& Channel::getClientList() { return _client_list; }
int Channel::getClientNum() { return static_cast<int>(_client_list.size()); }
std::vector<std::string>& Channel::getInvitedList() { return _invited_list; }
const std::string& Channel::getName() const { return _name; }
const std::string& Channel::getTopic() const { return _topic; }
const std::string& Channel::getPassword() const { return _password; }
char Channel::getMode() const { return _mode; }
int Channel::getMaxClient() { return _maxClient; }

e_auth Channel::getAuthority(const std::string &nick_name)
{
    e_auth status = ERROR;
    if (_client_list.find(nick_name) != _client_list.end())
    {
        status = (*_client_list.find(nick_name)).second.second;
    }
    return status;
}

std::string Channel::getClientListStr()
{
    std::string buffer = "";
    for (std::map<std::string, std::pair<Client *, e_auth> >::iterator it = _client_list.begin(); it != _client_list.end(); ++it)
    {
        if (it->second.second == OPERATOR)
            buffer += '@';
        buffer += it->first;
        if (it != --_client_list.end())
            buffer += ' ';
    }
    return buffer;
}


/** setter **/
void Channel::setMaxClient(const std::string &number) { _maxClient = atoi(number.c_str()); }
void Channel::setMode(e_Mode mode) { _mode += mode; }
void Channel::unsetMode(e_Mode mode) { _mode -= mode; }
bool Channel::checkMode(e_Mode mode) { return _mode & mode; }
void Channel::setPassword(const std::string &password) { _password = password; }
void Channel::unsetPassword() { _password = ""; }
void Channel::setTopic(std::string &topic) { _topic = topic; }

void Channel::setInvitedList(const std::string &nick_name)
{
    if (std::find(_invited_list.begin(), _invited_list.end(), nick_name) == _invited_list.end())
        _invited_list.push_back(nick_name);
}

void Channel::unsetInvitedList(const std::string &nick_name)
{
    _invited_list.erase(std::find(_invited_list.begin(), _invited_list.end(), nick_name));
}

/** Channel util **/

void Channel::setOperator(const std::string &nick_name)
{
    for (std::map<std::string, std::pair<Client *, e_auth> >::iterator it = _client_list.begin(); it != _client_list.end(); ++it)
    {
        if ((*it).second.first->getNick() == nick_name && (*it).second.second != OPERATOR)
        {
            (*it).second.second = OPERATOR;
            return;
        }
    }
}

void Channel::unsetOperator(const std::string &nick_name)
{
    for (std::map<std::string, std::pair<Client *, e_auth> >::iterator it = _client_list.begin(); it != _client_list.end(); ++it)
    {
        if ((*it).second.first->getNick() == nick_name && (*it).second.second == OPERATOR)
        {
            (*it).second.second = REGULAR;
            return;
        }
    }
}

void Channel::joinChannel(Client &client, e_auth lev)
{
    _client_list.insert(std::make_pair(client.getNick(), std::make_pair(&client, lev)));
}

void Channel::exitChannel(Client &client)
{
    std::map<std::string, std::pair<Client *, e_auth> >::iterator it = _client_list.find(client.getNick());
    std::cout << client.getNick() << " is exited from channel : " << _name << std::endl;
    if (it != _client_list.end())
        _client_list.erase(it);
}

bool Channel::isClient(const std::string &nick_name)
{
    if (_client_list.find(nick_name) != _client_list.end())
        return true;
    return false;
}

void Channel::toAllSetOutBuffer(std::string &buffer, const std::string &my_nick)
{
    for (std::map<std::string, std::pair<Client *, e_auth> >::iterator it = _client_list.begin(); it != _client_list.end(); ++it)
    {
        Client *client = (*it).second.first;
        if (client->getNick() == my_nick)
            continue;
        client->setOutBuffer(buffer);
        std::cout << "Set Out Buffer Client : " << client->getNick() << '\n';
    }
}
