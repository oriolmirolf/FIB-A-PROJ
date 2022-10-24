/**
 * @mainpage Super Sopa: Búsqueda de palabras en una sopa de letras estrambótica. Documentación.
 
 El programa principal se encuentra en el módulo main.cc. En referencia a las diferentes implementaciones del diccionario según su estructura de datos interna, para cada estructura de datos tendremos un módulo asociado.<br>Estos son los siguientes: para el diccionario implementado como vector ordenado se le asocia SortedVector, para el diccionario implementado como Filtro de Bloom se le asocia BloomFilter, para el diccionario implementado como un Trie se le asocia TST y para el diccionario implementado como Double Hash se le asocia DoubleHashing.
*/

#include "Sopa.cc"
#include "LibreriaSolvers.cc"
#ifndef NO_DIAGRAM
#include "tiempo.c"
#endif

#define PROB_FALSE_POSITIVE 0.0000001

int main() {
	// Obtenemos el número de palabras a insertar 
	int n;
	cin >> n;
	
	// Creación de las estructuras de datos
	SortedVector diccSV(n);
	BloomFilter diccBF(n, PROB_FALSE_POSITIVE);
	TST diccTST;
	DoubleHashing diccDH;

	vector<string> words(n);
	int nprefixes = 0;

	// Insertamos todas las palabras en las estructuras de datos
	for (int i = 0; i < n; ++i) {
		string s; cin >> s;
		diccSV.insert(s);
		diccBF.insert(s);
		diccTST.insert(s);

		words[i] = s;
		nprefixes += s.length();
	}

	diccBF.hashPrefixes(words, nprefixes);
	diccDH.hashPrefixes(words, nprefixes);
	
	// Creación de la Sopa
	int m; cin >> m; // Obtenemos el tamaño de la Sopa
	vector<string> v(20);
	for (string& s : v) cin >> s;
	Sopa S(m, v);
	
	// Almacenamos las soluciones encontradas por cada estructura de datos y comparamos
	// el nombre de soluciones encontradas y el tiempo de ejecución entre ellas
	set<string> solucionesSV;
	float t1SV = GetTime();
	solVector(S.M, diccSV, solucionesSV);
	float t2SV = GetTime();
	cout << "Sorted Vector (m = " << m << ") ha encontrado " << solucionesSV.size() << " palabras distintas en " << t2SV - t1SV << "ms." << endl;
	
	set<string> solucionesBF;
	float t1BF = GetTime();
	solBloom(S.M, diccBF, solucionesBF);
	float t2BF = GetTime();
	cout << "Bloom Filter (m = " << m << ") ha encontrado " << solucionesBF.size() << " palabras distintas en " << t2BF - t1BF << "ms." << endl;
	
	set<string> solucionesTST;
	float t1TST = GetTime();
	solTrie(S.M, diccTST, solucionesTST);
	float t2TST = GetTime();
	cout << "TST (m = " << m << ") ha encontrado " << solucionesTST.size() << " palabras distintas en " << t2TST - t1TST << "ms." << endl;
	
	set<string> solucionesDH;
	float t1DH = GetTime();
	solHash(S.M, diccDH, solucionesDH);
	float t2DH = GetTime();
	cout << "Double Hashing (m = " << m << ") ha encontrado " << solucionesDH.size() << " palabras distintas en " << t2DH - t1DH << "ms." << endl;
	
}
