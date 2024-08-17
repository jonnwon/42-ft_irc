#include "Util.hpp"
#include "Server.hpp"
#include "Channel.hpp"
#include "Message.hpp"
#include "Client.hpp"

namespace RPL
{
	namespace NICK
	{
		std::string SUCCESS(Client &executor, Message &message)
		{
			std::string buffer = ":" + RPL::getClientId(executor) + " NICK :" + message.getParam(0) + "\r\n";
			return buffer;
		}

		std::string ERR_461(Client &executor)
		{
			std::string buffer = ":" + executor.getServer() + " 461 " + executor.getNick() + " NICK :Not enough parameters.\r\n";
			return buffer;
		}

		std::string ERR_433(Client &executor, Message &message)
		{
			std::string buffer = ":" + executor.getServer() + " 433 * " + message.getParam(0) + " :Nickname is already in use.\r\n";
			return buffer;
		}
	}
}
