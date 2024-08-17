#include "Server.hpp"

namespace Command
{
    void KICK(Server &server, Client &executor, Message &message)
    {
        std::string channel_name = "";
        std::string kicked_name = "";
        std::string buffer;

		if (message.getParams().size() < 2)
		{
			buffer = RPL::KICK::ERR_461(executor);
            executor.setOutBuffer(buffer);
            return;
		}

        for (size_t i = 0; i < message.getParams().size(); ++i)
        {
            if (i == 0)
                channel_name = message.getParam(0);
            if (i == 1)
                kicked_name = message.getParam(1);
        }

        if (!server.isChannel(channel_name))
        {
            buffer = RPL::KICK::ERR_403(executor, message);
            executor.setOutBuffer(buffer);
            return;
        }

        if (!server.isClient(kicked_name))
        {
            buffer = RPL::KICK::ERR_401(executor, message);
            executor.setOutBuffer(buffer);
            return;
        }

        Channel &channel = server.getChannel(channel_name);
        if (!channel.isClient(kicked_name))
        {
            buffer = RPL::KICK::ERR_441(executor, message);
            executor.setOutBuffer(buffer);
            return;
        }

        if (!channel.isClient(executor.getNick()))
        {
            buffer = RPL::KICK::ERR_442(executor, message);
            executor.setOutBuffer(buffer);
            return;
        }

        if (channel.getAuthority(executor.getNick()) != OPERATOR)
        {

            buffer = RPL::KICK::ERR_482(executor, message);
            executor.setOutBuffer(buffer);
            return;
        }

        buffer = RPL::KICK::SUCCESS(executor, message);
        executor.setOutBuffer(buffer);
        channel.toAllSetOutBuffer(buffer, executor.getNick());
        channel.exitChannel(*(server.getClient(kicked_name)));
    }
}
