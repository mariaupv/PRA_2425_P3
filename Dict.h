#ifndef DICT_H
#define DICT_H
#include <string>
using namespace std;
template <typename V>
class Dict {
	public:
		void insert (string key, V value); //inserta key->value
		V search(string key); //busca el valor de key. Devuelve value
		V remove(string key); //elimina key->value
		int entries(); //devuelve num elementos del diccionario

};
#endif