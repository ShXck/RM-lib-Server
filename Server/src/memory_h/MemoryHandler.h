#ifndef MEMORY_H_MEMORYHANDLER_H_
#define MEMORY_H_MEMORYHANDLER_H_
#define CACHE_CAPACITY 5
#define CACHE_PERIOD 120
#include "../data_structs/Map.h"
#include <iostream>
#include <string>
#include "../utility.hpp"
#include "../error_handler.hpp"
#include "../server_h/JSONHandler.h"
#include "../data_structs/LinkedList.h"
#include "../MemoryMonitor.h"
#include "Cache.h"
#include <chrono>
#include <thread>
#include <future>

struct RmRef_h {
	int _size;
	char* _value;
	int ref_counter;
	char* client_id;
	RmRef_h( int size, char* value, char* c_id ) : _size( size ), _value( value ), ref_counter( 4 ), client_id( c_id ) {}

	void add_ref() {
		ref_counter++;
	}

	friend bool operator != ( const RmRef_h& r1, const RmRef_h& r2 ) {
		if( strcmp( r1._value, r2._value ) != 0 ) {
			return true;
		}
		return false;
	}

	friend bool operator == ( const RmRef_h& r1, const RmRef_h& r2 ) {
		if( strcmp( r1._value, r2._value ) == 0 ) {
			return true;
		}
		return false;
	}

	RmRef_h& operator=( RmRef_h& r2 ) {
		_value = r2._value;
		_size = r2._size;
		ref_counter = r2.ref_counter;
		client_id = r2.client_id;
		return *this;
	}

	friend std::ostream& operator << ( std::ostream& strm, const RmRef_h& container ) {
		strm << container._value;
		return strm;
	}
};

struct Unused_Ref {
	unsigned int tmp_counter;
	std::string _key;
	Unused_Ref( std::string key ) : tmp_counter( 0 ), _key( key ) {}

	bool operator == ( const Unused_Ref& u_ref ) {
		if( u_ref._key == _key ) {
			return true;
		}
		return false;
	}

	bool operator != ( const Unused_Ref& u_ref ) {
		if( u_ref._key != _key ) {
			return true;
		}
		return false;
	}

	friend std::ostream& operator << ( std::ostream& strm, const Unused_Ref& u_ref ) {
		strm << u_ref._key;
		return strm;
	}
};

typedef std::string str;

class Memory_Handler {
public:
	Memory_Handler();
	/**
	 * Almacena un elemento en el mapa de memoria.
	 * @param key la llave del valor.
	 * @param value el dato.
	 * @param c_id el id del cliente.
	 * @param size el tamaño del elemento.
	 * @return el estado de la acción.
	 */
	str store_value( str key, char* value, char* c_id, int size );
	/**
	 * Busca un valor en la memoria.
	 * @param key la llave del elemento.
	 * @return el estado de la acción.
	 */
	str find_value( str key );
	/**
	 * Encuentra un conjunto de valores.
	 * @param data el json con las llaves.
	 * @return el estadod de la acción.
	 */
	str find_value_set( char* data );
	/**
	 * Elimina un valor en la memoria.
	 * @param key la llave del elemento.
	 * @return el estado de la acción.
	 */
	str delete_value( str key );
	/**
	 * Reemplaza el dato de un elemento.
	 * @param key la llave del elemento.
	 * @param new_val el nuevo dato.
	 * @return el estado de la acción.
	 */
	str replace_value( str key, char* new_val );
	/**
	 * Sincroniza la información con el servidor HA.
	 * @param key la llave del elemento.
	 * @param data la información.
	 * @param c_id la id del cliente.
	 * @param size el tamaño del elemento.
	 * @param instruction la acción a realizar.
	 */
	void sync_data( str key, char* data, char* c_id, int size, int instruction );
	/**
	 * Elimina todos los valores de un usuario.
	 * @param key el id del cliente.
	 */
	void delete_from( char* key );
	virtual ~Memory_Handler();
private:
	/**
	 * Revisa si una llave es válida.
	 * @param key la llave a comparar.
	 * @return si es válida.
	 */
	bool is_valid( str key );
	/**
	 * Crea un nuevo contenedor de referencias.
	 * @param size el tamaño del elemento.
	 * @param value el dato.
	 * @param c_id la id del usuario.
	 * @return el nuevo contenedor.
	 */
	RmRef_h create_ref( int size, char* value, char* c_id );
	/**
	 * Crea un nuevo contenedor de referencias sin usar.
	 * @param key la llave del elemento.
	 * @return el nuevo contenedor.
	 */
	Unused_Ref create_unused( str key );
	/**
	 * Corre el algoritmo de recolección de basura.
	 */
	void run_garbage_collector();
private:
	Map < str, RmRef_h > memory_map;
	Cache _cache;
	Linked_List < Unused_Ref > unused_resources;
	std::future< void > gbc_handler;
	std::size_t memory_allocated;
	Memory_Monitor _monitor;
};

#endif /* MEMORY_H_MEMORYHANDLER_H_ */
