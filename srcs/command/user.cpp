#include "Server.hpp"

namespace Command
{
    void USER(Server &server, Client &executor, Message &message)
    {
        (void)server;
		std::string buffer;

		if (message.getParams().size() < 4)
		{
			buffer = RPL::USER::ERR_461(executor);
			executor.setOutBuffer(buffer);
			return;
		}

        executor.setUser(message.getParam(0));
        executor.setServer(message.getParam(2));
    }
}
