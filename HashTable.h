//Implementación mediante tabla hash con encadenamiento
//SE implementa con array de punteros a lista de tipo ListLinked
#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <ostream>
#include <stdexcept>
#include "Dict.h"
#include "TableEntry.h"

#include "../PRA_2425_P1/ListLinked.h" //Modificado
using namespace std;
template <typename V>
class HashTable: public Dict<V> {

    private:
        int n; // num elementos almacenados actual en tabla hash
        int max; //Tamaño tabla hash (num total de cubetas)
        ListLinked<TableEntry<V>>* table; //tabla de cubetas (arrays pteros tipo ListLinked), que almacenan clave->valor (tipo TableEntry)

        int h(string key){ //función hash que devuelve pos(cubeta) en tabla hash de key
			int ascii = 0;
            for(int i = 0; i<key.length(); i++){
                ascii += int(key.at(i));
            }
			int res = ascii % max; //calcula como resto de div suma valores ascii de clave y tamaño tabla
            return res;
        }
    public:
        HashTable(int size){ //método constructor
            table = new ListLinked<TableEntry<V>> [size]; //reserva memoria dinámica->crea tabla de tamaño size
            n = 0;
            max = size;
        }
        ~HashTable(){ //libera mem dinámica de table
            delete[] table;
        }
        int capacity(){ //num total de cubetas de la tabla
            return max;
        }
        friend ostream& operator<<(ostream &out, const HashTable<V> &th){ //imprime tabla hash por pantalla
			out << "HashTable [entries: " << th.n << ", capacity: "<< th.max <<"]\n" << endl;
            out << "==========================" << endl;
            for(int i = 0; i < th.max; i++){
				out << "== Cubeta " << i << " ==\n" << endl;
				out << th.table[i] << endl;
			}
            out << "\n" << endl;
			return out;
        }
        V operator[](string key){ //devuelve valor key si existe
            if(search(key) != -1){
                return search(key);
            }else{
                throw runtime_error("No existe el valor key\n");
            }
        }
//Hay que añadirlos pq para gestionar las entradas clave->valor hace falta los métodos de List<T>
        void insert (string key, V value)override{
            //primero calcula la posición donde se encuentra key
            int pos = h(key); //h(key) función de hash que determina la pos en tabla donde se almacena elemento con clave key
			if(table[pos].search(key) != -1){ //Si ya está ocupado
				throw runtime_error("El elemento que se quiere insertar está duplicado. NO se puede insertar\n");
			}else{ // si está libre
				TableEntry<V> add(key, value); // se crea un objeto key->value
				table[pos].prepend(add);//añade elemento en pos al principio de lista
				n++; //se aumenta el contador 
			}
		
        }

		V search(string key)override{
            int pos = h(key); // calcula la pos de la tabla
			for(int i = 0; i < table[pos].size(); i++){ //recorre la lista en esa posición
                if(table[pos].get(i).key == key){ //si encuentra la clave
                    return table[pos].get(i).value;//devuelve el valor asociado (value)
                }
            }
			throw runtime_error("No se ha encontrado key\n");
        } 

		V remove(string key)override{
			int pos = h(key); //calcula la pos de la tabla
			TableEntry<V> elimina(key); //crea un objeto con la clave key
			for(int i = 0; i < table[pos].size(); i++){ 
                if(table[pos].get(i)==elimina){//buscar key en pos
                    V value = table[pos].get(i).value; // cuando se encuentra se guarda value en value
                    table[pos].remove(i); // se elimina i
                    n--; // se decrementa el num de elementos
                    return value;//se devuelve el valor
                }
            }
            throw runtime_error("No se ha encontrado key\n");
        } 

		int entries()override{
            return n; //devuelve num total de elementos en la tabla hash
        }
};
#endif


