#include "Sopa.cc"
#include "LibreriaSolvers.cc"
#ifndef NO_DIAGRAM
#include "tiempo.c"
#include <set>
#include <unistd.h>
#endif

// Cambiar para experimentar con diferentes precisiones
#define PROB_FALSE_POSITIVE 0.0000001

int main() {
	// Obtenemos el número de palabras a insertar 
	int n;
	cin >> n;
	
	// Creación de las estructuras de datos necesarias para el testeo
	BloomFilter diccBF(n, PROB_FALSE_POSITIVE);
	TST diccTST;

	vector<string> words(n);
	int nprefixes = 0;

	// Insertamos todas las palabras en las estructuras de datos
	for (int i = 0; i < n; ++i) {
		string s; cin >> s;
		diccBF.insert(s);
		diccTST.insert(s);

		words[i] = s;
		nprefixes += s.length();
	}

	diccBF.hashPrefixes(words, nprefixes);
	
	//Aquí medimos el coste en memoria y la cantidad de hashes usados
	cout << "Coste de memoria: " << diccBF.getPrimaryArraySize() + diccBF.getAuxiliarArraySize() << endl;
	cout << "Cantidad de hashes usados: " << diccBF.getPrimaryHashQuantity() + diccBF.getAuxiliarHashQuantity() << endl;
	
	// Creación de la Sopa
	int m; cin >> m; // Obtenemos el tamaño de la Sopa
	vector<string> v(20);
	for (string& s : v) cin >> s;

	//Para las iteraciones de los experimentos
	for (int i = 0; i < 5; ++i) {
		Sopa S(m, v); // Para poder generar diferentes sopas
		
		float t1 = GetTime();
		set<string> solucionesBF;
		solBloom(S.M, diccBF, solucionesBF);
		float t2 = GetTime();
		
		set<string> solucionesTST;
		solTrie(S.M, diccTST, solucionesTST);
		
		// Medimos la cantidad de falsos positivos
		cout << "Número de falsos positivos : " << solucionesBF.size() - solucionesTST.size() << endl;
		
		// Medimos el tiempo de cada iteración
		cout << "Tiempo : " << t2-t1 << endl;
		
		sleep(1); // Nos aseguramos que entre 2 iteraciones seguidas no usamos la misma semilla
	}
}
