#include "Server.hpp"

namespace Command
{
    void PASS(Server &server, Client &executor, Message &message)
    {
		std::string buffer;

		if (message.getParams().size() < 1)
		{
			buffer = RPL::PASS::ERR_461(executor);
			executor.setOutBuffer(buffer);
			return;
		}

        if (executor.getCheckPassWord())
            return;
        if (message.getParam(0) != server.getPassWord())
            throw(std::logic_error("invalid password"));
        executor.setCheckPassword(true);
    }
}
