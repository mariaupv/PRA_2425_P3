//Representar en esta clase los pares clave->valor

#ifndef TABLEENTRY_H
#define TABLEENTRY_H

#include <string> 
#include <ostream>
using namespace std;
template <typename V>
class TableEntry{
	public:
		string key;
		V value;

		TableEntry(string key, V value){ //método constructor con clave->valor
			this->key = key;
			this->value = value;
		}
		TableEntry(string key){ //crea sólo una entrada (sin valor)
			this->key = key;
		}
		TableEntry(){
			key = "";
		}
		friend bool operator==(const TableEntry<V> &te1, const TableEntry<V> &te2){
			if(te1.key == te2.key){ // para determinar que los pares se comparan sólo usando la clave. Nos ayuda a detectar colisiones
				return true;
			}else{
				return false;
			}
		}

		friend bool operator!=(const TableEntry<V> &te1, const TableEntry<V> &te2){
			if(te1.key != te2.key){
				return true;
			}else{
				return false;
			}
		}

		friend ostream& operator<<(ostream &out, const TableEntry<V> &te){ // Imprime contenido de entrada por pantalla
			out << "('" << te.key << "' => " << te.value << ")";
			return out;
		}

		friend bool operator<(const TableEntry<V> &te1, const TableEntry<V> &te2){ //comparar orden de obj de la clase y buscar pos en el ABB
			if(te1.key < te2.key){
				return true;
			}else{
				return false;
			}
		}

		friend bool operator>(const TableEntry<V> &te1, const TableEntry<V> &te2){
			if(te1.key > te2.key){
				return true;
			}else{
				return false;
			}
		}
};
#endif
