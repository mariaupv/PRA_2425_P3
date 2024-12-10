//Estructura del nodo de árbol binario-> elemento y left/right

#ifndef BSNODE_H
#define BSNODE_H

#include <ostream>

template <typename T>
class BSNode {
	public:
		T elem; //elem tipo T almacenado en el nodo
		BSNode<T>* left; //puntero nodo sucesor izquierdo
		BSNode<T>* right; //puntero nodo sucesor derecho

		BSNode(T elem, BSNode<T>* left=nullptr, BSNode<T>* right=nullptr){ //método constructor(der, izq nulos por defecto)
			this->elem = elem;
			this->left = left; 
			this->right = right;
		}

		friend std::ostream& operator<<(std::ostream &out, const BSNode<T> &bsn){ //imprimir nodo por pantalla
			out << "Elemento: " << bsn.elem ;
			out << ", derecha: " << bsn.right;
			out << ", izquierda: " << bsn.left;
			return out;
		}
};		
#endif
