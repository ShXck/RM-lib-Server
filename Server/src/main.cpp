#define MAIN_MODE 0
#define HA_MODE 1
#include <iostream>
#include "server_h/Server.h"
#include <SFML/Graphics.hpp>
#include "ModeSelector.h"

int main() {

	sf::RenderWindow _window( sf::VideoMode( 300, 150 ), "RM Server Mode Selector" );

	Mode_Selector mode_selector( _window.getSize().x, _window.getSize().y );

	while( _window.isOpen() ) {

		sf::Event _event;

		while( _window.pollEvent( _event ) ) {
			switch( _event.type ) {
			case sf::Event::KeyReleased: {
				switch( _event.key.code ) {
				case sf::Keyboard::Up: {
					mode_selector.move_up();
					break;
				case sf::Keyboard::Down: {
					mode_selector.move_down();
					break;
				}
				case sf::Keyboard::Return: {
					int _mode = mode_selector.get_index_selected();
					if( _mode == 0 ) {
						_window.close();
						Server _server ( MAIN_MODE, false );
						_server.run();
					} else {
						_window.close();
						Server _server( HA_MODE, true );
					}
				}
				}
				}
				break;
			}
			case sf::Event::Closed: {
				_window.close();
				break;
			}
			}
		}

		_window.clear();
		mode_selector.draw( _window );
		_window.display();
	}

	return 0;
}
