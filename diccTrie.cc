/** @file diccTrie.cc
    @brief Implementación de la clase TST
*/
#include "diccTrie.hh"

TST::TST() {
    this->root = NULL;
    this->n = 0;
}

void TST::insert(const string& s) {
    insertRec(root, s, 0);
}

bool TST::search(const string& s) {
    return searchRec(root, s, 0);
}

bool TST::prefix(const string& s) {
    return prefixRec(root, s, 0);
}

TST::node* TST::newNode(const char& c) {
    node* temp = new node();
    temp->data = c;
    temp->wordEnd = false;
    temp->left = temp->mid = temp-> right = NULL;
    return temp;
}

void TST::insertRec(node*& n, const string& s, int i) {
    // Caso base: si no existe el nodo raíz creamos uno
    if (n == NULL) n = newNode(s[i]);
    
    // Si la letra es de valor inferior insertamos la palabra en el subárbol izquierdo
    if (s[i] < n->data) insertRec(n->left, s, i);
    
    // Si la letra es de valor superior insertamos la palabra en el subárbol derecho
    else if (s[i] > n->data) insertRec(n->right, s, i);
    
    // Si la letra tiene el mismo valor...
    else {
        // ...si aún hay palabra por procesar, continuamos la palabra en el subárbol del medio
        if (i < (int)s.length()) insertRec(n->mid, s, i + 1);
        // ...en caso contrario ya hemos llegado al final de la palabra
        else n->wordEnd = true;
    }
}

bool TST::searchRec(node*& n, const string& s, int i) {
    // Caso base: si el árbol está vacío retornamos falso
    if (n == NULL) return false;
        
    // Si la letra es de valor inferior buscamos en el subárbol izquierdo
    if (s[i] < n->data) return searchRec(n->left, s, i);
       
	// Si la letra es de valor superior buscamos en el subárbol derecho
    else if (s[i] > n->data) return searchRec(n->right, s, i);
  	
  	// Si la letra tiene el mismo valor...
    else {
        //...si hemos llegado al final de s, verificamos que el nodo actual sea un final de palabra
        if (i == (int)s.length()) return n->wordEnd;
        //...en caso contrario continuamos buscando por el subárbol del medio
        return searchRec(n->mid, s, i+1);
    }
}

bool TST::prefixRec(node*& n, const string& s, int i) {
    // Caso base: si el árbol está vacío retornamos falso
    if (n == NULL) return false;
        
    // Si la letra es de valor inferior buscamos en el subárbol izquierdo
    if (s[i] < n->data) return prefixRec(n->left, s, i);
        
    // Si la letra es de valor superior buscamos en el subárbol derecho
    else if (s[i] > n->data) return prefixRec(n->right, s, i);
        
    // Si la letra tiene el mismo valor...
    else {
        //...si hemos llegado al final de s, es un prefijo de una palabra sin importar que
        // wordEnd sea cierto o falso
        if (i == (int)s.length() - 1) return true;
        //...en caso contrario seguimos buscando por el subárbol del medio
        return prefixRec(n->mid, s, i + 1);
    }
    return false;
}

