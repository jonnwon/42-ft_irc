#ifndef MESSAGE_HPP
#define MESSAGE_HPP

#include <iostream>
#include <vector>
#include <sstream>
#include <string>

class Message
{
private:
    int _executor_fd;
    std::string _cmd;
    std::vector<std::string> _params;

    Message();
    Message &operator=(const Message &other);

public:
    Message(int fd, std::string &line);
    Message(std::string &line);
    Message(const Message &other);
    ~Message();

    /** getter **/
    const std::string &getCmd() const;
    const std::string &getParam(int i) const;
    std::vector<std::string> getParams();
};

#endif
