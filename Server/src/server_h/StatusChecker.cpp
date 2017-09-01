#include "StatusChecker.h"

Status_Checker::Status_Checker( sf::TcpSocket* sender, bool run ) : sender_socket( sender ), is_main_working( true ) {

	if( run ) checker_time_handler = std::async( std::launch::async, &Status_Checker::check_status, this );
}

void Status_Checker::check_status( ) {

	while( is_main_working ) {

		std::this_thread::sleep_for( std::chrono::seconds( CHECK_PERIOD ) );

		std::cout << "CHECKING STATUS" << std::endl;

		sf::Packet checker_packet;
		checker_packet << _encrypter.apply( JSON_Handler::build_check_msg() );
		sender_socket->send( checker_packet );
	}
}

void Status_Checker::set_main_status( bool is_working ) {
	is_main_working = is_working;
}

bool Status_Checker::get_main_status() const {
	return is_main_working;
}

void Status_Checker::check_response( std::string* response ) {

	std::thread( [response, this ]( ) {

		while( true ) {

			std::time_t  _start, _end;
			double _elapsed;

			time( &_start );

			do {
				time( &_end );
				_elapsed = difftime( _end, _start );
				if( *response != "" ) break;
			} while( _elapsed < 12 );

			if( *response == "" && _elapsed >= 12 ) {
				is_main_working = false;
				break;
			}

			_elapsed = 0.0;
			_start = 0;
			_end = 0;

			*response = "";

			std::cout << "IM STILL RUNNING" << std::endl;
		}

		std::cout << "IM OUT" << std::endl;

	}).detach();
}

Status_Checker::~Status_Checker() { }

