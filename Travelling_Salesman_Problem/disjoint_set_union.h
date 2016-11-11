#ifndef DISJOINT_SET_UNION
#define DISJOINT_SET_UNION

#include <vector>

class DisjointSetUnion {
	std::vector<int> parent_;
	std::vector<int> size_; // the number of successors
public:
	DisjointSetUnion(const int& number_of_elements);
	void MakeSet(const int& element);
	void UnionSets(const int& element1, const int& element2);
	int FindSet(const int& element);
};

#endif
