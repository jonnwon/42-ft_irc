#include "Util.hpp"
#include "Server.hpp"
#include "Channel.hpp"
#include "Message.hpp"
#include "Client.hpp"

namespace Parsing
{
	void splitByCRLF(std::string &client_in_buffer, std::vector<std::string> &result)
	{
		std::istringstream ss(client_in_buffer);
		std::string line;

		if (client_in_buffer.find('\n') == std::string::npos)
			return;
		while (std::getline(ss, line, '\n'))
		{
			if (line.find_first_not_of("\r\n\t ") == std::string::npos)
				continue;
			if (!line.empty() && line.length() >= 1 && line[line.length() - 1] == '\r')
				line.erase(line.length() - 1);
			result.push_back(line);
		}
		client_in_buffer = "";
	}

	bool isValidModeArgument(const std::string &mode)
	{
		if (mode.length() != 2)
			return false;

		if (mode[0] != '+' && mode[0] != '-')
			return false;

		if (mode[1] != 'i' && mode[1] != 't' && mode[1] != 'k' && mode[1] != 'o' && mode[1] != 'l')
			return false;

		return true;
	}
}
