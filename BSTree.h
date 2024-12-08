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
			if(n == nullptr){
				throw runtime_error("Elemento no encontrado\n");
			}else if(n->elem < e){
				return search(n->right, e);
			}else if(n->elem > e){
				return search(n->left, e);
			}else{
				return n;
			}
		}

	//Inserción de elementos
		BSNode<T>* insert(BSNode<T>* n, T e){
			if(n == nullptr){
				return new BSNode<T> (e);
			}else if(n->elem == e){
				throw runtime_error("El elemento ya existe\n");
			}else if(n->elem < e){
				n->right = insert(n->right, e);
			}else{
				n->left = insert(n->left, e);
			}
			return n;
		}

	//Recorrido e impresión del árbol
		void print_inorder(ostream &out, BSNode<T>* n)const{
			if(n != nullptr){
				print_inorder(out, n->left);
				out << n->elem << " ";
				print_inorder(out, n->right);
			}
		}


	//Eliminación de elementos
		BSNode<T>* remove(BSNode<T>* n, T e){
			if(n == nullptr){
				throw runtime_error("No se ha encontrado el elemento\n");
			}else if(n->elem < e){
				n->right = remove(n->right, e);
			}else if(n->elem > e){
				n->left = remove(n->left, e);
			}else{
				if(n->left != nullptr && n->right != nullptr){
					n->elem = max(n->left);
					n->left = remove_max(n->left);
					
				}else{
					BSNode<T>* temp = n;
					n = (n->left != nullptr)? n->left : n->right;
					delete temp;
					
				}
			}
			return n;
		}
		T max(BSNode<T>* n) const{
			if( n == nullptr){
				throw runtime_error("Árbol vacío\n");
			}else if(n->right != nullptr){
				return max(n->right);
			}else{
				return n->elem;
			}
		}
		BSNode<T>* remove_max(BSNode<T>* n){
			if(n->right == nullptr){
				BSNode<T>* aux = n;
				delete aux;
				return n->left;
			}else{
				n->right = remove_max(n->right);
				return n;
			}
		}

	//Destrucción
		void delete_cascade(BSNode<T>* n){
			if(n != nullptr){
				delete_cascade(n->left);
				delete_cascade(n->right);
				delete n;
			}
		}

	public:

	//creación y tamaño
		BSTree(){
			nelem = 0;
			root = nullptr;
		}
		int size() const{
			return nelem;
		}

	//Búsqueda de elementos
		T search(T e) const{
			return search(root,e)->elem;
		}

		T operator[](T e) const{
			return search(root, e)->elem;
		}

	//Inserción de elementos
		void insert(T e){
			root = insert(root, e);
			//nelem++;
		}

	//Recorrido e impresión del árbol
		friend ostream& operator<<(ostream &out, const BSTree<T> &bst){
			bst.print_inorder(out, bst.root);
			return out;
		}
	
	//Eliminación de elementos
		void remove(T e){
			root = remove(root, e);
			nelem--;
		}

	//Destrucción
		~BSTree(){
			delete_cascade(root);
		}
};

#endif
