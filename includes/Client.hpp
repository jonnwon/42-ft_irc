#ifndef CLIENT_HPP
#define CLIENT_HPP

#include <iostream>

class Client
{
private:
    std::string _nickName;
    std::string _userName;
    std::string _serverName;
    std::string _out_buffer;
    std::string _in_buffer;
    bool _check_passWord;
    bool _is_register;

    Client &operator=(const Client &other);
public:
    Client();
    Client(const Client &other);
    ~Client();

    /** getter **/
    const std::string &getNick() const;
    const std::string &getUser() const;
    const std::string &getServer() const;
    bool getCheckPassWord() const;
    std::string &getOutBuffer();
    std::string &getInBuffer();
    bool getIsRegister();

    /** setter **/
    void setNickName(const std::string &nickName);
    void setUser(const std::string &userName);
    void setServer(const std::string &serverName);
    void setInBuffer(const std::string &buffer);
    void setOutBuffer(const std::string &buffer);
    void setCheckPassword(bool sOneShot);
    void setIsRegister(bool sOneShot);

    /** check **/
    bool checkInfoSet();
    void clearOutBuffer();
};

#endif
