#include "Util.hpp"
#include "Server.hpp"
#include "Channel.hpp"
#include "Message.hpp"
#include "Client.hpp"

namespace RPL
{
	namespace PART
	{
		std::string SUCCESS(Client &executor, Message &message)
		{
			std::string buffer = ":" + RPL::getClientId(executor) + " PART :" + message.getParam(0);
			for (size_t i = 1; i < message.getParams().size(); ++i)
			{
				buffer += " ";
				buffer += message.getParam(i);
			}
			buffer += "\r\n";
			return buffer;
		}

		std::string ERR_461(Client &executor)
		{
			std::string buffer = ":" + executor.getServer() + " 461 PART " + executor.getNick() + " :Not enough parameters.\r\n";
			return buffer;
		}

		std::string ERR_403(Client &executor, Message &message) 
		{
			std::string buffer = ":" + executor.getServer() + " 403 " + executor.getNick() + " " + message.getParam(0) + " :No such channel\r\n";
			return buffer;
		}

		std::string ERR_422(Client &executor, Message &message)
		{
			std::string buffer = ":" + executor.getServer() + " 442 " + executor.getNick() + " " + message.getParam(0) + " :You're not on that channel\r\n";
			return buffer;
		}
	}
}
