#ifndef MODESELECTOR_H_
#define MODESELECTOR_H_
#include <SFML/Graphics.hpp>
#include <iostream>
#define ITEMS 2

class Mode_Selector {
public:
	Mode_Selector( float width, float height );
	void draw( sf::RenderWindow& window );
	void move_up();
	void move_down();
	const int& get_index_selected() const;
	virtual ~Mode_Selector( );
private:
	int selected_mode;
	sf::Font _font;
	sf::Text _menu[ ITEMS ];
};

#endif /* MODESELECTOR_H_ */
