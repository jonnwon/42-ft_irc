#include "Util.hpp"
#include "Server.hpp"
#include "Channel.hpp"
#include "Message.hpp"
#include "Client.hpp"

namespace RPL
{
	namespace PING
	{
		std::string SUCCESS(Message &message)
		{
			std::string buffer = ":" + message.getParam(0) + " PONG " + message.getParam(0) + " :" + message.getParam(0) + "\r\n";
			return buffer;
		}
	}
}
