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
#include <chrono>
#include <thread>
#include <future>

class Server {
public:
	Server( int mode, bool run_checker );
	/**
	 * Ejecución del servidor principal.
	 */
	void run();
	virtual ~Server();
private:
	/**
	 * Cambia el estado del servidor de pasivo a activo.
	 */
	void switch_to_active();
	/**
	 * Inicia el servidor en modo pasivo.
	 */
	void connect_as_passive();
	/**
	 * Ejecución del servidor pasivo.
	 */
	void run_passive();
	/**
	 * Corre el verificador de estado del servidor pasivo.
	 */
	void run_checker();
	/**
	 * Espera por la respuesta de la verificaión.
	 */
	void wait_for_response();
private:
	sf::TcpListener _listener;
	sf::SocketSelector _selector;
	sf::TcpSocket passive_socket;
	std::vector< sf::TcpSocket* > active_clients;
	Reader _reader;
	Memory_Handler _handler;
	bool is_passive;
	std::future< void > checker_time_handler;
};


#endif /* SERVER_H_SERVER_H_ */
