//Diccionario clave->valor cómo se puede gestionar

#ifndef DICT_H
#define DICT_H
#include <string>
using namespace std;
template <typename V>
class Dict {
	public:
		virtual void insert (string key, V value) = 0; //inserta key->value
		virtual V search(string key) = 0; //busca el valor de key. Devuelve value
		virtual V remove(string key) = 0; //elimina key->value
		virtual int entries() = 0; //devuelve num elementos del diccionario

};
#endif