#include "Util.hpp"
#include "Server.hpp"
#include "Channel.hpp"
#include "Message.hpp"
#include "Client.hpp"

namespace RPL
{
	namespace JOIN
	{
		std::string SUCCESS(Client &executor, Message &message)
		{
			std::string buffer = ":" + RPL::getClientId(executor) + " JOIN :" + message.getParam(0) + "\r\n";
			return buffer;
		}

		std::string ERR_461(Client &executor)
		{
			std::string buffer = ":" + executor.getServer() + " 461 " + executor.getNick() + " JOIN :Not enough parameters.\r\n";
			return buffer;
		}

		std::string SUCCESS_332(Client &executor, Message &message, const std::string &topic)
		{
			std::string buffer = ":" + RPL::getClientId(executor) + " 332 " + executor.getUser() + " " + message.getParam(0) + " :" + topic +"\r\n";
			return buffer;
		}

		std::string SUCCESS_353_366(Client &executor, Message &message, const std::string &client_list)
		{
			std::string buffer = ":" + executor.getServer() + " 353 " + executor.getUser() + " = " + message.getParam(0) + " :" + client_list + "\r\n";
			buffer += ":" + executor.getServer() + " 366 " + executor.getUser() + ' ' + message.getParam(0) + " :End of /NAMES list.\r\n";
			return buffer;
		}

		std::string ERR_451(Client &executor)
		{
			std::string buffer = ":" + executor.getServer() + " 451 * JOIN :You have not registered.\r\n";
			return buffer;
		}

		std::string ERR_471(Client &executor, Message &message)
		{
			std::string buffer = ":" + executor.getServer() + " 471 " + executor.getNick() + " " + message.getParam(0) + " :Cannot join channel (channel is full)\r\n";
			return buffer;
		}

		std::string ERR_473(Client &executor, Message &message)
		{
			std::string buffer = ":" + executor.getServer() + " 473 " + executor.getNick() + " " + message.getParam(0) + " :Cannot join channel (invite only)\r\n";
			return buffer;
		}

		std::string ERR_475(Client &executor, Message &message)
		{
			std::string buffer = ":" + executor.getServer() + " 475 " + executor.getNick() + " " + message.getParam(0) + " :Cannot join channel (incorrect channel key)\r\n";
			return buffer;
		}

		std::string ERR_476(Client &executor, Message &message)
		{
			std::string buffer = ":" + executor.getServer() + " 476 " + executor.getNick() + " " + message.getParam(0) + " :Invalid channel name\r\n";
			return buffer;
		}
	}
}
