#include "Util.hpp"
#include "Server.hpp"
#include "Channel.hpp"
#include "Message.hpp"
#include "Client.hpp"

namespace RPL
{
	namespace USER
	{
		std::string ERR_461(Client &executor)
		{
			std::string nick = "*";
			std::string server = "localhost";

			if (executor.getNick() != "")
				nick = executor.getNick();
			if (executor.getServer() != "")
				server = executor.getServer();
				
			std::string buffer = ":" + server + " 461 " + nick + " USER :Not enough parameters.\r\n";
			return buffer;
		}
	}
}