#include "Util.hpp"
#include "Server.hpp"
#include "Channel.hpp"
#include "Message.hpp"
#include "Client.hpp"

namespace RPL
{
	std::string NO_REPLY() { return ""; }

	std::string getClientId(Client &client)
	{
		std::string str = client.getNick() + "!" + client.getUser() + "@" + client.getServer();
		return str;
	}

	std::string ERR_421(Client &executor, Message &message)
	{
		std::string buffer = ":" + executor.getServer() + " 421 " + executor.getNick() + " " + message.getCmd() + " :Unknown command\r\n";
		return buffer;
	}
}
