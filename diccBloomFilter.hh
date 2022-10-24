/** @file diccBloomFilter.hh
    @brief Especificación de la clase BloomFilter
*/

#ifndef DICCBLOOMFILTER_HH
#define DICCBLOOMFILTER_HH

#ifndef NO_DIAGRAM
#include <math.h> 
#include <vector>
#include <string>
#endif
using namespace std;

/** @class BloomFilter
    @brief Representa el diccionario implementado como Filtro de Bloom.
*/
class BloomFilter {
public:

    // Constructora
    
    /** @brief Creadora por defecto.
  	Se ejecuta automáticamente al declarar un BloomFilter.
    \pre Cierto.
    \post El resultado es un diccionario inicializado mediante los valores pasados como parámetro.
    \coste O(m).
  	*/
    BloomFilter(int dictionaryElements, double falsePositiveProb);
	
	// Modificadoras
	
  	/** @brief Modificadora por defecto.
  	Se ejecuta cuando queremos añadir una palabra al diccionario.
    \pre Cierto.
    \post La palabra word se añade al parámetro implícito.
    \coste O(k * l), donde l es la longitud de la palabra que se quiere insertar.
  	*/
    void insert(const string& word);
	
	/** @brief Añade todos los prefijos de words al array auxiliar.
    \pre words tiene nt palabras.
    \post Se computan los parametros óptimos mprefixes y kprefixes. Se crea un array auxiliar de tamaño mprefixes y se le insertan todas las palabras de words, hasheadas tal como se hace en los Filtros de Bloom. 
    \coste O(mprefixes + nprefixes * kprefixes * l^2), donde l es el tamaño máximo de entre las palabras que se quieren insertar.
  	*/
    void hashPrefixes(const vector<string> &words, int nt);
    
    // Consultoras
    
    /** @brief Consulta si el string word es una palabra del diccionario.
    \pre Cierto.
    \post Retorna cierto si word es una de las palabras del parámetro implícito.
    \coste O(k * l), donde l es la longitud de la palabra que se quiere insertar consultar.
  	*/
    bool check(const string& word);
	
	/** @brief Consulta si el string word es un prefijo de una de las palabras del diccionario.
    \pre Cierto.
    \post Retorna cierto si word es un prefijo de una de las palabras del parámetro implícito.
    \coste O(kprefixes * l), donde l es la longitud de la palabra que se quiere consultar.
  	*/
    bool prefix(const string& word);
    
    /** @brief Consultora del tamaño de la array de palabras.
    \pre Cierto.
    \post Retorna el tamaño m de la array de palabras del parámetro implícito.
    \coste O(1)
  	*/
    int getPrimaryArraySize() const;
	
	/** @brief Consultora del tamaño de la array de prefijos.
    \pre Cierto.
    \post Retorna el tamaño mprefixes de la array de prefijos del parámetro implícito.
    \coste O(1)
  	*/
	int getAuxiliarArraySize() const;
	
	/** @brief Consulta la cantidad de hashes usados para las palabras.
    \pre Cierto.
    \post Retorna la cantidad de hashes k usados para las palabras.
    \coste O(1)
  	*/
	int getPrimaryHashQuantity() const;
	
	/** @brief Consulta la cantidad de hashes usados para los prefijos.
    \pre Cierto.
    \post Retorna la cantidad de hashes usados kprefixes para los prefijos.
    \coste O(1)
  	*/
	int getAuxiliarHashQuantity() const;
    
private:
    
    /** @brief Número total de palabras completas en el diccionario. */
    int n;
    
    /** @brief Número total de prefijos de todas las palabras en el diccionario. */
    int nprefixes; 
    
    /** @brief Probabilidad de un falso positivo. */
    double p;
    
    /** @brief Tamaño del array de palabras. */
    int m;
    
    /** @brief Tamaño del array de prefijos. */
    int mprefixes;
    
    /** @brief Número de funciones de hash a ser usadas para las palabras. */
    int k;
    
    /** @brief Número de funciones de hash a ser usadas para los prefijos. */
    int kprefixes;
	
	/** @brief Vector donde almacenamos todas las palabras. */
    vector<bool> array;
    
    /** @brief Vector donde almacenamos todos los prefijos. */
    vector<bool> prefix_array;
    
	// Modificadoras
	
	/** @brief Inserta la palabra word y todos sus prefijos.
    \pre word tiene una longitud >= 1.
    \post Se insertan en el array auxiliar la palabra word y todos sus prefijos.
    \coste O(kprefixes*l^2) donde l es la longitud de la palabra de la que se quieren insertar sus prefijos.
  	*/
    void insertPrefixes(const string& word);
	
	/** @brief Devuelve un hash único para la palabra insertada.
    \pre len es el tamaño de la palabra a insertar.
    \post Retorna un hash único para la palabra.
    \coste O(l), donde l es la longitud de la palabra que se quiere hashear.
    */
    uint32_t mm3Hash(const char *key, uint32_t len, uint32_t seed);
    
    // Consultoras
	
	/** @brief Obtiene el tamaño de la array óptimo m, dada la siguiente fórmula: m = -(n * ln(p)) / (ln(2)^2).
    \pre Cierto.
    \post Retorna el tamaño óptimo del array.
    \coste Constante.
  	*/
    int calcArraySize(int ntmp) const;
	
	/** @brief Obtiene el número óptimo de funciones de hash k, dada la siguiente fórmula: k = (m/n) * ln(2).
    \pre Cierto.
    \post Retorna el número óptimo de funciones de hash.
    \coste Constante.
  	*/
    int calcHashCount(int ntmp, int mtmp) const;
};
#endif
