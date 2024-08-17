#include "Util.hpp"
#include "Server.hpp"
#include "Channel.hpp"
#include "Message.hpp"
#include "Client.hpp"

namespace RPL
{
	namespace QUIT
	{
		std::string SUCCESS_TO_EXECUTOR(Client &executor, Message &message)
		{
			std::string buffer = "ERROR :Closing link: (" + executor.getUser() + "@" + executor.getServer() + ") [Quit:";

			for (size_t i = 0; i < message.getParams().size(); ++i)
			{
				buffer += " ";
				if (i == 0)
					buffer += message.getParam(i).substr(1);
				else
					buffer += message.getParam(i);
			}
			buffer += "]\r\n";
			return buffer;
		}

		std::string SUCCESS_TO_CHANNEL(Client &executor, Message &message)
		{
			std::string buffer = ":" + RPL::getClientId(executor) + " QUIT :Quit:";

			for (size_t i = 0; i < message.getParams().size(); ++i)
			{
				buffer += " ";
				if (i == 0)
					buffer += message.getParam(i).substr(1);
				else
					buffer += message.getParam(i);
			}
			buffer += "\r\n";

			return buffer;
		}

		std::string DIS_CONNECTION(Client &executor)
		{
			const std::string buffer = ":" + RPL::getClientId(executor) + " QUIT :Connection closed\r\n";
			return buffer;
		}
	}
}
