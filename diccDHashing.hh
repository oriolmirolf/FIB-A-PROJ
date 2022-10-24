/** @file diccDHashing.hh
    @brief Especificación de la clase DoubleHashing
*/

#ifndef DICCDHASHING_HH
#define DICCDHASHING_HH

#ifndef NO_DIAGRAM
#include <vector>
#include <bitset>
#include <cmath>
#include <iostream>
#endif
using namespace std;

/** @class DoubleHashing
    @brief Representa el diccionario implementado como tabla de Hash con Double Hashing
*/

#define MAX_SIZE 10000001ll

class DoubleHashing {
public:

    // Constructora
    
    /** @brief Creadora por defecto.
  	Se ejecuta automáticamente al declarar un DoubleHashing.
    \pre Cierto.
    \post El resultado es un diccionario vacío.
    \coste Constante.
  	*/
    DoubleHashing();
	
	// Modificadora
	
	/** @brief Hace un hash structure con todos los prefijos de los elementos del vector.
    \pre El vector contiene las palabras que se desean insertar en el Hash. n_elem contiene el número prefijos que hay en el vector.
    \post Se hace un hash en el diccionario actual de las palabras en el vector. Los elementos que estaban anteriormente en la estructura desaparecen.
    \coste  O(m+n(m + x)) donde m es el tamaño del array interno, n el número de elementos a insertar y x el tamaño máximo de los strings que introducimos.
  	*/
    void hashPrefixes(const vector<string> &words, int n_elem);
    
    // Consultoras

    /** @brief Consulta si el string word es una palabra del diccionario.
    \pre Cierto.
    \post Retorna cierto si word es una de las palabras del parámetro implícito, en caso contrario retorna falso.
    \coste En tiempo medio O(1/(1 - α)) donde alfa es el factor de carga (n/m) y en caso peor es O(m + x) donde m es el tamaño del array y x el tamaño máximo del string.
  	*/
    bool search(const string& word) const;
	
  	/** @brief Consulta si el string word es el prefijo de una de las palabras del diccionario.
    \pre Cierto.
    \post Retorna cierto si word es el prefijo de una de las palabras que forman parte del parámetro implícito.
    \coste En tiempo medio O(1/(1 - α)) donde alfa es el factor de carga (n/m) y en caso peor es O(m + x) donde m es el tamaño de array y x el tamaño máximo del string.
  	*/
    bool prefix(const string& word) const;

private:
    
    // Teoría de Double Hashing extraída de https://www.geeksforgeeks.org/hashing-set-3-open-addressing/
	
	/** @brief Número de posiciones en la tabla de hash. */
    int m;
    
    /** @brief Número de elementos insertados en la tabla de hash. */
    int n;
    
    /** @brief Factor de carga de la estructura de datos calculado a partir de n/m. */
    double load;
    
    /** @brief Tabla de hash donde se hashean las palabras y prefijos, el booleano indica si es palabra y prefijo (cierto) o solo prefijo (falso). */
    vector<pair<string,bool>> hashTable;
    
    /** @brief Taba bitmap necesaria para calcular rápidamente el rehash pues necesitamos saber rápidamente si un número es primo o no. Se llena con el Sieve of Eratosthenes.*/
    bitset<MAX_SIZE> isPrime;
	
	// Modificadoras
	
    /** @brief Inserta una palabra en el double hash.
    \pre El array del diccionario aún no está lleno.
    \post Se inserta la palabra word en el parámetro implícito según las funciones de hash.
    \coste En tiempo medio O(1/(1 - α)) donde alfa es el factor de carga (n/m) y en caso peor es O(m + x) donde m es el tamaño del array y x el tamaño máximo del string.
  	*/
    void priv_insert_word(const string& word);

    /** @brief Inserta un prefijo en el double hash.
    \pre El array del diccionario aún no está lleno.
    \post Se inserta el prefijo word en el parámetro implícito según las funciones de hash.
    \coste En tiempo medio O(1/(1 - α)) donde alfa es el factor de carga (n/m) y en caso peor es O(m + x) donde m es el tamaño del array y x el tamaño máximo del string.
  	*/
    void priv_insert_prefix(const string& word);
	
	// Consultoras
	
    /** @brief Calcula el valor del índice a partir de la llave.
    \pre Cierto.
    \post Se devuelve un probe para colocar la palabra word en el array.
    \coste O(x) donde x es el tamaño de word.
  	*/
    int getHashKey(const string& word) const;

    /** @brief Calcula el stride para la open adressing iteration.
    \pre Cierto.
    \post Se devuelve un stride para iterar la palabra word por el array hasta encontrar hueco.
    \coste O(x) donde x es el tamaño de word.
  	*/
    int getDoubleHashKey(const string& word) const;

    /** @brief Calcula el valor óptimo del tamaño de la array.
    \pre n es el número de elementos que se intenta tener en el hash map.
    \post Devuelve el tamaño óptimo de la array.
    \coste 
  	*/
    int getArraySize(int n) const;
    
    /** @brief
    \pre Cierto.
    \post Se crea un bitmap que nos dice que numeros son primos y cuales no segun el Sieve of Eratosthenes.
    \coste O(n*log(log(n))) donde n es el número de elementos en el bitmap. 
  	*/
    void setSieve();
};
#endif

