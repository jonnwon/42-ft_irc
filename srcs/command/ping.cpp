#include "Server.hpp"

namespace Command
{
    void PING(Server &server, Client &executor, Message &message)
    {
        (void)server;
        std::string buffer = RPL::PING::SUCCESS(message);
        executor.setOutBuffer(buffer);
    }
}
