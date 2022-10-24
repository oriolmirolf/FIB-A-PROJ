#ifndef NO_DIAGRAM
#include <set>
#endif

#include "diccSortedVector.cc"
#include "diccBloomFilter.cc"
#include "diccTrie.cc"
#include "diccDHashing.cc"

using namespace std;

typedef vector<vector<uint>> VVI;
typedef vector<vector<char>> VVC;
 
// Vectores de dirección
int dRow[] = {0, 1, 0, -1, 1, 1, -1, -1};
int dCol[] = {-1, 0, 1, 0, 1, -1, 1, -1};

// Comprobador de posiciones válidas
bool isValid(int n, int row, int col) {
    if (row < 0 || col < 0 || row >= n || col >= n) return false;
    return true;
}

// SORTED VECTOR

void DFSVector(const int& row, const int& col, const VVC& Sopa, const SortedVector& Dic, VVI& vis, const uint& it, const string& str, set<string>& Soluciones) {
	int n = Sopa.size();
    if (Dic.search(str)) Soluciones.insert(str);

    for (int i = 0; i < 8; i++) {    
        int adjx = row + dRow[i];
        int adjy = col + dCol[i];
        if (isValid(n, adjx, adjy) and vis[adjx][adjy] != it and Dic.prefix(str)) {
         	vis[adjx][adjy] = it;
            DFSVector(adjx, adjy, Sopa, Dic, vis, it, str + Sopa[adjx][adjy], Soluciones);
         	vis[adjx][adjy] = 0;
        }
    }
}

void solVector(const VVC& Sopa, SortedVector& Dic, set<string>& Soluciones) {
    int n = Sopa.size();
    VVI vis(n, vector<uint>(n, 0));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
        	vis[i][j] = n*i + j + 1;
            string str = string(1, Sopa[i][j]);
            DFSVector(i, j, Sopa, Dic, vis, n*i+j+1, str, Soluciones);
        }
    }
}

// BLOOM FILTER

void DFSBloom(const int& row, const int& col, const VVC& Sopa, BloomFilter& Dic, VVI& vis, const uint& it, string str, set<string> &Soluciones) {
	int n = Sopa.size();
    if (Dic.check(str)) Soluciones.insert(str);
     
    for (int i = 0; i < 8; i++) {    
        int adjx = row + dRow[i];
        int adjy = col + dCol[i];
        if (isValid(n, adjx, adjy) and vis[adjx][adjy] != it and Dic.prefix(str)) {
        	vis[adjx][adjy] = it;
            DFSBloom(adjx, adjy, Sopa, Dic, vis, it, str + Sopa[adjx][adjy], Soluciones);
        	vis[adjx][adjy] = 0;
        }
    }
}

void solBloom(const VVC &Sopa, BloomFilter& Dic, set<string>& Soluciones) {      
    int n = Sopa.size();
    VVI vis(n, vector<uint>(n, 0));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
        	vis[i][j] = n*i + j + 1;
            string str = string(1, Sopa[i][j]);
            DFSBloom(i, j, Sopa, Dic, vis, n*i+j+1, str, Soluciones);
        }
    }
}

// TRIE

void DFSTrie(const int& row, const int& col, const VVC& Sopa, TST& Dic, VVI& vis, const uint& it, string str, set<string>& Soluciones) {
	int n = Sopa.size();
    if (Dic.search(str)) Soluciones.insert(str);

    for (int i = 0; i < 8; i++) {
        int adjx = row + dRow[i];
        int adjy = col + dCol[i];
        if (isValid(n, adjx, adjy) and vis[adjx][adjy] != it and Dic.prefix(str)) {
        	vis[adjx][adjy] = it;
            DFSTrie(adjx, adjy, Sopa, Dic, vis, it, str + Sopa[adjx][adjy], Soluciones);
        	vis[adjx][adjy] = 0;
        }
    }
}

void solTrie(const VVC& Sopa, TST& Dic, set<string>& Soluciones) {
    int n = Sopa.size();
    VVI vis(n, vector<uint>(n, 0));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
        	vis[i][j] = n*i + j + 1;
            string str = string(1, Sopa[i][j]);
            DFSTrie(i, j, Sopa, Dic, vis, n*i+j+1, str, Soluciones);
        }
    }
}

// DOUBLE HASH

void DFSHash(const int& row, const int& col, const VVC& Sopa, DoubleHashing& Dic, VVI& vis, const uint& it, string str, set<string>& Soluciones) {
	int n = Sopa.size();
    if (Dic.search(str)) Soluciones.insert(str);

    for (int i = 0; i < 8; i++) {  
        int adjx = row + dRow[i];
        int adjy = col + dCol[i];
        if (isValid(n, adjx, adjy) and vis[adjx][adjy] != it and Dic.prefix(str)) {
        	vis[adjx][adjy] = it;
            DFSHash(adjx, adjy, Sopa, Dic, vis, it, str + Sopa[adjx][adjy], Soluciones);
            vis[adjx][adjy] = 0;
        }
    }
}

void solHash(const VVC& Sopa, DoubleHashing& Dic, set<string>& Soluciones) {
    int n = Sopa.size();
    VVI vis(n, vector<uint>(n, 0));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
        	vis[i][j] = n*i + j + 1;
            string str = string(1, Sopa[i][j]);
            DFSHash(i, j, Sopa, Dic, vis, n*i+j+1, str, Soluciones);
        }
    }
}
