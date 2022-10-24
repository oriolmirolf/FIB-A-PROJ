/** @file diccTrie.hh
    @brief Especificación de la clase TST
*/

#ifndef DICCTRIE_HH
#define DICCTRIE_HH

#ifndef NO_DIAGRAM
#include <string>
#endif
using namespace std;

/** @class TST
    @brief Representa el diccionario implementado como un trie
*/
class TST {
public:

	// Constructora
  
  	/** @brief Creadora por defecto.
  	Se ejecuta automáticamente al declarar un TST.
    \pre Cierto.
    \post El resultado es un diccionario vacío.
    \coste Constante.
  	*/
    TST();
    
    // Modificadora
    
    /** @brief Modificadora por defecto.
  	Se ejecuta cuando queremos añadir una palabra al diccionario.
    \pre Cierto.
    \post Añade la palabra s al parámetro implícito.
    \coste O(log(n+k)) en caso medio y O(n+k) en caso peor, donde n es el número de palabras en el TST y k la longitud de la palabra insertada.
    */
    void insert(const string& s);
    
    // Consultoras

    /** @brief Consulta si la palabra s pertenece al trie.
    \pre Cierto.
    \post Retorna cierto si s se encuentra en el parámetro implícito, en caso contrario retorna falso.
    \coste O(log(n+k)) en caso medio y O(n+k) en caso peor, donde n es el número de palabras en el TST y k la longitud de la palabra insertada.
    */
    bool search(const string& s);
	
	/** @brief Consulta si existe el prefijo s en el trie.
    \pre Cierto.
    \post Retorna cierto si s es un prefijo de una de las palabras del parámetro implícito, en caso contrario retorna falso.
    \coste O(log(n+k)) en caso medio y O(n+k) en caso peor, donde n es el número de palabras en el TST y k la longitud de la palabra insertada.
    */
    bool prefix(const string& s);

private: 
	
	/** @brief Representación interna de un nodo del árbol. */
    struct node {
        char data;
        bool wordEnd = false;
        node *left, *mid, *right;
    };
    
    // Constructora
	
	/** @brief Crea un nuevo nodo del árbol con la información pasada por parámetro.
    \pre Cierto.
    \post Retorna un nuevo nodo del árbol con data == c, wordEnd == false y todos
    los punteros de sus subárboles apuntando a NULL.
    \coste Constante.
    */
    node* newNode(const char& c);
	
	/** @brief Nodo raíz del árbol. */
    node* root;
    
    /** @brief Número de palabras contenidas en el árbol. */
    int n;
    
	// Modificadora
	
	/** @brief Función insertora recursiva privada para facilitar la operación insertar.
    \pre n == root && i == 0.
    \post Añade la palabra s al parámetro implícito.
    \coste O(log(n+k)) en caso medio y O(n+k) en caso peor, donde n es el num de palabras en el TST y k la longitud de la palabra insertada.
    */
    void insertRec(node*& n, const string& s, int i);
    
    // Consultoras
    
    /** @brief Consulta si la palabra s pertenece al trie recursivamente.
    \pre n == root && i == 0.
    \post Retorna cierto si s pertenece al parámetro implícito, en caso contrario retorna falso.
    \coste O(log(n+k)) en caso medio y O(n+k) en caso peor, donde n es el número de palabras en el TST y k la longitud de la palabra insertada.
    */
    bool searchRec(node*& n, const string& s, int i);
	
	/** @brief Consulta si existe el prefijo s en el trie recursivamente.
    \pre n == root && i == 0.
    \post Retorna cierto si s es un prefijo de una de las palabras del parámetro implícito, en caso contrario retorna falso.
    \coste O(log(n+k)) en caso medio y O(n+k) en caso peor, donde n es el número de palabras en el TST y k la longitud de la palabra insertada.
    */
    bool prefixRec(node*& n, const string& s, int i);
};
#endif
