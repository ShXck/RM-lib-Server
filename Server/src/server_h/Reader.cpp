#include "Reader.h"

Reader::Reader() {}

void Reader::read( sf::Packet packet, sf::TcpSocket* socket, Memory_Handler* handler, sf::TcpSocket* passive_socket ) {

	std::string _request;
	if( packet >> _request ) {

		std::string d_request = _encrypter.apply( _request );

		std::cout << d_request << std::endl;

		std::string _response = process( JSON_Handler::get_value( d_request.c_str(), "instruction" ).GetInt(), d_request, handler, passive_socket );

		sf::Packet response_packet;
		response_packet << _encrypter.apply( _response );
		socket->send( response_packet );
	}
}

std::string Reader::process( int instruction, std::string data, Memory_Handler* handler, sf::TcpSocket* passive_socket ) {

	std::string return_msg;

	std::string _key = JSON_Handler::get_value( data.c_str(), "key" ).GetString();

	switch( instruction ) {
		case NEW_INSTR: {
			std::string _val = JSON_Handler::get_value( data.c_str(), "value" ).GetString();
			int _size = JSON_Handler::get_value( data.c_str(), "size" ).GetInt();
			std::string c_id = JSON_Handler::get_value( data.c_str(), "id" ).GetString();
			return_msg = handler->store_value( _key, strdup( _val.c_str() ), strdup( c_id.c_str() ), _size );
			_synchronizer.synchronize( _key, strdup( _val.c_str() ), strdup( c_id.c_str() ), _size, instruction, passive_socket, &_encrypter );
			break;
		}
		case GET_INSTR: {
			return_msg = handler->find_value( _key );
			break;
		}
		case DEL_INSTR: {
			return_msg = handler->delete_value( _key );
			_synchronizer.synchronize( _key, strdup( "" ), strdup( "" ) , 0, instruction, passive_socket, &_encrypter );
			break;
		}
		case GET_SET_INSTR: {
			return_msg = handler->find_value_set( strdup( data.c_str() ) );
			break;
		}
		case REPLC_INSTR: {
			std::string new_data = JSON_Handler::get_value( data.c_str(), "new_value" ).GetString();
			return_msg = handler->replace_value( _key, strdup( new_data .c_str() ) );
			_synchronizer.synchronize( _key, strdup( new_data.c_str() ), strdup( "" ), 0, instruction, passive_socket, &_encrypter );
			break;
		}
		case DISCONNECT_INSTR: {
			handler->delete_from( strdup( _key.c_str() ) );
			_synchronizer.synchronize( "", strdup( "" ), strdup( _key.c_str() ), 0, instruction, passive_socket, &_encrypter );
			break;
		}
		case CHECK_INSTR: {
			return_msg = data;
			break;
		}
	}
	return return_msg;
}

void Reader::read( std::string message, Memory_Handler* handler ) {  // { key, data, client_id, size, instruction }

	std::cout << message << std::endl;

	std::string decrypted_msg = _encrypter.apply( message );

	int _instruction = JSON_Handler::get_value( decrypted_msg.c_str(), "instruction" ).GetInt();
	std::string _key = JSON_Handler::get_value( decrypted_msg.c_str(), "key" ).GetString();

	switch( _instruction ) {
		case NEW_INSTR: {
			std::string _data = JSON_Handler::get_value( decrypted_msg.c_str(), "value" ).GetString();
			std::string c_id = JSON_Handler::get_value( decrypted_msg.c_str(), "client_id" ).GetString();
			int _size = JSON_Handler::get_value( decrypted_msg.c_str(), "size" ).GetInt();
			handler->store_value( _key, strdup( _data.c_str() ), strdup( c_id.c_str() ), _size );
			break;
		}
		case DEL_INSTR: {
			handler->delete_value( _key );
			break;
		}
		case REPLC_INSTR: {
			std::string _data = JSON_Handler::get_value( decrypted_msg.c_str(), "value" ).GetString();
			handler->replace_value( _key, strdup( _data.c_str() ) );
			break;
		}
		case DISCONNECT_INSTR: {
			std::string c_id = JSON_Handler::get_value( decrypted_msg.c_str(), "client_id" ).GetString();
			handler->delete_from( strdup( c_id.c_str() ) );
			break;
		}
	}
}

Encrypter& Reader::enrypter() {
	return _encrypter;
}

Reader::~Reader() { }

