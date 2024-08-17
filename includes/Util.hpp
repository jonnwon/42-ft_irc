#ifndef UTIL_HPP
#define UTIL_HPP

#include <iostream>
#include <string>
#include <vector>
class Server;
class Channel;
class Message;
class Client;

enum check_Mode
{
	Mode_plus_I = 0,
	Mode_minus_I,

	Mode_plus_T,
	Mode_minus_T,

    Mode_plus_K,
	Mode_minus_K,

	Mode_plus_O,
	Mode_minus_O,

	Mode_plus_L,
	Mode_minus_L,

	Mode_error,
};

namespace RPL
{
	std::string NO_REPLY();
	std::string getClientId(Client &client);

	std::string ERR_421(Client &executor, Message &message);
	namespace WELCOME
	{
		std::string STR0(Client &client);
		std::string STR1(Client &client);
		std::string STR2(Client &client);
		std::string STR3(Client &client);
		std::string STR4(Client &client);
		std::string STR5(Client &client);
		std::string STR5_1(Client &client);
		std::string STR5_2(Client &client);
		std::string STR6(Client &client);
	}

	namespace BOT
	{
		std::string HELP();
		std::string LIBFT();
		std::string PIPEX();
		std::string MINISHELL();
		std::string CUB3D();
		std::string INCEPTION();
		std::string ERROR(const std::string &cmd);
	}

	namespace PASS
	{
		std::string ERR_461(Client &executor);
	}
	
	namespace NICK
	{
		std::string SUCCESS(Client &executor, Message &message);
		std::string ERR_461(Client &executor);
		std::string ERR_433(Client &executor, Message &message);
		std::string ERR_473(Client &executor, Message &message);
	}

	namespace USER
	{
		std::string ERR_461(Client &executor);
	}

	namespace JOIN
	{
		std::string SUCCESS(Client &executor, Message &message);
		std::string ERR_461(Client &executor);
		std::string SUCCESS_332(Client &executor, Message &message, const std::string &topic);
		std::string SUCCESS_353_366(Client &executor, Message &message, const std::string &client_list);
		std::string ERR_451(Client &executor);
		std::string ERR_471(Client &executor, Message &message);
		std::string ERR_473(Client &executor, Message &message);
		std::string ERR_475(Client &executor, Message &message);
		std::string ERR_476(Client &executor, Message &message);
	}

	namespace INVITE
	{
		std::string SUCCESS_TO_EXECUTOR(Client &executor, Message &message);
		std::string SUCCESS_TO_INVITED_CLIENT(Client &executor, Message &message);
		std::string SUCCESS_TO_CHANNEL(Client &executor, Message &message);
		std::string ERR_461(Client &executor);
		std::string ERR_401(Client &executor, Message &message);
		std::string ERR_403(Client &executor, Message &message);
		std::string ERR_442(Client &executor, Message &message);
		std::string ERR_443(Client &executor, Message &message);
		std::string ERR_482(Client &executor, Message &message);
	}

	namespace PING
	{
		std::string SUCCESS(Message &message);
	}

	namespace PART
	{
		std::string SUCCESS(Client &executor, Message &message);
		std::string ERR_461(Client &executor);
		std::string ERR_403(Client &executor, Message &message);
		std::string ERR_422(Client &executor, Message &message);
	}

	namespace QUIT
	{
		std::string SUCCESS_TO_EXECUTOR(Client &executor, Message &message);
        std::string SUCCESS_TO_CHANNEL(Client &executor, Message &message);
		std::string DIS_CONNECTION(Client &executor);
	}

	namespace PRIVMSG
	{
		std::string SUCCESS_TO_CLIENT(Client &executor, Message &message, std::string &message_b);
		std::string SUCCESS_TO_CHANNEL(Client &executor, Message &message, std::string &message_buffer);
		std::string ERR_401(Client &executor, Message &message);
		std::string ERR_403(Client &executor, Message &message);
		std::string ERR_404(Client &executor, Message &message);
		std::string ERR_461(Client &executor);
	}

	namespace TOPIC
	{
		std::string SUCCESS(Client &executor, Message &message, const std::string &topic);
		std::string SUCCESS_2(Client &executor, Message &message, const std::string &topic);
		std::string ERR_461(Client &executor);
		std::string ERR_403(Client &executor, Message &message);
		std::string ERR_331(Client &executor, Message &message);
		std::string ERR_442(Client &executor, Message &message);
		std::string ERR_482(Client &executor, Message &message);
	}

	namespace KICK
	{
		std::string SUCCESS(Client &executor, Message &message);
		std::string ERR_461(Client &executor);
		std::string ERR_403(Client &executor, Message &message);
		std::string ERR_401(Client &executor, Message &message);
		std::string ERR_441(Client &executor, Message &message);
		std::string ERR_442(Client &executor, Message &message);
		std::string ERR_482(Client &executor, Message &message);
	}

	namespace MODE
	{
		std::string ERR_461(Client &executor);
		std::string ERR_300(Client &executor, Message &message);
		std::string ERR_403(Client &executor, Message &message);
		std::string ERR_482(Client &executor, Message &message);
	}

	namespace MODE_pI
	{
		std::string SUCCESS(Client &executor, Message &message);
		std::string ERR_300(Client &executor, Message &message);
	}

	namespace MODE_mI
	{
		std::string SUCCESS(Client &executor, Message &message);
		std::string ERR_300(Client &executor, Message &message);
	}

	namespace MODE_pT
	{
		std::string SUCCESS(Client &executor, Message &message);
		std::string ERR_300(Client &executor, Message &message);
	}

	namespace MODE_mT
	{
		std::string SUCCESS(Client &executor, Message &message);
		std::string ERR_300(Client &executor, Message &message);
	}

	namespace MODE_pK
	{
		std::string SUCCESS(Client &executor, Message &message);
		std::string ERR_696(Client &executor, Message &message);
	}

	namespace MODE_mK
	{
		std::string SUCCESS(Client &executor, Message &message);
		std::string ERR_696(Client &executor, Message &message);
		std::string ERR_467(Client &executor, Message &message);
	}

	namespace MODE_pO
	{
		std::string SUCCESS(Client &executor, Message &message);
		std::string ERR_696(Client &executor, Message &message);
		std::string ERR_401(Client &executor, Message &message);

	}

	namespace MODE_mO
	{
		std::string SUCCESS(Client &executor, Message &message);
		std::string ERR_696(Client &executor, Message &message);
		std::string ERR_401(Client &executor, Message &message);
	}

	namespace MODE_pL
	{
		std::string SUCCESS(Client &executor, Message &message);
		std::string ERR_696(Client &executor, Message &message);
		std::string ERR_300(Client &executor, Message &message);
	}

	namespace MODE_mL
	{
		std::string SUCCESS(Client &executor, Message &message);
		std::string ERR_300(Client &executor, Message &message);
	}
}


namespace Check
{
	void checkArg(int argc, char **argv);
	bool invitedList(Channel &channel, const std::string &nick_name);
	check_Mode getModeToEnum(const std::string &mode);
	bool executableMode(Server &server, Channel &channel, Message &message, check_Mode mode, std::string &buffer, Client &executor);
}


namespace Parsing
{
	void splitByCRLF(std::string &input, std::vector<std::string> &result);
	bool isValidModeArgument(const std::string& mode);
}

#endif
