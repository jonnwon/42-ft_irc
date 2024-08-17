#include "Util.hpp"
#include "Server.hpp"
#include "Channel.hpp"
#include "Message.hpp"
#include "Client.hpp"

namespace RPL
{
	namespace INVITE
	{
		std::string SUCCESS_TO_EXECUTOR(Client &executor, Message &message)
		{
			std::string buffer = ":" + executor.getServer() + " 341 " + executor.getNick() + " " + message.getParam(0) + " :" + message.getParam(1) + "\r\n";
			return buffer;
		}

		std::string SUCCESS_TO_INVITED_CLIENT(Client &executor, Message &message)
		{
			std::string buffer = ":" + RPL::getClientId(executor) + " INVITE " + message.getParam(0) + " :" + message.getParam(1) + "\r\n";
			return buffer;
		}

		std::string SUCCESS_TO_CHANNEL(Client &executor, Message &message)
		{
			std::string buffer = ":" + executor.getServer() + " NOTICE " + message.getParam(1) + " :*** " + executor.getNick() + " invited " + message.getParam(0) + " into the channel\r\n";
			return buffer;
		}

		std::string ERR_461(Client &executor)
		{
			std::string buffer = ":" + executor.getServer() + " 461 " + executor.getNick() + " INVITE :Not enough parameters.\r\n";
			return buffer;
		}

		std::string ERR_401(Client &executor, Message &message)
		{
			std::string buffer = ":" + executor.getServer() + " 401 " + executor.getNick() + " " + message.getParam(0) + " " + message.getParam(1) + " :No such nick\r\n";
			return buffer;
		}

		std::string ERR_403(Client &executor, Message &message)
		{
			std::string buffer = ":" + executor.getServer() + " 403 " + executor.getNick() + " " + message.getParam(1) + " :No such channel\r\n";
			return buffer;
		}
		std::string ERR_442(Client &executor, Message &message)
		{
			std::string buffer = ":" + executor.getServer() + " 442 " + executor.getNick() + " " + message.getParam(1) + " :You're not on that channel!\r\n";
			return buffer;
		}
		std::string ERR_443(Client &executor, Message &message)
		{
			std::string buffer = ":" + executor.getServer() + " 443 " + executor.getNick() + " " + message.getParam(0) + " " + message.getParam(1) + " :is already on channel\r\n";
			return buffer;
		}
		std::string ERR_482(Client &executor, Message &message)
		{
			std::string buffer = ":" + executor.getServer() + " 482 " + executor.getNick() + " " + message.getParam(1) + " :You must be a channel operator\r\n";
			return buffer;
		}
	}
}
