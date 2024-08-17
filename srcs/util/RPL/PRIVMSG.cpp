#include "Util.hpp"
#include "Server.hpp"
#include "Channel.hpp"
#include "Message.hpp"
#include "Client.hpp"

namespace RPL
{
	namespace PRIVMSG
	{
		std::string SUCCESS_TO_CLIENT(Client &executor, Message &message, std::string &message_buffer)
		{
			std::string buffer = ":" + RPL::getClientId(executor) + " PRIVMSG " + message.getParam(0) + " " + message_buffer + "\r\n";
			return buffer;
		}

		std::string SUCCESS_TO_CHANNEL(Client &executor, Message &message, std::string &message_buffer)
		{
			std::string buffer = ":" + RPL::getClientId(executor) + " PRIVMSG " + message.getParam(0) + " " + message_buffer + "\r\n";
			return buffer;
		}

		std::string ERR_401(Client &executor, Message &message)
		{
			std::string buffer = ":" + executor.getServer() + " 401 " + executor.getNick() + " " + message.getParam(0) + " :No such nick\r\n";
			return buffer;
		}

		std::string ERR_403(Client &executor, Message &message)
		{
			std::string buffer = ":" + executor.getServer() + " 403 " + executor.getNick() + " " + message.getParam(0) + " :No such channel\r\n";
			return buffer;
		}

		std::string ERR_404(Client &executor, Message &message)
		{
			std::string buffer = ":" + executor.getServer() + " 404 " + executor.getNick() + " " + message.getParam(0) + " :You cannot send external messages to this channel whilst the +n (noextmsg) mode is set.\r\n";
			return buffer;
		}

		std::string ERR_461(Client &executor)
		{
			std::string buffer = ":" + executor.getServer() + " 461 " + executor.getNick() + " " + "PRIVMSG" + " :Not enough parameters.\r\n";
			return buffer;
		}

	}
}
