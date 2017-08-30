#ifndef SERVER_H_READER_H_
#define SERVER_H_READER_H_

#define NEW_INSTR 1
#define GET_INSTR 2
#define DEL_INSTR 3
#define GET_SET_INSTR 4
#define REPLC_INSTR 5
#define DISCONNECT_INSTR 6
#define CHECK_INSTR 8

#include <string>
#include <iostream>
#include <SFML/Network.hpp>
#include "Encrypter.h"
#include "JSONHandler.h"
#include "../error_handler.hpp"
#include "../data_structs/Map.h"
#include "../memory_h/MemoryHandler.h"

struct Synchronizer {

	void synchronize( std::string key, char* data, char* client_id, int size,  int instruction, sf::TcpSocket* passive_socket, Encrypter* encrypter ) {
		sf::Packet sync_packet;
		sync_packet << encrypter->apply( JSON_Handler::build_sync_data( key.c_str(), data, client_id, size, instruction ) );
		passive_socket->send( sync_packet );
	}
};

class Reader {
public:
	Reader();
	void read( sf::Packet packet, sf::TcpSocket* socket, Memory_Handler* handler, sf::TcpSocket* passive_socket );
	void read( std::string message, Memory_Handler* handler );
	Encrypter& enrypter();
	virtual ~Reader();
private:
	std::string process( int instruction, std::string data, Memory_Handler* handler, sf::TcpSocket* passive_socket );
private:
	Encrypter _encrypter;
	Synchronizer _synchronizer;
};

#endif /* SERVER_H_READER_H_ */
