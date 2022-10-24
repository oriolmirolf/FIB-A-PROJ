/** @file diccDHashing.cc
    @brief Implementación de la clase DoubleHashing
*/
#include "diccDHashing.hh"

DoubleHashing::DoubleHashing() {
    setSieve();
    this->n = 0;
    this->hashTable = vector<pair<string, bool>> (0);
}

void DoubleHashing::hashPrefixes(const vector<string> &words, int n_elem) {
    this->n = n_elem;
    this->m = getArraySize(n);
    this->hashTable = vector<pair<string, bool>>(m);
    
    for (int i = 0; i < (int)words.size(); i++) {
        string word = "";
        for (int j = 0; j < (int)words[i].size(); j++){
            word = word + words[i][j];
            if (j + 1 == (int)words[i].size()) { // Si vamos a insertar la palabra
            	priv_insert_word(word);
            }
            else priv_insert_prefix(word); // Sino insertamos el prefijo que toque
        } 
    }
}

bool DoubleHashing::search(const string& word) const {
    int probe = getHashKey(word);
    int stride = getDoubleHashKey(word);
    int iniPos = probe;
    bool first = true;

    while (hashTable[probe].first != word) {
        if ((probe == iniPos && !first) || (hashTable[probe].first=="")) return false;
        else probe = (probe+stride) % m;

        first = false;
    }
    return hashTable[probe].second;
}

bool DoubleHashing::prefix(const string& word) const {
    int probe = getHashKey(word);
    int stride = getDoubleHashKey(word);
    int iniPos = probe;
    bool first = true;

    while (hashTable[probe].first != word) {
        if ((probe == iniPos && !first) || (hashTable[probe].first=="")) return false;
        else probe = (probe+stride) % m;

        first = false;
    }
    return true;
}

void DoubleHashing::priv_insert_word(const string& word) {

    int probe = getHashKey(word);
    int stride = getDoubleHashKey(word);

    while (hashTable[probe].first!="" and hashTable[probe].first!=word) {
        probe = (probe+stride) % m;
    }

    hashTable[probe] = make_pair(word,true); // El valor cierto indica que esta palabra pertenece al diccionario y no es solo un prefijo
    ++n;
}

void DoubleHashing::priv_insert_prefix(const string& word) {
    int probe = getHashKey(word);
    int stride = getDoubleHashKey(word);
    
    while (hashTable[probe].first != "" and hashTable[probe].first != word) {
        probe = (probe+stride) % m;
    }

    if (hashTable[probe].first != word) hashTable[probe] = make_pair(word, false);
    ++n;
}

int DoubleHashing::getHashKey(const string& word) const {
// Extraído de https://stackoverflow.com/questions/29759214/double-hashing-efficiency-with-word-dictionary
    int index = 0;
    for (int i = 0; i < (int)word.length(); i++) {
        index += pow(2, i)*(int(word[i]));
        index = index%m;
    }
    return index;
}

int DoubleHashing::getDoubleHashKey(const string& word) const {
    int jump = 1;

    for (int i = 0; i < (int)word.length(); i++) {
        jump = jump * int(word[i]);
        jump = jump%m;
    }
    return jump;
}

int DoubleHashing::getArraySize(int n) const {
// Extraído de https://cseweb.ucsd.edu/~kube/cls/100/Lectures/lec16/lec16-8.html
    int prime = n*1.3;
    while (isPrime[prime] == 1) ++prime;
    return prime;
}

void DoubleHashing::setSieve() {
// Extraído de https://www.geeksforgeeks.org/double-hashing/
    isPrime[0] = isPrime[1] = 1;
    
    for (long long i = 2; i*i <= MAX_SIZE; i++) {
        if (isPrime[i] == 0) {
            for (long long j = i*i; j <= MAX_SIZE; j += i) {
                isPrime[j] = 1;
            }
    	}
	}
}
