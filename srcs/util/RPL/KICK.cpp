#include "Util.hpp"
#include "Server.hpp"
#include "Channel.hpp"
#include "Message.hpp"
#include "Client.hpp"

namespace RPL
{
	namespace KICK
	{
		std::string SUCCESS(Client &executor, Message &message)
		{
			std::string reason_mess = "";
			for (size_t i = 0; i < message.getParams().size(); ++i)
			{
				if(i >= 2)
					reason_mess += message.getParam(i);
			}

			std::string buffer = ":" + RPL::getClientId(executor) + " KICK " + message.getParam(0);
			buffer += " " + message.getParam(1);
			if (reason_mess != "")
				buffer += " " + reason_mess; 
			buffer += "\r\n";
			return buffer;
		}

		std::string ERR_461(Client &executor)
		{
			std::string buffer = ":" + executor.getServer() + " 461 " + executor.getNick() + " KICK :Not enough parameters.\r\n";
			return buffer;
		}


		std::string ERR_403(Client &executor, Message &message)
		{
			std::string buffer = ":" + executor.getServer() + " 403 " + executor.getNick() + " " + message.getParam(0) + " :No such channel\r\n";
			return buffer;
		}

		std::string ERR_401(Client &executor, Message &message)
		{
			std::string buffer = ":" + executor.getServer() + " 401 " + executor.getNick() + " " + message.getParam(1) + " :No such nick\r\n";
			return buffer;
		}

		std::string ERR_441(Client &executor, Message &message)
		{
			std::string buffer = ":" + executor.getServer() + " 441 " + executor.getNick() + " " + message.getParam(1) + " :They are not on that channel\r\n";
			return buffer;
		}

		std::string ERR_442(Client &executor, Message &message)
		{
			std::string buffer = ":" + executor.getServer() + " 442 " + executor.getNick() + " " + message.getParam(0) + " :You're not on that channel!\r\n";
			return buffer;
		}

		std::string ERR_482(Client &executor, Message &message)
		{
			std::string buffer = ":" + executor.getServer() + " 482 " + executor.getNick() + " " + message.getParam(0) + " :You must be a channel operator\r\n";
			return buffer;
		}

	}
}
