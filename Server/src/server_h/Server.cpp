#include "Server.h"

Server::Server() {
	_listener.listen( PORT_M );
	_selector.add( _listener );
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
				for( int i = 0; i < active_clients.size(); i++ ) {
					if( _selector.isReady( *active_clients[i] ) ){
						sf::Packet _packet;
						if( active_clients[i]->receive( _packet ) == sf::Socket::Done ) {
							_reader.read( _packet, active_clients[i], &_handler );
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

void Server::send( sf::TcpSocket& socket, std::string data ) {
	sf::Packet _packet;
	_packet << data;
	socket.send( _packet );
}

Server::~Server() {
	// TODO Auto-generated destructor stub
}
