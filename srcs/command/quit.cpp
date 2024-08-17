#include "Server.hpp"

namespace Command
{
    void QUIT(int client_fd, Server &server, Client &executor, Message &message)
    {
        std::string buffer_to_executor = RPL::QUIT::SUCCESS_TO_EXECUTOR(executor, message);
        std::string buffer_to_channel = RPL::QUIT::SUCCESS_TO_CHANNEL(executor, message);
        executor.setOutBuffer(buffer_to_executor);
        server.sendQuitMessage(executor, buffer_to_channel);
        (void)client_fd;
    }
}
