#include "Message.hpp"

Message::Message(int fd, std::string &line) : _executor_fd(fd)
{
	std::istringstream ss(line);

	ss >> _cmd;
	std::string param;
	while (ss >> param)
		_params.push_back(param);
}

Message::Message(std::string &line) : _executor_fd(0)
{
	std::istringstream ss(line);

	ss >> _cmd;
	std::string param;
	while (ss >> param)
		_params.push_back(param);
}

Message::Message(const Message &other) : _executor_fd(other._executor_fd), _cmd(other._cmd), _params(other._params) { }

Message::~Message() {}

/** getter **/
const std::string& Message::getCmd() const { return _cmd; }
const std::string& Message::getParam(int i) const { return _params[i]; }
std::vector<std::string> Message::getParams() { return _params; }