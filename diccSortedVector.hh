/** @file diccSortedVector.hh
    @brief Especificación de la clase SortedVector
*/

#ifndef DICCSORTEDVECTOR_HH
#define DICCSORTEDVECTOR_HH

#ifndef NO_DIAGRAM
#include <iostream>
#include <algorithm>
#endif
using namespace std;

/** @class SortedVector
    @brief Representa el diccionario implementado como vector ordenado
*/
class SortedVector {
public:

    // Constructora
  
  	/** @brief Creadora por defecto.
  	Se ejecuta automáticamente al declarar un SortedVector.
    \pre Cierto.
    \post El resultado es un diccionario vacío.
    \coste Constante.
  	*/
  	SortedVector(const int& n);
  
  	// Modificadora
  	
  	/** @brief Modificadora por defecto.
  	Se ejecuta cuando queremos añadir una palabra al diccionario.
    \pre Cierto.
    \post La palabra s se añade al parámetro implícito si el diccionario aún no tiene n palabras, en caso contrario no la añade.
    \coste Constante en general, O(nlog(n)) al añadir la palabra número n.
  	*/
  	void insert(const string& s);
  
  	// Consultora

  	/** @brief Consulta si el string s es una palabra del diccionario.
    \pre Cierto.
    \post Retorna cierto si s es una de las palabras del parámetro implícito, en caso contrario retorna falso.
    \coste Logarítmico en el número de palabras del diccionario.
  	*/
  	bool search(const string& s) const;
  	
  	/** @brief Consulta si el string s es el prefijo de una de las palabras del diccionario.
    \pre Cierto.
    \post Retorna cierto si s es el prefijo de una de las palabras que forman parte del parámetro implícito.
    \coste O(nlog(n) + |s|), donde n es el número de palabras en el diccionario y |s| el tamaño de la palabra a buscar.
  	*/
  	bool prefix(const string& s) const;

private:

	/** @brief Vector que guarda todas las palabras del diccionario. */
  	vector<string> v;
  	
  	/** @brief Número de palabras deseadas en el diccionario. */
  	int n;
  	
  	// Consultora
  	
  	/** @brief Comprueba si el string p es prefijo del string s.
    \pre |p| <= |s|.
    \post Retorna cierto si p es prefijo o es igual a s, en caso contrario retorna falso. 
    \coste Lineal en el tamaño de p.
  	*/
  	bool isPrefix(const string& p, const string& s) const;
};
#endif

