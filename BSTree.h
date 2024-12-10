//Representación del árbol ABB

#ifndef BSTREE_H
#define BSTREE_H

#include <ostream>
#include <stdexcept>
#include <stdio.h>
#include <stdlib.h>   
#include <iostream> 
#include "BSNode.h"
using namespace std;
template <typename T>
class BSTree{
	private:
		int nelem = 0; //n elem almacenados en ABB
		BSNode<T>* root; // nodo raíz de ABB
	//Búsqueda de elementos
		BSNode<T>* search(BSNode<T>* n, T e)const{
			if(n == nullptr){ //si nodo es nulo->excepc.
				throw runtime_error("Elemento no encontrado\n");
			}else if(n->elem < e){ // si valor nodo actual es < e
				return search(n->right, e); // se busca en la derecha
			}else if(n->elem > e){
				return search(n->left, e);
			}
			return n;
			
		}

	//Inserción de elementos
		BSNode<T>* insert(BSNode<T>* n, T e){
			if(n == nullptr){
				nelem++; //aumentar tamaño
				return new BSNode<T> (e); // si no existe crea un nuevo nodo
			}else if(n->elem == e){
				throw runtime_error("El elemento ya existe\n");
			}else if(n->elem < e){ // si es mayor se inserta en la derecha
				n->right = insert(n->right, e);
			}else if(n->elem > e){
				n->left = insert(n->left, e);
			}
			return n;
		}

	//Recorrido e impresión del árbol en orden-->inorden
		void print_inorder(ostream &out, BSNode<T>* n)const{
			if(n != nullptr){ //si hay nodos
				print_inorder(out, n->left); //imprime izq
				out << n->elem << " ";
				print_inorder(out, n->right); //imprime der
			}
		}


	//Eliminación de elementos
		BSNode<T>* remove(BSNode<T>* n, T e){
			if(n == nullptr){
				throw runtime_error("No se ha encontrado el elemento\n");
			}else if(n->elem < e){//si es mayor, buscar a la derecha
				n->right = remove(n->right, e);
			}else if(n->elem > e){ //si es menor, a la izq
				n->left = remove(n->left, e);
			}else{//si lo encuentra 
				if(n->left != nullptr && n->right != nullptr){ //si tiene dos hijos
					n->elem = max(n->left); //buscamos el max del subarbol izq
					n->left = remove_max(n->left);//lo eliminamos para que no esté repetido
					
				}else{ //si tiene 1 o ningún hijo
					if(n->left != nullptr){
						n = n->left;
					}else{
						n = n->right;
					}
					nelem--;
				}
			}
			return n;
		}
		T max(BSNode<T>* n) const{ //busca valor máximo en el subárbol a partir de n
			if( n == nullptr){
				throw runtime_error("Árbol vacío\n");
			}else if(n->right != nullptr){ // si no es el final sigue hacia la drecha
				return max(n->right); //busca el max en el sig subarbol
			}
			return n->elem;
			
		}
		BSNode<T>* remove_max(BSNode<T>* n){ //elimina el max
			if(n->right == nullptr){ // si lo encuentro
				BSNode<T>* aux = n->left; //lo elimina
				delete n;
				nelem--;
				return aux;//vuelve a su hijo izquierdo (menor por arriba)
			}
			n->right = remove_max(n->right); //si tiene hijo derecho->func. recursiva
			return n;
			
		}

	//Destrucción
		void delete_cascade(BSNode<T>* n){
			if (n->left != nullptr && n->right != nullptr) {
                delete_cascade(n->left);
                delete_cascade(n->right);
            }
            else if (n->left == nullptr && n->right != nullptr) {
                delete_cascade(n->right);
            }
            else if (n->left != nullptr && n->right == nullptr) {
                delete_cascade(n->left);
            }
            nelem--;
            return delete n;
		}

	public:

	//método constructor y tamaño
		BSTree(){
			nelem = 0;
			root = nullptr;
		}
		int size() const{
			return nelem;
		}

	//Búsqueda de elementos
		T search(T e) const{
			return search(root,e)->elem; //busca y devuelve elem e de tipo T
		}//debe devolver elem que contiene nodo que devuelve método privado

		T operator[](T e) const{
			return search(e); //actúa como interfaz del método search(T e)
		}

	//Inserción de elementos
		void insert(T e){
			root = insert(root, e); //inserta un elemento
		}

	//Recorrido e impresión del árbol
		friend ostream& operator<<(ostream &out, const BSTree<T> &bst){
			bst.print_inorder(out, bst.root);
			return out;
		}
	
	//Eliminación de elementos
		void remove(T e){ //elimina el nodo raíz
			root = remove(root, e);
			
		}

	//Destrucción
		~BSTree(){ //elimina todo el árbol
			delete_cascade(root);
		}
};

#endif
