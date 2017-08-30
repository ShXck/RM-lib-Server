#include "StatusChecker.h"

Status_Checker::Status_Checker( sf::TcpSocket* sender ) : sender_socket( sender ) {
	checker_time_handler = std::async( std::launch::async, &Status_Checker::check_status, this );
}

void Status_Checker::check_status( ) {

	while( true ) {

		std::this_thread::sleep_for( std::chrono::seconds( CHECK_PERIOD ) );

		sf::Packet checker_packet;
		checker_packet << _encrypter.apply( JSON_Handler::build_check_msg() );
		sender_socket->send( checker_packet );
	}
}

Status_Checker::~Status_Checker() { }

