/** @file diccBloomFilter.cc
    @brief Implementación de la clase BloomFilter
*/
#include "diccBloomFilter.hh"

BloomFilter::BloomFilter(int dictionaryElements, double falsePositiveProb) {
    this->p = falsePositiveProb;

    this->n = dictionaryElements;
    this->m = calcArraySize(dictionaryElements);
    this->array = vector<bool>(m, false);
    this->k = calcHashCount(n, m);
}

void BloomFilter::insert(const string& word) {
    // Para aplicar k veces en la función de hash
    for (int i = 0; i < k; ++i) {
        uint32_t result = mm3Hash(word.c_str(), word.length(), i);
        array[result % m] = true;
    }
}

void BloomFilter::hashPrefixes(const vector<string> &words, int n) {
    nprefixes = n;
    mprefixes = calcArraySize(nprefixes);
    prefix_array = vector<bool>(mprefixes, false);
    kprefixes = calcHashCount(nprefixes, mprefixes);

    for (int i = 0; i < (int)words.size(); ++i) {
        insertPrefixes(words[i].substr(0, words[i].length()-1));
    }
}

bool BloomFilter::check(const string& word) {
    // Para aplicar k veces en la función de hash
    for (int i = 0; i < k; ++i) {
        uint32_t result = mm3Hash(word.c_str(), word.length(), i);
        if (not array[result % m]) return false;
    }
    return true;
}

bool BloomFilter::prefix(const string& word) {
    for (int i = 0; i < this->kprefixes; ++i) {
        uint32_t result = mm3Hash(word.c_str(), word.length(), i);
        if (not this->prefix_array[result % mprefixes]) return false;
    }
    return true;
}

int BloomFilter::getPrimaryArraySize() const {
	return m;
}

int BloomFilter::getAuxiliarArraySize() const {
	return mprefixes;
}

int BloomFilter::getPrimaryHashQuantity() const {
	return k;
}

int BloomFilter::getAuxiliarHashQuantity() const {
	return kprefixes;
}

void BloomFilter::insertPrefixes(const string& word) {
    for (int i = 0; i < this->kprefixes; ++i) {
        uint32_t result = mm3Hash(word.c_str(), word.length(), i);
        prefix_array[result % mprefixes] = true;
    }
    
    if (word.length() > 1)
    	insertPrefixes(word.substr(0, word.length() - 1));
}

uint32_t BloomFilter::mm3Hash(const char *key, uint32_t len, uint32_t seed) {
// Extraído de https://www.folkstalk.com/2022/09/basic-murmur-hash-function-with-code-examples.html
    static const uint32_t c1 = 0xcc9e2d51;
    static const uint32_t c2 = 0x1b873593;
    static const uint32_t r1 = 15;
    static const uint32_t r2 = 13;
    static const uint32_t m = 5;
    static const uint32_t n = 0xe6546b64;

    uint32_t hash = seed;

    const int nblocks = len / 4;
    const uint32_t *blocks = (const uint32_t *) key;
    int i;
    for (i = 0; i < nblocks; i++) {
        uint32_t k = blocks[i];
        k *= c1;
        k = (k << r1) | (k >> (32 - r1));
        k *= c2;

        hash ^= k;
        hash = ((hash << r2) | (hash >> (32 - r2))) * m + n;
    }

    const uint8_t *tail = (const uint8_t *) (key + nblocks * 4);
    uint32_t k1 = 0;

    switch (len & 3) {
    case 3:
        k1 ^= tail[2] << 16;
    case 2:
        k1 ^= tail[1] << 8;
    case 1:
        k1 ^= tail[0];

        k1 *= c1;
        k1 = (k1 << r1) | (k1 >> (32 - r1));
        k1 *= c2;
        hash ^= k1;
    }

    hash ^= len;
    hash ^= (hash >> 16);
    hash *= 0x85ebca6b;
    hash ^= (hash >> 13);
    hash *= 0xc2b2ae35;
    hash ^= (hash >> 16);

    return hash;
}

int BloomFilter::calcArraySize(int ntmp) const {
    return int(-(ntmp * log(p))/pow(log(2),2));
}

int BloomFilter::calcHashCount(int ntmp, int mtmp) const {
    return (mtmp/ntmp)*log(2);
}
