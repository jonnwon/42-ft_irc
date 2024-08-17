#include "Util.hpp"
#include "Server.hpp"
#include "Channel.hpp"
#include "Message.hpp"
#include "Client.hpp"

static std::string readWelcomeMessage()
{
	const std::string filePath = WELCOME_FILE_PATH;
	std::ifstream file(filePath.c_str());
	std::string buffer;

	if (file.is_open())
	{
		std::getline(file, buffer, '\0');
		file.close();
	}
	else
	{
		std::cerr << "Error opening welcome file: " << filePath << std::endl;
		buffer = "୧༼ಠ益ಠ༽୨ What is man? confident!!!";
	}
	return buffer;
}

namespace RPL
{
	namespace WELCOME
	{
		std::string STR0(Client &client)
		{
			std::string buffer = ":" + RPL::getClientId(client) + " NICK " + client.getNick() + "\r\n";
			return buffer;
		}
		std::string STR1(Client &client)
		{
			std::string buffer = ":localhost 001 " + client.getNick() + " :Welcome IRC :" + RPL::getClientId(client) + "\r\n";
			return buffer;
		}
		std::string STR2(Client &client)
		{
			std::string buffer = ":localhost 002 " + client.getNick() + " :Your host is ft_irc (" + client.getServer() + ")" + "\r\n";
			return buffer;
		}
		std::string STR3(Client &client)
		{
			std::time_t currentTime = std::time(NULL);
			std::string timeString = std::ctime(&currentTime);
			std::string buffer = ":localhost 003 " + client.getNick() + " :created time :" + timeString + "\r\n";
			return buffer;
		}
		std::string STR4(Client &client)
		{
			std::string buffer = ":localhost 004 " + client.getNick() + " " + client.getServer() + "\r\n";
			return buffer;
		}
		std::string STR5(Client &client)
		{
			std::string buffer = ":localhost 005 " + client.getNick() + "°º¤ø,¸¸,ø¤º°`°º¤ø,¸,ø¤°º¤ø,¸¸,ø¤º°`°º¤ø,¸\r\n";
			return buffer;
		}
		std::string STR5_1(Client &client)
		{
			std::string buffer = ":localhost 375 " + client.getNick() + " :" + "************** What is man? Confident!! **************" + "\r\n";
			return buffer;
		}
		std::string STR5_2(Client &client)
		{
			std::string buffer = ":localhost 372 " + client.getNick() + " :" + readWelcomeMessage() + "\r\n";
			return buffer;
		}
		std::string STR6(Client &client)
		{
			std::string buffer = ":localhost 376 " + client.getNick() + " :" + "************** What is man? Confident!! **************" + "\r\n";
			return buffer;
		}
	}
}