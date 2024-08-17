#include "Server.hpp"

namespace Command
{
    static void handleJoinSuccess(Channel &channel, Client &executor, e_auth auth, Message &message)
    {
        channel.joinChannel(executor, auth);
        std::string buffer = RPL::JOIN::SUCCESS(executor, message);
        channel.toAllSetOutBuffer(buffer, executor.getNick());
        if (channel.getTopic() != "")
            buffer += RPL::JOIN::SUCCESS_332(executor, message, channel.getTopic());
        buffer += RPL::JOIN::SUCCESS_353_366(executor, message, channel.getClientListStr());
        executor.setOutBuffer(buffer);
    }

    void JOIN(Server &server, Client &executor, Message &message)
    {
        std::string buffer;
        if (!executor.getIsRegister())
        {
            buffer = RPL::JOIN::ERR_451(executor);
            executor.setOutBuffer(buffer);
            return;
        }
		
		if (message.getParams().size() < 1)
		{
			buffer = RPL::JOIN::ERR_461(executor);
			executor.setOutBuffer(buffer);
			return;
		}

        std::string channel_name = message.getParam(0);

        if (channel_name == "#bot")
        {
            if (!server.isChannel(channel_name))
                server.addChannel(channel_name);
			Channel &channel = server.getChannel(channel_name);
            channel.joinChannel(executor, REGULAR);
            buffer = RPL::JOIN::SUCCESS(executor, message);
            executor.setOutBuffer(buffer);
            return;
        }

        if (channel_name[0] != '#')
		{
			buffer = RPL::JOIN::ERR_476(executor, message);
			executor.setOutBuffer(buffer);
			return;
		}

        e_auth auth_ = REGULAR;
        if (!server.isChannel(channel_name))
        {
            server.addChannel(channel_name);
            auth_ = OPERATOR;
        }
        else
        {
			Channel &channel = server.getChannel(channel_name);

			if (channel.isClient(executor.getNick()))
			{
				buffer = RPL::NO_REPLY();
				executor.setOutBuffer(buffer);
				return;
			}
            if (Check::invitedList(channel, executor.getNick()))
            {
                channel.unsetInvitedList(executor.getNick());
                handleJoinSuccess(channel, executor, auth_, message);
                return;
            }
            if (channel.checkMode(MODE_K) && (message.getParams().size() != 2 || channel.getPassword() != message.getParam(1)))
            {
                buffer = RPL::JOIN::ERR_475(executor, message);
                executor.setOutBuffer(buffer);
                return;
            }

            if (channel.checkMode(MODE_I) && Check::invitedList(channel, executor.getNick()) == false)
            {
                buffer = RPL::JOIN::ERR_473(executor, message);
                executor.setOutBuffer(buffer);
                return;
            }
            if (channel.checkMode(MODE_L) && channel.getClientNum() >= channel.getMaxClient())
            {
                buffer = RPL::JOIN::ERR_471(executor, message);
                executor.setOutBuffer(buffer);
                return;
            }

        }
		Channel &channel = server.getChannel(channel_name);
        handleJoinSuccess(channel, executor, auth_, message);
        Print::printChannel(channel);
    }
}
