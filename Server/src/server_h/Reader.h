#ifndef SERVER_H_READER_H_
#define SERVER_H_READER_H_

#define NEW_INSTR 1
#define GET_INSTR 2
#define DEL_INSTR 3
#define GET_SET_INSTR 4
#define REPLC_INSTR 5

#include <string>
#include <iostream>
#include <SFML/Network.hpp>
#include "Encrypter.h"
#include "JSONHandler.h"
#include "../error_handler.hpp"
#include "../data_structs/Map.h"
#include "../memory_h/MemoryHandler.h"

class Reader {
public:
	Reader();
	void read( sf::Packet packet, sf::TcpSocket* socket, Memory_Handler* handler );
	virtual ~Reader();
private:
	std::string process( int instruction, std::string data, Memory_Handler* handler );
private:
	Encrypter _encrypter;
};

#endif /* SERVER_H_READER_H_ */
