#include "print.hpp"

namespace Print
{
	void printMessages(std::vector<Message> &messages)
	{
		for (std::vector<Message>::size_type i = 0; i < messages.size(); i++)
		{
			std::cout << i << " 번째 메세지의 cmd: " << messages[i].getCmd() << std::endl;
			for (std::vector<Message>::size_type j = 0; j < messages[i].getParams().size(); j++)
				std::cout << i << " 번째 메세지의 " << j << "번째 인자: " << messages[i].getParam(j) << std::endl;
			std::cout << "----------------" << std::endl;
		}
	}
	
	void printClientBook(std::map<int, Client> myMap)
	{
		std::map<int, Client>::iterator it;

		std::cout << "======printClientBook======" << std::endl;
		for (it = myMap.begin(); it != myMap.end(); ++it)
		{
			std::cout << "[fd] : " << it->first << std::endl;
			std::cout << "nickName: " << it->second.getNick() << std::endl;
			std::cout << "userName: " << it->second.getUser() << std::endl;
			std::cout << "serverName: " << it->second.getServer() << std::endl;
			std::cout << "------------------" << std::endl;
		}
	}

	void printChannel(Channel &channel)
	{
		std::cout << "==========printChannel==========" << std::endl;

		std::cout << "Channel name: " << channel.getName() << std::endl;
		std::cout << "Channel topic: " << channel.getTopic() << std::endl;
		std::cout << "Channel password: " << channel.getPassword() << std::endl;
		std::cout << "Channel mode: " << channel.getMode() << std::endl;

		std::cout << "---client list---" << std::endl;
		std::vector<std::pair<Client, e_auth> >::const_iterator it;
		std::cout << channel.getClientListStr() << std::endl;


	}

	void printClients(std::vector<Client> clients)
	{
		std::vector<Client>::iterator it;

		std::cout << "=====printClients=====" << std::endl;
		for (it = clients.begin(); it != clients.end(); ++it)
		{
			std::cout << "nickName: " << it->getNick() << std::endl;
			std::cout << "userName: " << it->getUser() << std::endl;
			std::cout << "serverName: " << it->getServer() << std::endl;
			std::cout << "------------------" << std::endl;
		}
	}
}
