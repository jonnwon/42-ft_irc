#include "Util.hpp"
#include "Server.hpp"
#include "Channel.hpp"
#include "Message.hpp"
#include "Client.hpp"

namespace RPL
{
	namespace BOT
	{
		std::string HELP()
		{
			std::string buffer = ":BOT!BOT_DDARI@this_is_man PRIVMSG #bot :Please enter the [libft], [pipex], [minishell], [cub3d], [inception]\r\n";
			return buffer;
		}

		std::string LIBFT()
		{
			std::string buffer = ":BOT!BOT_DDARI@this_is_man PRIVMSG #bot :This project is your very first project as a student at 42. You will need to recode a few functions of the C standard library as well as some other utility functions that you will use during your whole cursus.\r\n";
			return buffer;
		}

		std::string PIPEX()
		{
			std::string buffer = ":BOT!BOT_DDARI@this_is_man PRIVMSG #bot :This project aims to deepen your understanding of the two concepts that you already know: Redirections and Pipes. It is an introductory project for the bigger UNIX projects that will appear later on in the cursus.\r\n";
			return buffer;
		}

		std::string MINISHELL()
		{
			std::string buffer = ":BOT!BOT_DDARI@this_is_man PRIVMSG #bot :The objective of this project is for you to create a simple shell.\r\n";
			return buffer;
		}

		std::string CUB3D()
		{
			std::string buffer = ":BOT!BOT_DDARI@this_is_man PRIVMSG #bot :This project is inspired by the world-famous eponymous 90's game, which was the first FPS ever. It will enable you to explore ray-casting. Your goal will be to make a dynamic view inside a maze, in which you'll have to find your way.\r\n";
			return buffer;
		}
		std::string INCEPTION()
		{
			std::string buffer = ":BOT!BOT_DDARI@this_is_man PRIVMSG #bot :This project aims to broaden your knowledge of system administration by using Docker. You will virtualize several Docker images, creating them in your new personal virtual machine.\r\n";
			return buffer;
		}
		std::string ERROR(const std::string &cmd)
		{
			std::string buffer = ":BOT!BOT_DDARI@this_is_man PRIVMSG #bot " + cmd + ": Not command\r\n";
			buffer += ":BOT!BOT_DDARI@this_is_man PRIVMSG #bot :Please enter the [libft], [pipex], [minishell], [cub3d], [inception]\r\n";
			return buffer;
		}
	}
}
