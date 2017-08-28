#include "Reader.h"

Reader::Reader( sf::TcpSocket* p_socket ) : passive_socket( p_socket ) {}

void Reader::read( sf::Packet packet, sf::TcpSocket* socket, Memory_Handler* handler ) {

	std::string _request;
	if( packet >> _request ) {

		std::string d_request = _encrypter.apply( _request );

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
		case NEW_INSTR: {
			std::string _val = JSON_Handler::get_value( data.c_str(), "value" ).GetString();
			int _size = JSON_Handler::get_value( data.c_str(), "size" ).GetInt();
			std::string c_id = JSON_Handler::get_value( data.c_str(), "id" ).GetString();
			return_msg = handler->store_value( _key, strdup( _val.c_str() ), strdup( c_id.c_str() ), _size );
			//_synchronizer.synchronize( _key, strdup( _val.c_str() ), strdup( c_id.c_str() ), _size, instruction, socket, &_encrypter );
			break;
		}
		case GET_INSTR: {
			return_msg = handler->find_value( _key );
			break;
		}
		case DEL_INSTR: {
			return_msg = handler->delete_value( _key );
			//_synchronizer.synchronize( _key, "", "", 0, instruction, socket, &_encrypter );
			break;
		}
		case GET_SET_INSTR: {
			return_msg = handler->find_value_set( strdup( data.c_str() ) );
			break;
		}
		case REPLC_INSTR: {
			std::string new_data = JSON_Handler::get_value( data.c_str(), "new_value" ).GetString();
			return_msg = handler->replace_value( _key, strdup( new_data .c_str() ) );
			//_synchronizer.synchronize( _key, strdup( new_data.c_str() ), "", 0, instruction, socket, &_encrypter );
			break;
		}
		case DISCONNECT_INSTR: {
			handler->delete_from( strdup( _key.c_str() ) );
			break;
		}

		case SYNC_INSTR: {
			std::string _val = JSON_Handler::get_value( data.c_str(), "value" ).GetString();
			int _size = JSON_Handler::get_value( data.c_str(), "size" ).GetInt();
			std::string c_id = JSON_Handler::get_value( data.c_str(), "id" ).GetString();
			int handler_instruction = JSON_Handler::get_value( data.c_str(), "memory_instruction" ).GetInt();
			handler->sync_data( _key, strdup( _val.c_str() ), strdup( c_id.c_str() ), _size, handler_instruction );
		}
	}
	return return_msg;
}

Reader::~Reader() { }

