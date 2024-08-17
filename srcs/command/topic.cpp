#include "Server.hpp"

namespace Command
{
    void TOPIC(Server &server, Client &executor, Message &message)
    {
        std::string buffer;

		if (message.getParams().size() < 1)
		{
			buffer = RPL::TOPIC::ERR_461(executor);
			executor.setOutBuffer(buffer);
			return;
		}

        Channel &channel = server.getChannel(message.getParam(0));

		if (server.isChannel(channel.getName()) == false)
		{
			buffer = RPL::TOPIC::ERR_403(executor, message);
			executor.setOutBuffer(buffer);
			return;
		}

		if (channel.getTopic() == "" && message.getParams().size() == 1)
		{
			buffer = RPL::TOPIC::ERR_331(executor, message);
			executor.setOutBuffer(buffer);
			return;
		}

		if (channel.getTopic() != "" && message.getParams().size() ==1)
		{
			buffer = RPL::TOPIC::SUCCESS_2(executor, message, channel.getTopic());
			executor.setOutBuffer(buffer);
			return;
		}

		if (message.getParams().size() > 1 && channel.isClient(executor.getNick()) == false)
		{
			buffer = RPL::TOPIC::ERR_442(executor, message);
			executor.setOutBuffer(buffer);
			return;
		}

        std::string target_topic = message.getParam(1);
		if (!target_topic.empty() && target_topic[0] == ':')
			target_topic = target_topic.substr(1);

        if (channel.checkMode(MODE_T) && channel.getAuthority(executor.getNick()) != OPERATOR) 
            buffer = RPL::TOPIC::ERR_482(executor, message);
        else if (channel.checkMode(MODE_T) && channel.getAuthority(executor.getNick()) == OPERATOR && channel.getTopic() == target_topic)
            buffer = RPL::NO_REPLY();
        else if (channel.checkMode(MODE_T) == false && channel.getTopic() == target_topic)
            buffer = RPL::NO_REPLY();
        else
        {
            channel.setTopic(target_topic);
            buffer = RPL::TOPIC::SUCCESS(executor, message, target_topic);
            channel.toAllSetOutBuffer(buffer, executor.getNick());
        }
        executor.setOutBuffer(buffer);
    }
}
