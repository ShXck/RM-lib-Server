#include "Server.h"

Server::Server( int mode ) : is_passive( false ) {

	switch( mode ) {
		case 0: {
			_listener.listen( PORT_M );
			_selector.add( _listener );
			break;
		}
		case 1: {
			connect_as_passive();
			break;
		}
	}
}

void Server::run() {
	std::cout << "Server Running" << std::endl;

	while ( true ) {
		if( _selector.wait() ) {
			if( _selector.isReady( _listener ) ) {
				sf::TcpSocket *_socket = new sf::TcpSocket;
				_listener.accept( *_socket );
				active_clients.push_back( _socket );
				_selector.add( *_socket );
				std::cout << "New app online" << std::endl;
			} else {
				for( unsigned int i = 0; i < active_clients.size(); i++ ) {
					if( _selector.isReady( *active_clients[i] ) ){
						sf::Packet _packet;
						if( active_clients[i]->receive( _packet ) == sf::Socket::Done ) {
							_reader.read( _packet, active_clients[i], &_handler, active_clients[0] );
						}
					}
				}
			}
		}
	}

	for( std::vector<sf::TcpSocket*>::iterator it = active_clients.begin(); it != active_clients.end(); it++ ) {
		delete *it;
	}
}

void Server::connect_as_passive() {
	sf::IpAddress _address = sf::IpAddress::getLocalAddress();
	passive_socket.setBlocking( false );
	passive_socket.connect( _address, PORT_M );
	//_checker.set_sender( passive_socket );
	//_checker.check_status( &_reader.enrypter() );
	is_passive = true;
	run_passive();
	_checker.check_status(); //TODO: Test if it's sending the message
}

/*void Server::switch_to_active() {
	passive_socket->disconnect();
	_listener.listen( PORT_HA );
	_selector.add( _listener );
	run();
}*/

void Server::run_passive() {

	std::cout << "RUNNING PASSIVE" << std::endl;

	sf::Packet _packet;
	std::string _message;

	while( is_passive ) {
		if( passive_socket.receive( _packet ) == sf::Socket::Done ) {
			if( _packet >> _message ) {
				_reader.read( _message, &_handler );
			}
		}
	}
}

Server::~Server() { }

