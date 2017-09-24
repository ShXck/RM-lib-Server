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

	/**
	 * Manda la información de sincronización al servidor HA.
	 * @param key la llave del valor.
	 * @param data el valor del recurso.
	 * @param client_id la identificación del cliente.
	 * @param size el tamaño del recurso.
	 * @param instruction la instrucción que se quiere.
	 * @param passive_socket el socket del servidor pasivo.
	 * @param encrypter el encriptador de datos.
	 */
	void synchronize( std::string key, char* data, char* client_id, int size,  int instruction, sf::TcpSocket* passive_socket, Encrypter* encrypter ) {
		sf::Packet sync_packet;
		sync_packet << encrypter->apply( JSON_Handler::build_sync_data( key.c_str(), data, client_id, size, instruction ) );
		passive_socket->send( sync_packet );
	}
};

class Reader {
public:
	Reader();
	/**
	 * Lee la información entrante.
	 * @param packet el paquete con la iformación.
	 * @param socket el socket del emisor.
	 * @param handler en manejador de memoria.
	 * @param passive_socket el socket del servidor HA.
	 */
	void read( sf::Packet packet, sf::TcpSocket* socket, Memory_Handler* handler, sf::TcpSocket* passive_socket );
	/**
	 * Lee la información entrante del servidor principal.
	 * @param message la información.
	 * @param handler el manejador de memoria.
	 */
	void read( std::string message, Memory_Handler* handler );
	/**
	 * @return el encriptador
	 */
	Encrypter& enrypter();
	virtual ~Reader();
private:
	/**
	 * Procesa la instrucción y los datos entrantes.
	 * @param instruction la acción que se va a hacer.
	 * @param data la informacioń.
	 * @param handler el manejador de memoria.
	 * @param passive_socket el socket del servidor pasivo.
	 * @return
	 */
	std::string process( int instruction, std::string data, Memory_Handler* handler, sf::TcpSocket* passive_socket );
private:
	Encrypter _encrypter;
	Synchronizer _synchronizer;
};

#endif /* SERVER_H_READER_H_ */
