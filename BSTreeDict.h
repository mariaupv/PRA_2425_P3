#ifndef BSTREEDICT_H
#define BSTREEDICT_H

#include <ostream>
#include <stdexcept>
#include "Dict.h"
#include "BSTree.h"
#include "TableEntry.h"
using namespace std;

template <typename V>
class BSTreeDict: public Dict<V>{
	
	private:
		BSTree<TableEntry<V>>* tree;

	public:
		BSTreeDict(){
			tree = new BSTree<TableEntry<V>>; // Creamos ABB vacío con memoria dinámica
		}

		~BSTreeDict(){
			delete tree;
		}

		friend ostream& operator<<(ostream &out, const BSTreeDict<V> &bs){
			out <<*bs.tree;
			out << endl;
			return out;
		}
		V operator[] (string key){
				TableEntry<V> aux(key);
				return tree->search(aux).value;
		}

		void insert (string key, V value){
			TableEntry<V> aux (key, value);
			tree->insert(aux); 

		} //inserta key->value

		V search(string key){
			TableEntry<V> aux (key);
			return tree->search(aux).value;
		} //busca el valor de key. Devuelve value

		V remove(string key){
			TableEntry<V> aux(key);
			V value = tree->search(aux).value;
			tree->remove(aux);
			return value;
		} //elimina key->value

		int entries(){
			return tree->size();
			
		} //devuelve num elementos del diccionario
};

#endif
