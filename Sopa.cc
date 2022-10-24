/** @file Sopa.cc
    @brief Implementación de la clase Sopa
*/
#include "Sopa.hh"
#define LIMIT 50

typedef vector<vector<char>> Matrix;

Sopa::Sopa(int n, vector<string> v) {
  this->n = n;
  this->M = Matrix(n, vector<char>(n, '-'));
  
  // Ordenamos aleatoriamente el vector de palabras proporcionado por el usuario
  // para que así el orden de entrada no afecte a la aleatoriedad
  srand(time(NULL));
  random_shuffle(v.begin(), v.end());
  
  // Vamos intentando colocar las palabras una por una
  // si una no se puede colocar, dejamos de intentar colocar las demás
  bool placed = true;
  for (string s : v) {
  	placed = placeWord(s);
  	if (not placed) break;
  }
  
  if (not placed) {
  	this->M.clear();
  	this->n = 0;
  }
  else {
	  // Rellenamos el resto de casillas vacías aleatoriamente
	  for (int i = 0; i < n; ++i) {
		for (int j = 0; j < n; ++j) {
		  if (M[i][j] == '-') M[i][j] = char('a' + rand()%26);
		}
	  }
	}
}

bool Sopa::pos_ok(const pair<int, int>& p) const {
  return p.first >= 0 and p.first < this->n and p.second >= 0 and p.second < this->n;
}

bool Sopa::placeWord(const string& s) {
  if (s.empty()) return false;
  vector<pair<int, int>> v; // Guardamos la posición (i, j) de cada carácter del string s en la Sopa

  bool canPlace = false;
  int times = 0;
  while (not canPlace and times < LIMIT) { // Intentamos añadir s en la Sopa hasta que canPlace == true o superemos el límite de intentos
    pair<int, int> p = {rand()%n, rand()%n}; // Intentamos seleccionar un punto de partida aceptable
    while (M[p.first][p.second] != '-' and M[p.first][p.second] != s[0]) p = {rand()%n, rand()%n};
    placeWordRec(p, s, v, canPlace);
    if (not canPlace and not v.empty()) v.clear();
    ++times;
  }
  if (times == 50) {
  	cerr << "ERROR: No se ha podido generar la Sopa." << endl;
  	return false;
  }
  
  for (int i = 0; i < (int)v.size(); ++i) {
    M[v[i].first][v[i].second] = s[i];
  }
  return true;
}

void Sopa::placeWordRec(const pair<int, int>& p, const string& s, vector<pair<int, int>>& v, bool& stop) {
  v.push_back(p);
  stop = v.size() == s.length();
  if (stop) return;

  vector<pair<int, int>> dir2 = dir;
  random_shuffle(dir2.begin(), dir2.end());

  for (int i = 0; i < 8 and not stop; ++i) {
    pair<int, int> p2 = {p.first + dir2[i].first, p.second + dir2[i].second};
    if (pos_ok(p2)) {
      char c = M[p2.first][p2.second];
      if (c == '-' or c == s[v.size()]) {
      bool duplicated = false;
      for (int j = 0; j < (int)v.size() and not duplicated; ++j) {
      	if (p2 == v[j]) duplicated = true;
      }
      if (not duplicated) {
          placeWordRec(p2, s, v, stop);
          if (not stop) v.pop_back();
       }
      }
    }
  }
}

void Sopa::write() const {
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      cout << M[i][j];
    }
    cout << endl;
  }
}

