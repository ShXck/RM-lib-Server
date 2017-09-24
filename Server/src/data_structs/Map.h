#ifndef DATA_STRUCTS_MAP_H_
#define DATA_STRUCTS_MAP_H_
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <cstring>

template < typename Key, typename Value >
struct Node {
	Value _data;
	Key _key;
	Node < Key, Value > *_next;
	Node ( Key key, Value data ):_data( data ), _key( key ), _next( nullptr ) { }
};

template < typename Key, typename Value >
class Map {
private:
	Node< Key, Value > *_head;
	int _size;
private:
	void remove_head() {
		Node< Key, Value > *_temp = _head;
		_head = _head->_next;
		delete _temp;
		//free( _temp );
	}

public:
	Map() : _head( nullptr ), _size( 0 ) { }

	void add( Key key, Value data ) {
		Node< Key, Value >* _new = new Node< Key, Value >( key, data );
		//Node< Key, Value >* _new = create_node( key, data );
		if( is_empty() ) {
			_head = _new;
		} else {
			Node< Key, Value >* _current = _head;
			while( _current->_next != nullptr ) {
				_current = _current->_next;
			}
			_current->_next = _new;
		}
		_size++;
	}

	void add_first( Key key, Value data ) {
		Node< Key, Value >* _new = new Node< Key, Value >( key, data );
		//Node< Key, Value >* _new = create_node( key, data );
		if( is_empty() ) {
			_head = _new;
		} else {
			_new->_next = _head;
			_head = _new;
		}
		_size++;
	}

	void add_at( int pos, Key key, Value data ) {
		Node< Key, Value >* _new = new Node< Key, Value >( key, data );
		//Node< Key, Value >* _new = create_node( key, data );

		if( pos > _size || pos < 0 || (is_empty() && pos != 0) ){
			throw std::invalid_argument( "Impossible action. Invalid position value" );
		} else {
			Node< Key, Value > *_current = _head;
			int i = 0;
			while ( i < (pos - 1) ) {
				_current = _current->_next;
				i++;
			}
			_new->_next = _current->_next;
			_current->_next = _new;
		}
		_size++;
	}

	void remove( Key key ) {

		std::runtime_error not_found( "Element not found" );

		if( is_empty() ) {
			throw not_found;
		} else if( _head->_key == key ) {
			remove_head();
		} else {
			Node< Key, Value > *_current = _head;
			while( _current->_next != nullptr ) {
				if( _current->_next->_key == key ){
					Node< Key, Value > *_temp = _current->_next;
					_current->_next = _current->_next->_next;
					delete _temp;
					_size--;
					return;
				} else {
					_current = _current->_next;
				}
			}
			throw not_found;
		}
		_size--;
	}

	void remove_at( int pos ) {
		if( pos > _size || pos < 0 || ( is_empty() && pos != 0 ) ){
			throw std::invalid_argument( "Imposible action. Invalid position value" );
		} else if( pos == 0 ) {
			remove_head();
		} else {
			Node< Key, Value > *_current = _head;
			int i = 0;
			while( i < (pos - 1) ) {
				_current = _current->_next;
				i++;
			}
			Node< Key, Value > *_temp = _current->_next;
			_current->_next = _current->_next->_next;
			delete _temp;
			//free( _temp );
		}
		_size--;
	}

	bool contains( Key key ) {
		if( is_empty() ) {
			return false;
		} else {
			Node< Key, Value > *_current = _head;
			while( _current != nullptr ) {
				if( _current->_key == key ) {
					return true;
				} else {
					_current = _current->_next;
				}
			}
		}
		return false;
	}

	Value& get( Key key ) {

		std::runtime_error not_found( "Element not found" );

		if( is_empty() ) {
			throw not_found;
		} else {
			Node< Key, Value > *_current = _head;
			while( _current != nullptr ) {
				if( _current->_key == key ) {
					return _current->_data;
				}
				_current = _current->_next;
			}
		}
		throw not_found;
	}

    Value& get( int pos ) {

        if( pos > _size || pos < 0 || is_empty() ){
            throw std::invalid_argument( "Impossible action. Invalid position value" );
        } else {
            Node< Key, Value > *_current = _head;

            int i = 0;
            while( i < pos ) {
                _current = _current->_next;
                i++;
            }
            return _current->_data;
        }
    }

	Value* peek() {
		if( is_empty() ) {
			return nullptr;
		} else {
			return *_head->_data;
		}
	}

	void display() {
		if( is_empty() ) {
			std::cout << "The list is empty" << std::endl;
		} else  {
			Node< Key, Value > *_current = _head;
			while( _current != nullptr ) {
				std::cout << _current->_data << " ";
				_current = _current->_next;
			}
			std::cout << "" << std::endl;
		}
	}

	bool is_empty() const {
		return _size == 0;
	}

	const int& size() const {
		return _size;
	}

	void clear() {
		while( !is_empty() ) {
			remove_at( 0 );
		}
	}

	Node< Key,Value >* head() {
		return _head;
	}

	std::size_t node_size() {
		return sizeof( Node< Key, Value > );
	}

	~Map() {
		while( !is_empty() ) {
			remove_at( 0 );
		}
	}
};







#endif /* DATA_STRUCTS_MAP_H_ */
