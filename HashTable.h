#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <ostream>
#include <stdexcept>
#include "Dict.h"
#include "TableEntry.h"

#include "/mnt/c/Users/Usuario/OneDrive/Escritorio/Universidad/2_CARRERA/PRA/practicas/PRA_2425_P1/PRA_2425_P1/ListLinked.h"

using namespace std;
template <typename V>
class HashTable: public Dict<V> {

    private:
        int n;
        int max;
        ListLinked<TableEntry<V>>* table;

        int h(string key){
			int ascii = 0;
            for(int i = 0; i<key.length(); i++){
                ascii += int(key.at(i));
            }
			int res = ascii % max;
            return res;
        }
    public:
        HashTable(int size){
            table = new ListLinked<TableEntry<V>> [size];
            n = 0;
            max = size;
        }
        ~HashTable(){
            delete[] table;
        }
        int capacity(){
            return max;
        }
        friend ostream& operator<<(ostream &out, const HashTable<V> &th){
			out << "HashTable [entries: " << th.n << ", capacity: "<< th.max <<"]\n" << endl;
            out << "==========================" << endl;
            for(int i = 0; i < th.max; i++){
				out << "== Cubeta " << i << " ==\n" << endl;
				out << th.table[i] << endl;
			}
            out << "\n" << endl;
			return out;
        }
        V operator[](string key){
            if(search(key) != -1){
                return search(key);
            }else{
                throw runtime_error("No existe el valor key\n");
            }
        }

        void insert (string key, V value)override{
            int pos = h(key); //h(key) función de hash que determina la pos en tabla donde se almacena elemento con clave key
			if(table[pos].search(key) != -1){
				throw runtime_error("El elemento que se quiere insertar está duplicado. NO se puede insertar\n");
			}else{
				TableEntry<V> add(key, value);
				table[pos].prepend(add);//añade elemento al principio de lista
				n++;
			}
		
        }

		V search(string key)override{
            int pos = h(key);
			for(int i = 0; i < table[pos].size(); i++){
                if(table[pos].get(i).key == key){
                    return table[pos].get(i).value;
                }
            }
			throw runtime_error("No se ha encontrado key\n");
        } 

		V remove(string key)override{
			int pos = h(key);
			TableEntry<V> elimina(key);
			while (table[pos].search(key) == -1){
            	throw runtime_error("No se ha encontrado key\n");
        	}
            n--;
        	return table[pos].remove(pos).value;
        } 

		int entries()override{
            return n;
        }
};
#endif


