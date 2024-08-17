#include "Util.hpp"
#include "Server.hpp"
#include "Channel.hpp"
#include "Message.hpp"
#include "Client.hpp"

namespace RPL
{
	namespace PASS
	{
		std::string ERR_461(Client &executor)
		{
			std::string buffer = ":" + executor.getServer() + " 461 " + executor.getNick() + " PASS :Not enough parameters.\r\n";
			return buffer;
		}
	}
}
