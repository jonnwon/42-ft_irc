#include "Server.hpp"

namespace Command
{
    void NICK(Server &server, Client &executor, Message &message)
    {
        std::string buffer;

		if (message.getParams().size() < 1)
		{
			buffer = RPL::NICK::ERR_461(executor);
			executor.setOutBuffer(buffer);
			return;
		}

        std::string nick_name = message.getParam(0);

        if (server.isClient(nick_name))
            buffer = RPL::NICK::ERR_433(executor, message);
        else
        {
            if (!executor.getIsRegister())
            {
                executor.setNickName(message.getParam(0));
                return;
            }
            buffer = RPL::NICK::SUCCESS(executor, message);
            executor.setNickName(message.getParam(0));
        }
        executor.setOutBuffer(buffer);
    }
}
