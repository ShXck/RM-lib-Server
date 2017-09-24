#ifndef MEMORY_H_CACHE_H_
#define MEMORY_H_CACHE_H_
#include "../data_structs/Map.h"
#include "../data_structs/LinkedList.h"
#include <string>

struct Cache_Resource_Container {
	unsigned int cache_counter;
	char* _value;
	Cache_Resource_Container( char* value, unsigned int counter ) : cache_counter( counter ), _value( value ) {}

	friend std::ostream& operator << ( std::ostream& strm, const Cache_Resource_Container& container ) {
		strm << container._value;
		return strm;
	}
};

class Cache {
	typedef unsigned int u_int;
	typedef Linked_List< std::pair< std::string, char* > > list;
public:
	Cache( u_int capacity );
	/**
	 * Agrega un valor al cache.
	 * @param key la llave del valor.
	 * @param value el dato.
	 * @param counter el contador de referencias interno del caché.
	 */
	void add( std::string key, char* value, u_int counter );
	/**
	 * Actualiza el caché-
	 */
	void update();
	/**
	 * Verifica si el caché tiene cierto valor.
	 * @param key el identificador del valor.
	 * @return si el elemento está.
	 */
	bool contains( std::string key );
	/**
	 * Obtiene un elemento del caché-
	 * @param key la llave del elemento.
	 * @return el valor del elemento.
	 */
	char* get( std::string key );
	/**
	 * Disminuye el contador de referencias de caché en uno.
	 */
	void decrement_counters();
	/**
	 * Incrementa el contador en uno.
	 * @param key la llave del valor.
	 */
	void increment_counter ( std::string key );
	/**
	 * @return si el caché está lleno.
	 */
	bool is_full();
	/**
	 * Actualiza un el dato de un elemento.
	 * @param key la llave del elemento.
	 * @param new_val el nuevo dato.
	 */
	void update_value( std::string key, char* new_val );
	/**
	 * @return una representación en string de los elementos del caché.
	 */
	std::string to_string();
	virtual ~Cache();
private:
	/**
	 * Crea un contenedor de elementos de caché.
	 * @param value el valor del elemento.
	 * @param counter el contador de referencias.
	 * @return un nuevo contenedor.
	 */
	Cache_Resource_Container create_container( char* value, u_int counter );
private:
	u_int _capacity;
	Map< std::string, Cache_Resource_Container > cache_memory;
};

#endif /* MEMORY_H_CACHE_H_ */
