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
#include "StatusChecker.h"

class Server {
public:
	Server( int mode, bool run_checker );
	void run();
	virtual ~Server();
private:
	void switch_to_active();
	void connect_as_passive();
	void run_passive();
private:
	sf::TcpListener _listener;
	sf::SocketSelector _selector;
	sf::TcpSocket passive_socket;
	std::vector< sf::TcpSocket* > active_clients;
	Reader _reader;
	Memory_Handler _handler;
	Status_Checker _checker;
	bool is_passive;
};

#endif /* SERVER_H_SERVER_H_ */
