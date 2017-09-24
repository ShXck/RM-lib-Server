#include "MemoryMonitor.h"

Memory_Monitor::Memory_Monitor( std::size_t initial_mem_val, std::string initial_cache_val ) {
	if( !_font.loadFromFile("font/DroidSans.ttf") ) {
		std::cout << "Font error" << std::endl;
	}
	set_text( initial_mem_val, initial_cache_val );
}

void Memory_Monitor::run() {

	std::thread t( [this]() {
		sf::RenderWindow _window( sf::VideoMode( 300, 150 ), "RM Memory Monitor" );

		while( _window.isOpen() ) {

				sf::Event _event;

				while( _window.pollEvent( _event ) ) {
					switch( _event.type ) {
						case sf::Event::Closed: {
							_window.close();
							break;
						}
					}
				}
				_window.clear();
				draw( _window );
				_window.display();
			}
	} );
	t.detach();
}

void Memory_Monitor::draw( sf::RenderWindow& window ) {
	for( int i = 0; i < MONITOR_ITEMS; i++ ) {
		window.draw( _text[i] );
	}
}

void Memory_Monitor::set_text( std::size_t initial_mem_val, std::string initial_cache_val ) {
	_text[0].setFont( _font );
	_text[0].setCharacterSize( 18 );
	_text[0].setFillColor( sf::Color::White );
	_text[0].setString( "Memoria utilizada: " + std::to_string( initial_mem_val ) );
	_text[0].setPosition( 10, 20 );

	_text[1].setFont( _font );
	_text[1].setCharacterSize( 12 );
	_text[1].setFillColor( sf::Color::White );
	_text[1].setString( "Cache: " + initial_cache_val );
	_text[1].setPosition( 10, 50 );
}

void Memory_Monitor::update( int pos, std::string data ) {
	if( pos == 0 ) {
		_text[0].setString( "Memoria utilizada: " + data );
	} else {
		_text[1].setString( "Cache: " + data );
	}
}

Memory_Monitor::~Memory_Monitor() { }

