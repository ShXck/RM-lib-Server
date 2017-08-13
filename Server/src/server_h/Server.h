#ifndef SERVER_H_SERVER_H_
#define SERVER_H_SERVER_H_

#define PORT_M 8000
#define PORT_HA 7500

#include <SFML/Network.hpp>
#include "Reader.h"
#include <iostream>
#include <string>
#include <vector>
#include "../memory_h/MemoryHandler.h"


class Server {
public:
	Server();
	void run();
	void send( sf::TcpSocket& socket, std::string data );
	virtual ~Server();
private:
	sf::TcpListener _listener;
	sf::SocketSelector _selector;
	std::vector<sf::TcpSocket*> active_clients;
	Reader _reader;
	Memory_Handler _handler;
};

#endif /* SERVER_H_SERVER_H_ */
