/** @file Sopa.hh
    @brief Especificación de la clase Sopa
*/
#ifndef SOPA_HH
#define SOPA_HH

#ifndef NO_DIAGRAM
#include <iostream>
#include <algorithm>
#include <vector>
#endif
using namespace std;

/** @class Sopa
    @brief Representa la Sopa
*/
class Sopa {
public:

    // Constructora

  	/** @brief Creadora por defecto.
	Se ejecuta automáticamente al declarar una Sopa.
  	\pre n >= 1.
  	\post El resultado es una Sopa de n filas y n columnas con todas las palabras de v repartidas aleatoriamente dentro de la Sopa.
  	*/
  	Sopa(int n, vector<string> s);

  	// Consultoras

  	/** @brief Consulta si la fila p.first, columna p.second se encuentra dentro de la Sopa.
    \pre Cierto.
    \post Retorna cierto si la posición (p.first, p.second) se encuentra dentro de la Sopa, en caso contrario retorna falso.
    \coste Constante.
  	*/
  	bool pos_ok(const pair<int, int>& p) const;

  	// Escritura
  
  	/** @brief Escribe el contenido de todas las casillas de la Sopa.
    \pre Cierto.
    \post Escribe los caracteres de las n*n casillas en forma de matriz.
    \coste Cuadrático en el número de filas de la Sopa.
  	*/
  	void write() const;

  	/** @brief Matriz que representa las casillas de la Sopa. */
  	vector<vector<char>> M;
  
  	/** @brief Número de filas y columnas de la Sopa. */
  	int n;

private:

	/** @brief Vector que representa las 8 direcciones de movimiento. */
  	const vector<pair<int, int>> dir = {{-1, 0}, {-1, 1}, {0, 1}, {1, 1}, {1, 0}, {1, -1}, {0, -1}, {-1, -1}};
  
	/** @brief Posiciona aleatoriamente la palabra s en la Sopa.
    \pre Cierto.
    \post Se selecciona un conjunto de casillas de la sopa aleatoriamente para posicionar la palabra s, sin afectar a la colocación previa del resto de palabras. Si se ha podido colocar la palabra s en el parámetro implícito retorna cierto, en caso contrario retorna falso.
  	*/
  	bool placeWord(const string& s);

  	/** @brief Posiciona recursivamente los caracteres de s hasta haberlos posicionado todos dentro de la Sopa.
    \pre Todos los caracteres de s en los índices desde 0 hasta v.size() han encontrado una posición de colocación correcta dentro del parámetro implícito.
    \post Si es posible encuentra una posición de colocación correcta para el siguiente carácter, en caso contrario vuelve un paso atrás e intenta colocar de manera distinta el anterior carácter.
  	*/
  	void placeWordRec(const pair<int, int>& p, const string& s, vector<pair<int, int>>& v, bool& stop);
};
#endif

