#ifndef MEMORYMONITOR_H_
#define MEMORYMONITOR_H_
#define MONITOR_ITEMS 3
#include <SFML/Graphics.hpp>
#include <thread>
#include <iostream>

class Memory_Monitor {
public:
	Memory_Monitor( std::size_t initial_mem_val, std::string initial_cache_val );
	/**
	 * Inicia la ejecución del monitor.
	 */
	void run();
	/**
	 * Actualiza la información del monitor.
	 * @param pos la posición que se quiere cambiar.
	 * @param data la nueva información.
	 */
	void update( int pos, std::string data );
	virtual ~Memory_Monitor();
private:
	/**
	 * Pinta los elementos en la pantalla.
	 * @param window la ventana donde se pintan.
	 */
	void draw( sf::RenderWindow& window );
	/**
	 * Inicializa el texto del monitor.
	 * @param initial_mem_val el valor inicial de la memoria usada.
	 * @param initial_cache_val el valor inicial del caché.
	 */
	void set_text( std::size_t initial_mem_val, std::string initial_cache_val );
private:
	sf::Text _text[MONITOR_ITEMS];
	sf::Font _font;
};

#endif /* MEMORYMONITOR_H_ */
