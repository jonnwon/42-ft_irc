#include "Util.hpp"
#include "Server.hpp"
#include "Channel.hpp"
#include "Message.hpp"
#include "Client.hpp"

namespace RPL
{
	namespace MODE 
	{
		std::string ERR_461(Client &executor)
		{
			std::string buffer = ":" + executor.getServer() + " 461 " + executor.getNick() + " MODE :Not enough parameters.\r\n";
			return buffer;
		}

		std::string ERR_300(Client &executor, Message &message)
		{
			std::string buffer = ":" + executor.getServer() + " 300 " + executor.getNick() + " " + message.getParam(0) + " " + message.getParam(1) + " :not command\r\n";
			return buffer;
		}

		std::string ERR_403(Client &executor, Message &message)
		{
			std::string buffer = ":" + executor.getServer() + " 403 " + executor.getNick() + " " + message.getParam(0) + " :no such channel\r\n";
			return buffer;
		}

		std::string ERR_482(Client &executor, Message &message)
		{
			std::string buffer = ":" + executor.getServer() + " 482 " + executor.getNick() + " " + message.getParam(0) + " :You must have channel op access or above to unset channel mode t\r\n";
			return buffer;
		}
	}

	namespace MODE_pI
	{
		std::string SUCCESS(Client &executor, Message &message)
		{
			std::string buffer = ":" + RPL::getClientId(executor) + " MODE " + message.getParam(0) + " :+i\r\n";
			return buffer;
		}

		std::string ERR_300(Client &executor, Message &message)
		{
			std::string buffer = ":" + executor.getServer() + " 300 " + executor.getNick() + " " + message.getParam(0) + " " + message.getParam(1) + " :not command\r\n";
			return buffer;
		}
	}

	namespace MODE_mI
	{
		std::string SUCCESS(Client &executor, Message &message)
		{
			std::string buffer = ":" + RPL::getClientId(executor) + " MODE " + message.getParam(0) + " :-i\r\n";
			return buffer;
		}

		std::string ERR_300(Client &executor, Message &message)
		{
			std::string buffer = ":" + executor.getServer() + " 300 " + executor.getNick() + " " + message.getParam(0) + " " + message.getParam(1) + " :not command\r\n";
			return buffer;
		}
	}

	namespace MODE_pT
	{
		std::string SUCCESS(Client &executor, Message &message)
		{
			std::string buffer = ":" + RPL::getClientId(executor) + " MODE " + message.getParam(0) + " :+t\r\n";
			return buffer;
		}

		std::string ERR_300(Client &executor, Message &message)
		{
			std::string buffer = ":" + executor.getServer() + " 300 " + executor.getNick() + " " + message.getParam(0) + " " + message.getParam(1) + " :not command\r\n";
			return buffer;
		}

	}

	namespace MODE_mT
	{
		std::string SUCCESS(Client &executor, Message &message)
		{
			std::string buffer = ":" + RPL::getClientId(executor) + " MODE " + message.getParam(0) + " :-t\r\n";
			return buffer;
		}

		std::string ERR_300(Client &executor, Message &message)
		{
			std::string buffer = ":" + executor.getServer() + " 300 " + executor.getNick() + " " + message.getParam(0) + " " + message.getParam(1) + " :not command\r\n";
			return buffer;
		}

	}

	namespace MODE_pK
	{
		std::string SUCCESS(Client &executor, Message &message)
		{
			std::string buffer = ":" + RPL::getClientId(executor) + " MODE " + message.getParam(0) + " +k :" + message.getParam(2) + "\r\n";
			return buffer;
		}

		std::string ERR_696(Client &executor, Message &message)
		{
			std::string buffer = ":" + executor.getServer() + " 696 " + executor.getNick() + " " + message.getParam(0) + " k * " + " :You must specify a parameter for the key mode. Syntax: <key>.\r\n";
			return buffer;
		}
	}

	namespace MODE_mK
	{
		std::string SUCCESS(Client &executor, Message &message)
		{
			std::string buffer = ":" + RPL::getClientId(executor) + " MODE " + message.getParam(0) + " -k :" + message.getParam(2) + "\r\n";
			return buffer;
		}

		std::string ERR_696(Client &executor, Message &message)
		{
			std::string buffer = ":" + executor.getServer() + " 696 " + executor.getNick() + " " + message.getParam(0) + " k * " + " :You must specify a parameter for the key mode. Syntax: <key>.\r\n";
			return buffer;
		}

		std::string ERR_467(Client &executor, Message &message)
		{
			std::string buffer = ":" + executor.getServer() + " 467 " + executor.getNick() + " #" + message.getParam(0) + " :Channel key already set\r\n";
			return buffer;
		}
	}

	namespace MODE_pO
	{
		std::string SUCCESS(Client &executor, Message &message)
		{
			std::string buffer = ":" + RPL::getClientId(executor) + " MODE " + message.getParam(0) + " +o :" + message.getParam(2) + "\r\n";
			return buffer;
		}

		std::string ERR_696(Client &executor, Message &message)
		{
			std::string buffer = ":" + executor.getServer() + " 696 " + executor.getNick() + " " + message.getParam(0) + " o * " + " :You must specify a parameter for the op mode. Syntax: <nick>.\r\n";
			return buffer;
		}
		std::string ERR_401(Client &executor, Message &message)
		{
			std::string buffer = ":" + executor.getServer() + " 401 " + executor.getNick() + " " + message.getParam(1) + " :No such nick\r\n";
			return buffer;
		}
	}

	namespace MODE_mO
	{
		std::string SUCCESS(Client &executor, Message &message)
		{
			std::string buffer = ":" + RPL::getClientId(executor) + " MODE " + message.getParam(0) + " -o :" + message.getParam(2) + "\r\n";
			return buffer;
		}

		std::string ERR_696(Client &executor, Message &message)
		{
			std::string buffer = ":" + executor.getServer() + " 696 " + executor.getNick() + " " + message.getParam(0) + " o * " + " :You must specify a parameter for the op mode. Syntax: <nick>.\r\n";
			return buffer;
		}
		std::string ERR_401(Client &executor, Message &message)
		{
			std::string buffer = ":" + executor.getServer() + " 401 " + executor.getNick() + " " + message.getParam(2) + " :No such nick\r\n";
			return buffer;
		}
	}

	namespace MODE_pL
	{
		std::string SUCCESS(Client &executor, Message &message)
		{
			std::string buffer = ":" + RPL::getClientId(executor) + " MODE " + message.getParam(0) + " +l :" + message.getParam(2) + "\r\n";
			return buffer;
		}

		std::string ERR_696(Client &executor, Message &message)
		{
			std::string buffer = ":" + executor.getServer() + " 696 " + executor.getNick() + " " + message.getParam(0) + " l * " + " :You must specify a parameter for the limit mode. Syntax: <limit>.\r\n";
			return buffer;
		}

		std::string ERR_300(Client &executor, Message &message)
		{
			std::string buffer = ":" + executor.getServer() + " 300 " + executor.getNick() + " " + message.getParam(0) + " " + message.getParam(1) + " :not command\r\n";
			return buffer;
		}
	}

	namespace MODE_mL
	{
		std::string SUCCESS(Client &executor, Message &message)
		{
			std::string buffer = ":" + RPL::getClientId(executor) + " MODE " + message.getParam(0) + " :-l\r\n";
			return buffer;
		}
		std::string ERR_300(Client &executor, Message &message)
		{
			std::string buffer = ":" + executor.getServer() + " 300 " + executor.getNick() + " " + message.getParam(0) + " " + message.getParam(1) + " :not command\r\n";
			return buffer;
		}
	}
}