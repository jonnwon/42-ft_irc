#include "Client.hpp"

Client::Client() : _nickName(""), _userName(""), _serverName(""), _out_buffer(""), _in_buffer(""), _check_passWord(false), _is_register(false) { }

Client::Client(const Client &other) : _nickName(other._nickName), _userName(other._userName), _serverName(other._serverName), _out_buffer(other._out_buffer), _in_buffer(other._in_buffer), _check_passWord(other._check_passWord), _is_register(other._is_register) { }

Client::~Client() { }

/** getter **/
const std::string& Client::getNick() const { return _nickName; }
const std::string& Client::getUser() const { return _userName; }
const std::string& Client::getServer() const { return _serverName; }
bool Client::getCheckPassWord() const { return _check_passWord; }
std::string& Client::getOutBuffer() { return _out_buffer; }
std::string& Client::getInBuffer() { return _in_buffer; }
bool Client::getIsRegister() { return _is_register; }

/** setter **/
void Client::setNickName(const std::string &nickName) { _nickName = nickName; }
void Client::setUser(const std::string &userName) { _userName = userName; }
void Client::setServer(const std::string &serverName) { _serverName = serverName; }
void Client::setInBuffer(const std::string &buffer) { _in_buffer += buffer; }
void Client::setOutBuffer(const std::string &buffer) { _out_buffer += buffer; }
void Client::setCheckPassword(bool sOneShot) { _check_passWord = sOneShot; }
void Client::setIsRegister(bool sOneShot) { _is_register = sOneShot; }

/** check **/
bool Client::checkInfoSet()
{
    if (_nickName != "" && _check_passWord && _userName != "" && _serverName != "")
        return true;
    return false;
}

void Client::clearOutBuffer() { _out_buffer = ""; }