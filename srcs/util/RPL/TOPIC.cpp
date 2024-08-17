#include "Util.hpp"
#include "Server.hpp"
#include "Channel.hpp"
#include "Message.hpp"
#include "Client.hpp"

namespace RPL
{
	namespace TOPIC
	{
		std::string SUCCESS(Client &executor, Message &message, const std::string& topic)
		{
			std::string buffer = ":" + RPL::getClientId(executor) + " TOPIC " + message.getParam(0) + " :" + topic;
			for (size_t i = 2; i < message.getParams().size(); ++i)
			{
				buffer += " ";
				buffer += message.getParam(i);
			}
			buffer += "\r\n";
			return buffer;
		}

		std::string SUCCESS_2(Client &executor, Message &message, const std::string &topic)
		{
			std::string buffer = ":" + executor.getServer() + " 332 " + executor.getNick() + " " + message.getParam(0) + " :" + topic + "\r\n";
			return buffer;
		}

		std::string ERR_461(Client &executor)
		{
			std::string buffer = ":" + executor.getServer() + " 461 " + executor.getNick() + " TOPIC :Not enough parameters.\r\n";
			return buffer;
		}

		std::string ERR_403(Client &executor, Message &message)
		{
			std::string buffer = ":" + executor.getServer() + " 403 " + executor.getNick() + " " + message.getParam(0) + " :No such channel.\r\n";
			return buffer;
		}

		std::string ERR_331(Client &executor, Message &message)
		{
			std::string buffer = ":" + executor.getServer() + " 331 " + executor.getNick() + " " + message.getParam(0) + " :No topic is set.\r\n";
			return buffer;
		}

		std::string ERR_442(Client &executor, Message &message)
		{
			std::string buffer = ":" + executor.getServer() + " 442 " + executor.getNick() + " " + message.getParam(0) + " :You're not on that channel!\r\n";
			return buffer;
		}


		std::string ERR_482(Client &executor, Message &message)
		{
			std::string buffer = ":" + executor.getServer() + " 482 " + executor.getNick() + " " + message.getParam(0) + " :You do not have access to change the topic on this channel\r\n";
			return buffer;
		}
	}
}
