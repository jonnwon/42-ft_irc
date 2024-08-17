#include "Util.hpp"
#include "Server.hpp"
#include "Channel.hpp"
#include "Message.hpp"
#include "Client.hpp"

namespace Check
{
	void checkArg(int argc, char **argv)
	{
		if (argc != 3)
		{
			std::cerr << "./irc <port_number> <pass_word>" << std::endl;
			throw std::logic_error("Invalid argument number");
		}
		char *end;
		long number = std::strtol(argv[1], &end, 10);

		if (*end != '\0' || number < 1024 || number > 49151 || argv[1][0] == '+' || argv[1][0] == '0')
		{
			std::cerr << "./irc <port_number> <pass_word>" << std::endl;
			std::cerr << "Valid port numbers are in the range 1024 to 49151, excluding those starting with '+'." << std::endl;
			throw std::logic_error("Invalid port number");
		}

		number = std::strtol(argv[2], &end, 10);
		if (std::strlen(argv[2]) == 0 || *end != '\0' || argv[2][0] == '+' || argv[2][0] == '-')
		{
			std::cerr << "./irc <port_number> <pass_word>" << std::endl;
			std::cerr << "Valid passwords are only in numbers. " << std::endl;
			throw std::logic_error("Invalid password");
		}

		std::cout << "PortNumber: " << argv[1] << std::endl;
		std::cout << "PassWord: " << argv[2] << std::endl;
	}

	bool invitedList(Channel &channel, const std::string &nick_name)
	{
		std::vector<std::string> &list = channel.getInvitedList();
		std::vector<std::string>::iterator it = std::find(list.begin(), list.end(), nick_name);
		if (it != list.end())
			return true;
		return false;
	}

	check_Mode getModeToEnum(const std::string &mode)
	{
		if (mode == "+i")
			return Mode_plus_I;
		if (mode == "-i")
			return Mode_minus_I;

		if (mode == "+t")
			return Mode_plus_T;
		if (mode == "-t")
			return Mode_minus_T;

		if (mode == "+k")
			return Mode_plus_K;
		if (mode == "-k")
			return Mode_minus_K;

		if (mode == "+l")
			return Mode_plus_L;
		if (mode == "-l")
			return Mode_minus_L;

		if (mode == "+o")
			return Mode_plus_O;
		if (mode == "-o")
			return Mode_minus_O;

		return Mode_error;
	}

	bool executableMode(Server &server, Channel &channel, Message &message, check_Mode mode, std::string &buffer, Client &executor)
	{
		std::string channel_name = channel.getName();
		switch (mode)
		{
		case Mode_plus_I:
			if (message.getParams().size() != 2)
			{
				buffer = RPL::MODE_pI::ERR_300(executor, message);
				return false;
			}
			else if (channel.checkMode(MODE_I) == true)
			{
				buffer = RPL::NO_REPLY();
				return false;
			}
			else
				return true;

		case Mode_minus_I:
			if (message.getParams().size() != 2)
			{
				buffer = RPL::MODE_mI::ERR_300(executor, message);
				return false;
			}
			else if (channel.checkMode(MODE_I) == false)
			{
				buffer = RPL::NO_REPLY();
				return false;
			}
			else
				return true;

		case Mode_plus_T:
			if (message.getParams().size() != 2)
			{
				buffer = RPL::MODE_pT::ERR_300(executor, message);
				return false;
			}
			else if (channel.checkMode(MODE_T) == true)
			{
				buffer = RPL::NO_REPLY();
				return false;
			}
			else
				return true;

		case Mode_minus_T:
			if (message.getParams().size() != 2)
			{
				buffer = RPL::MODE_mT::ERR_300(executor, message);
				return false;
			}
			else if (channel.checkMode(MODE_T) == false)
			{
				buffer = RPL::NO_REPLY();
				return false;
			}
			else
				return true;

		case Mode_plus_K:
			if (message.getParams().size() != 3)
			{
				buffer = RPL::MODE_pK::ERR_696(executor, message);
				return false;
			}
			else if (channel.checkMode(MODE_K) == true && channel.getPassword() == message.getParam(2))
			{
				buffer = RPL::NO_REPLY();
				return false;
			}
			else
				return true;

		case Mode_minus_K:
			if (message.getParams().size() != 3)
			{
				buffer = RPL::MODE_mK::ERR_696(executor, message);
				return false;
			}
			else if (channel.getPassword() != message.getParam(2))
			{
				buffer = RPL::MODE_mK::ERR_467(executor, message);
				return false;
			}
			else
				return true;

		case Mode_plus_O:
			if (message.getParams().size() != 3)
			{
				buffer = RPL::MODE_pO::ERR_696(executor, message);
				return false;
			}
			else if (server.isClient(message.getParam(2)) == false)
			{
				buffer = RPL::MODE_pO::ERR_401(executor, message);
				return false;
			}
			else if (channel.getAuthority(message.getParam(2)) == OPERATOR ||
					 channel.isClient(message.getParam(2)) == false)
			{
				buffer = RPL::NO_REPLY();
				return false;
			}
			else
				return true;

		case Mode_minus_O:
			if (message.getParams().size() != 3)
			{
				buffer = RPL::MODE_mO::ERR_696(executor, message);
				return false;
			}
			else if (server.isClient(message.getParam(2)) == false)
			{
				buffer = RPL::MODE_mO::ERR_401(executor, message);
				return false;
			}
			else if (channel.getAuthority(message.getParam(2)) == REGULAR || channel.isClient(message.getParam(2)) == false)
			{
				buffer = RPL::NO_REPLY();
				return false;
			}
			else
				return true;

		case Mode_plus_L:
			if (message.getParams().size() != 3)
			{
				buffer = RPL::MODE_pL::ERR_696(executor, message);
				return false;
			}
			else if (channel.checkMode(MODE_L) == true && channel.getMaxClient() == atoi(message.getParam(2).c_str()))
			{
				buffer = RPL::NO_REPLY();
				return false;
			}
			else if (atoi(message.getParam(2).c_str()) == false)
			{
				buffer = RPL::MODE_pL::ERR_300(executor, message);
				return false;
			}
			else
				return true;

		case Mode_minus_L:
			if (message.getParams().size() != 2)
			{
				buffer = RPL::MODE_mL::ERR_300(executor, message);
				return false;
			}
			else if (channel.checkMode(MODE_L) == false)
			{
				buffer = RPL::NO_REPLY();
				return false;
			}
			else
				return true;

		default:
			break;
		}
		return true;
	}
}
