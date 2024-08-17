#include "Server.hpp"

namespace Command
{
    static e_Bot getTargetBot(const std::string &cmd)
    {
        if (cmd == ":help")
            return HELP;
        if (cmd == ":libft")
            return LIBFT;
        if (cmd == ":pipex")
            return PIPEX;
        if (cmd == ":minishell")
            return MINISHELL;
        if (cmd == ":cub3d")
            return CUB3D;
        if (cmd == ":inception")
            return INCEPTION;
        return B_ERROR;
    }

    static void handleBotMsg(const std::string &message, std::string &buffer)
    {
        switch (getTargetBot(message))
        {
        case HELP:
            buffer = RPL::BOT::HELP();
            break;
        case LIBFT:
            buffer = RPL::BOT::LIBFT();
            break;
        case PIPEX:
            buffer = RPL::BOT::PIPEX();
            break;
        case MINISHELL:
            buffer = RPL::BOT::MINISHELL();
            break;
        case CUB3D:
            buffer = RPL::BOT::CUB3D();
            break;
        case INCEPTION:
            buffer = RPL::BOT::INCEPTION();
            break;
        default:
            buffer = RPL::BOT::ERROR(message);
            break;
        }
    }

    void PRIVMSG(Server &server, Client &executor, Message &message)
    {
        std::string message_buffer;
        std::string buffer;

		if (message.getParams().size() < 2)
		{
			buffer = RPL::PRIVMSG::ERR_461(executor);
            executor.setOutBuffer(buffer);
            return;
		}

        std::string target_name = message.getParam(0);

        for (size_t i = 1; i < message.getParams().size(); ++i)
        {
            if (i != 1)
                message_buffer += " ";
            message_buffer += message.getParam(i);
        }

        if (target_name == "#bot")
        {
            handleBotMsg(message_buffer, buffer);
            executor.setOutBuffer(buffer);
            return;
        }

        if (target_name[0] != '#')
        {
            std::string &client_nick = target_name;
            if (!server.isClient(client_nick))
            {
                buffer = RPL::PRIVMSG::ERR_401(executor, message);
                executor.setOutBuffer(buffer);
            }
            else
            {
                buffer = RPL::PRIVMSG::SUCCESS_TO_CLIENT(executor, message, message_buffer);
                Client *target_client = server.getClient(client_nick);
                target_client->setOutBuffer(buffer);
            }
        }
        else
        {
            std::string &channel_name = target_name;
            if (!server.isChannel(channel_name))
            {
                buffer = RPL::PRIVMSG::ERR_403(executor, message);
                executor.setOutBuffer(buffer);
            }
            else
            {
                Channel &channel = server.getChannel(channel_name);
                if (!channel.isClient(executor.getNick()))
                {
                    buffer = RPL::PRIVMSG::ERR_404(executor, message);
                    executor.setOutBuffer(buffer);
                }
                else
                {
                    buffer = RPL::PRIVMSG::SUCCESS_TO_CHANNEL(executor, message, message_buffer);
                    std::cout << "channel_name in PRIVMSG: " << channel_name << std::endl;
                    channel.toAllSetOutBuffer(buffer, executor.getNick());
                }
            }
        }
    }
}
