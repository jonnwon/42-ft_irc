#include "Server.hpp"

namespace Command
{
    void INVITE(Server &server, Client &executor, Message &message)
    {
        std::string buffer;

		
		if (message.getParams().size() < 2)
		{
			buffer = RPL::INVITE::ERR_461(executor);
			executor.setOutBuffer(buffer);
			return;
		}

        std::string invited_nick_name = message.getParam(0);
        std::string channel_name = message.getParam(1);

        if (!server.isClient(invited_nick_name))
        {
            buffer = RPL::INVITE::ERR_401(executor, message);
        }
        else if (!server.isChannel(channel_name))
        {
            
            buffer = RPL::INVITE::ERR_403(executor, message);
        }
        else
        { 
            Channel &channel = server.getChannel(channel_name);
            if (!channel.isClient(executor.getNick())) 
            {
                buffer = RPL::INVITE::ERR_442(executor, message);
            }
            else if (channel.isClient(invited_nick_name)) 
            {
                buffer = RPL::INVITE::ERR_443(executor, message);
            }
            else if (channel.getAuthority(executor.getNick()) != OPERATOR)
            {
                buffer = ":" + executor.getServer() + " 482 " + executor.getNick() + " " + channel_name + " :You must be a channel operator\r\n";
            }
            else
            {
                buffer = RPL::INVITE::SUCCESS_TO_EXECUTOR(executor, message);
                std::string buffer_to_client = RPL::INVITE::SUCCESS_TO_INVITED_CLIENT(executor, message);
                server.getClient(invited_nick_name)->setOutBuffer(buffer_to_client);
                std::string buffer_to_channel = RPL::INVITE::SUCCESS_TO_CHANNEL(executor, message);
                Channel &channel = server.getChannel(channel_name);
                channel.toAllSetOutBuffer(buffer_to_channel, executor.getNick());
                channel.setInvitedList(invited_nick_name);
            }
        }
        executor.setOutBuffer(buffer);
    }
}
