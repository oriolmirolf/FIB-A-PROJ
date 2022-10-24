/** @file diccSortedVector.cc
    @brief Implementación de la clase SortedVector
*/
#include "diccSortedVector.hh"

SortedVector::SortedVector(const int& n) {
	this->n = n;
}

void SortedVector::insert(const string& s) {
	if ((int)v.size() == this->n) return;
	v.push_back(s);
	if ((int)v.size() == this->n) sort(v.begin(), v.end());
}

bool SortedVector::search(const string& s) const {
  	return binary_search(v.begin(), v.end(), s);
}

bool SortedVector::prefix(const string& s) const {
  	auto l = lower_bound(v.begin(), v.end(), s);
  	if (l == v.end()) return false;
  	string ss = v[l - v.begin()];
  	return isPrefix(s, ss);
}

bool SortedVector::isPrefix(const string& p, const string& s) const {
	bool b = mismatch(p.begin(), p.end(), s.begin()).first == p.end();
	return b;
}

