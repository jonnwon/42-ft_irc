#include "Server.hpp"

namespace Command
{
    void execMODE_pI(Channel &channel, Client &executor, std::string &buffer)
    {
        channel.setMode(MODE_I); 
        channel.toAllSetOutBuffer(buffer, executor.getNick());
    }

    void execMODE_mI(Channel &channel, Client &executor, std::string &buffer)
    {
        channel.unsetMode(MODE_I);
        channel.toAllSetOutBuffer(buffer, executor.getNick());
    }

    void execMODE_pT(Channel &channel, Client &executor, std::string &buffer)
    {
        channel.setMode(MODE_T);
        channel.toAllSetOutBuffer(buffer, executor.getNick());
    }

    void execMODE_mT(Channel &channel, Client &executor, std::string &buffer)
    {
        channel.unsetMode(MODE_T);
        channel.toAllSetOutBuffer(buffer, executor.getNick());
    }

    void execMODE_pK(Channel &channel, Client &executor, std::string &buffer, Message &message)
    {
        channel.setMode(MODE_K);
        channel.setPassword(message.getParam(2)); 
        channel.toAllSetOutBuffer(buffer, executor.getNick());
    }

    void execMODE_mK(Channel &channel, Client &executor, std::string &buffer, Message &message)
    {
        (void)message;
        channel.unsetMode(MODE_K);
        channel.unsetPassword(); 
        channel.toAllSetOutBuffer(buffer, executor.getNick());
    }

    void execMODE_pO(Channel &channel, Client &executor, std::string &buffer, Message &message)
    {
        channel.setOperator(message.getParam(2));
        channel.toAllSetOutBuffer(buffer, executor.getNick());
    }

    void execMODE_mO(Channel &channel, Client &executor, std::string &buffer, Message &message)
    {
        channel.unsetOperator(message.getParam(2));
        channel.toAllSetOutBuffer(buffer, executor.getNick());
    }

    void execMODE_pL(Channel &channel, Client &executor, std::string &buffer, Message &message)
    {
        channel.setMode(MODE_L);
        channel.setMaxClient(message.getParam(2));
        channel.toAllSetOutBuffer(buffer, executor.getNick());
    }

    void execMODE_mL(Channel &channel, Client &executor, std::string &buffer, Message &message)
    {
        (void)message;
        channel.unsetMode(MODE_L); 
        channel.toAllSetOutBuffer(buffer, executor.getNick());
    }

    void MODE(Server &server, Client &executor, Message &message)
    {
        std::time_t currentTime = std::time(NULL);
        std::stringstream ss;
        ss << currentTime;

        std::string buffer = "";
        std::string buffer_mode;

		if (message.getParams().size() < 1)
		{
			buffer = RPL::MODE::ERR_461(executor);
			executor.setOutBuffer(buffer);
			return;
		}

        std::string channel_name = message.getParam(0);

        if (message.getParams().size() < 2)
            return;
        buffer_mode = message.getParam(1);
        if (channel_name[0] != '#')
            buffer = RPL::MODE::ERR_300(executor, message);
        else if (!server.isChannel(channel_name))
            buffer = RPL::MODE::ERR_403(executor, message);
        else if (!Parsing::isValidModeArgument(buffer_mode))
            buffer = RPL::MODE::ERR_300(executor, message);
        else
        {
            Channel &channel = server.getChannel(channel_name);
            check_Mode mode = Check::getModeToEnum(buffer_mode);
            if (channel.getAuthority(executor.getNick()) != OPERATOR)
                buffer = RPL::MODE::ERR_482(executor, message);
            else if (Check::executableMode(server, channel, message, mode, buffer, executor) == false)
            {
                executor.setOutBuffer(buffer);
                return ;
            }
            else
            {
                switch (mode)
                {
                case Mode_plus_I:
                    buffer = RPL::MODE_pI::SUCCESS(executor, message);
                    Command::execMODE_pI(channel, executor, buffer);
                    break;

                case Mode_minus_I:
                    buffer = RPL::MODE_mI::SUCCESS(executor, message);
                    Command::execMODE_mI(channel, executor, buffer);
                    break;

                case Mode_plus_T:
                    buffer = RPL::MODE_pT::SUCCESS(executor, message);
                    Command::execMODE_pT(channel, executor, buffer);
                    break;

                case Mode_minus_T:
                    buffer = RPL::MODE_mT::SUCCESS(executor, message);
                    Command::execMODE_mT(channel, executor, buffer);
                    break;

                case Mode_plus_K:
                    buffer = RPL::MODE_pK::SUCCESS(executor, message);
                    Command::execMODE_pK(channel, executor, buffer, message);
                    break;

                case Mode_minus_K:
                    buffer = RPL::MODE_mK::SUCCESS(executor, message);
                    Command::execMODE_mK(channel, executor, buffer, message);
                    break;

                case Mode_plus_O:
                    buffer = RPL::MODE_pO::SUCCESS(executor, message);
                    Command::execMODE_pO(channel, executor, buffer, message);
                    break;

                case Mode_minus_O:
                    buffer = RPL::MODE_mO::SUCCESS(executor, message);
                    Command::execMODE_mO(channel, executor, buffer, message);
                    break;

                case Mode_plus_L:
                    buffer = RPL::MODE_pL::SUCCESS(executor, message);
                    Command::execMODE_pL(channel, executor, buffer, message);
                    break;

                case Mode_minus_L:
                    buffer = RPL::MODE_mL::SUCCESS(executor, message);
                    Command::execMODE_mL(channel, executor, buffer, message);
                    break;

                default:
                    break;
                }
            }
        }
        executor.setOutBuffer(buffer);
    }
}
