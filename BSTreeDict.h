//Implementar interfaz Dict mediante un ABB representado por clase BSTree que almacena clave->valor

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
		BSTree<TableEntry<V>>* tree; //ABB con elem tipo TableEntry ->gestión elem de diccionario

	public:
		BSTreeDict(){
			tree = new BSTree<TableEntry<V>>; // Creamos ABB vacío con memoria dinámica
		}

		~BSTreeDict(){
			delete tree;
		}

		friend ostream& operator<<(ostream &out, const BSTreeDict<V> &bs){
			out <<*bs.tree; //imprimir contenido diccionario por pantalla
			out << endl;
			return out;
		}
		V operator[] (string key){ //actúa interfaz al método heredado search(key)
				TableEntry<V> aux(key);
				return tree->search(aux).value;
		}

		void insert (string key, V value){
			TableEntry<V> aux (key, value); //crea un objeto de clase TableEntry
			tree->insert(aux); //se inserta en el árbol

		} //inserta key->value en estructura ABB

		V search(string key){
			TableEntry<V> aux (key); 
			return tree->search(aux).value;
		} //busca el valor de key. Devuelve value

		V remove(string key){
			TableEntry<V> aux(key);
			V value = tree->search(aux).value; //lo encuentra, guarda el valor value
			tree->remove(aux); // lo elimina
			return value; //devuelve el valor
		} //elimina key->value

		int entries(){
			return tree->size();
			
		} //devuelve num elementos del diccionario
};

#endif
