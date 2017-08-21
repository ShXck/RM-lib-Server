
#include "ModeSelector.h"

Mode_Selector::Mode_Selector( float width, float height ) : selected_mode( 0 ) {
	if( !_font.loadFromFile("font/DroidSans.ttf") ) {
		std::cout << "Font error" << std::endl;
	}

	_menu[ 0 ].setFont( _font );
	_menu[ 0 ].setFillColor( sf::Color::Blue );
	_menu[ 0 ].setString( "Active" );
	_menu[ 0 ].setPosition( sf::Vector2f( 100 , 25 ) );

	_menu[ 1 ].setFont( _font );
	_menu[ 1 ].setFillColor( sf::Color::White );
	_menu[ 1 ].setString( "Passive" );
	_menu[ 1 ].setPosition( sf::Vector2f( 100, 75 ) );
}

void Mode_Selector::draw( sf::RenderWindow& window ) {
	for ( int i = 0; i < ITEMS; i++ ) {
		window.draw( _menu[ i ] );
	}
}

void Mode_Selector::move_down() {
	if( selected_mode +1 < ITEMS ) {
		_menu[ selected_mode ].setFillColor( sf::Color::White );
		selected_mode++;
		_menu[ selected_mode ].setFillColor( sf::Color::Blue );
	}
}

void Mode_Selector::move_up() {
	if( selected_mode - 1 >= 0 ) {
		_menu[ selected_mode ].setFillColor( sf::Color::White );
		selected_mode--;
		_menu[ selected_mode ].setFillColor( sf::Color::Blue );
	}
}

const int& Mode_Selector::get_index_selected() const {
	return selected_mode;
}
Mode_Selector::~Mode_Selector() {

}

