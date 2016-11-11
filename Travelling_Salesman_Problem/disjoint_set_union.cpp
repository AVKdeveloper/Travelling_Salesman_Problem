#include "disjoint_set_union.h"

DisjointSetUnion::DisjointSetUnion(const int& number_of_elements)
	: parent_(number_of_elements), size_(number_of_elements) {}

void DisjointSetUnion::MakeSet(const int& element) {
	parent_.at(element) = element;
	size_[element] = 1;
}

void DisjointSetUnion::UnionSets(const int& element1, const int& element2) {
	int leader1 = FindSet(element1);
	int leader2 = FindSet(element2);
	if (leader1 != leader2) {
		if (size_[leader1] > size_[leader2]) {
			parent_[leader2] = leader1;
			size_[leader1] += size_[leader2];
		}
		else {
			parent_[leader1] = leader2;
			size_[leader2] += size_[leader1];
		}
	}
}

int DisjointSetUnion::FindSet(const int& element) {
	int leader = element;// at the end of this method we return the leader of the set
	while (leader != parent_.at(leader)) {
		leader = parent_[leader];
	} // we found the leader of the set
	  // now we need to compress the array of parents, changing the parent of visited nodes
	int variable_element = element; // for changing the parent of the visited nodes
	while (variable_element != leader) {
		int parent_of_variable_element = parent_[variable_element];
		parent_[variable_element] = leader;
		variable_element = parent_of_variable_element;
	}
	return leader;
}

