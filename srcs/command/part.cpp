#include "Server.hpp"

namespace Command
{
    void PART(Server &server, Client &executor, Message &message)
    {
        std::string buffer;
        if (message.getParams().size() < 1)
        {
            buffer = RPL::PART::ERR_461(executor);
            executor.setOutBuffer(buffer);
            return;
        }
        std::string channel_name = message.getParam(0);
        if (server.isChannel(channel_name) == false)
        {
            buffer = RPL::PART::ERR_403(executor, message);
            executor.setOutBuffer(buffer);
            return;
        }
        Channel &channel = server.getChannel(channel_name);
        if (channel.isClient(executor.getNick()) == false)
        {
            buffer = RPL::PART::ERR_422(executor, message);
            executor.setOutBuffer(buffer);
            return;
        }

        buffer = RPL::PART::SUCCESS(executor, message);
        channel.exitChannel(executor);
        if (channel.getClientNum() == 0)
        {
            server.eraseChannel(channel_name);
            executor.setOutBuffer(buffer);
            return;
        }
        executor.setOutBuffer(buffer);
        if (channel_name == "#bot")
            return;
        channel.toAllSetOutBuffer(buffer, executor.getNick());
    }
}
