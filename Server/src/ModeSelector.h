#ifndef MODESELECTOR_H_
#define MODESELECTOR_H_
#include <SFML/Graphics.hpp>
#include <iostream>
#define ITEMS 2

class Mode_Selector {
public:
	Mode_Selector( float width, float height );
	/**
	 * Dibuja en la ventana.
	 * @param window la ventana donde se dibuja.
	 */
	void draw( sf::RenderWindow& window );
	/**
	 * Mueve hacia arriba en el menu.
	 */
	void move_up();
	/**
	 * Mueve hacia abajo en el menú.
	 */
	void move_down();
	/**
	 * @return el item seleccionado.
	 */
	const int& get_index_selected() const;
	virtual ~Mode_Selector( );
private:
	int selected_mode;
	sf::Font _font;
	sf::Text _menu[ ITEMS ];
};

#endif /* MODESELECTOR_H_ */
