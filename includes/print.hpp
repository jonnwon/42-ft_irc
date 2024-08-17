#ifndef PRINT_HPP
#define PRINT_HPP

#include "Server.hpp"
#include "Channel.hpp"
#include "Client.hpp"

namespace Print
{
	void printMessages(std::vector<Message> &messages);
	void printClientBook(std::map<int, Client> myMap);
	void printChannel(Channel &channel);
	void printClients(std::vector<Client> clients);
}

#endif
