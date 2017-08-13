#include "Reader.h"

Reader::Reader() {}

void Reader::read( sf::Packet packet, sf::TcpSocket* socket, Memory_Handler* handler ) {

	std::string _request;
	if( packet >> _request ) {

		std::string d_request = _encrypter.apply( _request );    // Decrypts the message

		std::cout << d_request << std::endl;

		std::string _response = process( JSON_Handler::get_value( d_request.c_str(), "instruction" ).GetInt(), d_request, handler );

		sf::Packet response_packet;
		response_packet << _encrypter.apply( _response );
		socket->send( response_packet );
	}
}

std::string Reader::process( int instruction, std::string data, Memory_Handler* handler ) {

	std::string return_msg;

	std::string _key = JSON_Handler::get_value( data.c_str(), "key" ).GetString();

	switch( instruction ) {
		case 1: {
			std::string _val = JSON_Handler::get_value( data.c_str(), "value" ).GetString();
			int _size = JSON_Handler::get_value( data.c_str(), "size" ).GetInt();
			return_msg = handler->store_value( _key, _val, _size );
			break;
		}
		case GET_INSTR: {
			return_msg = handler->find_value( _key );
			break;
		}
		case DEL_INSTR: {

			break;
		}
	}

	return return_msg;
}

Reader::~Reader() { }
