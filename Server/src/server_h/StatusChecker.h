#ifndef SERVER_H_STATUSCHECKER_H_
#define SERVER_H_STATUSCHECKER_H_

#define CHECK_PERIOD 60

#include <chrono>
#include <thread>
#include <future>
#include <SFML/Network.hpp>
#include "Encrypter.h"
#include "JSONHandler.h"

class Status_Checker {
public:
	Status_Checker( sf::TcpSocket* sender, bool run );
	void check_status();
	void set_main_status( bool is_working );
	bool get_main_status() const;
	void check_response( std::string* response );
	virtual ~Status_Checker();
private:
	std::future< void > checker_time_handler;
	sf::TcpSocket* sender_socket;
	Encrypter _encrypter;
	bool is_main_working;
};

#endif /* SERVER_H_STATUSCHECKER_H_ */
