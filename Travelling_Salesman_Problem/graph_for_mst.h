#ifndef GRAPH_FOR_MST
#define GRAPH_FOR_MST

#include <list>
#include <unordered_set>
#include "disjoint_set_union.h"

struct Edge {
	int from_;
	int to_;
	int weight_;

	bool operator==(const Edge& another_edge) const;
};

namespace std {
	template<>
	class hash<Edge> {
	public:
		size_t operator()(const Edge& edge) const {
			hash<int> hash_for_int;
			return hash_for_int(edge.weight_) ^ hash_for_int(edge.from_) ^ hash_for_int(edge.to_);
		}
	};
}


class GraphForMst {
	int number_of_vertices_;
	int number_of_edges_;
	std::list<Edge> edges_;
public:
	GraphForMst(const int& number_of_vertices, const int& number_of_edges);
	void AddEdge(const Edge& edge);
	std::unordered_set<Edge> BuiltMstByBoruvka() const;
};

#endif

