#ifndef GRAPH_FOR_MST_H_
#define GRAPH_FOR_MST_H_

#include <list>
#include <unordered_set>
#include <climits>
#include <limits>
#include "disjoint_set_union.h"

template <typename T>
struct Edge {
	int from_;
	int to_;
	T weight_;

	bool operator==(const Edge& another_edge) const;
};

namespace std {
	template <typename T>
	class hash<Edge<T>> {
	public:
		size_t operator()(const Edge<T>& edge) const {
			hash<T> hash_for_template_type;
			hash<int> hash_for_int;
			return hash_for_template_type(edge.weight_) ^ hash_for_int(edge.from_) ^ hash_for_int(edge.to_);
		}
	};
}

template <typename T>
class GraphForMst {
	int number_of_vertices_;
	int number_of_edges_;
	std::list<Edge<T>> edges_;
public:
	GraphForMst(const int& number_of_vertices, const int& number_of_edges);
	void AddEdge(const Edge<T>& edge);
	std::unordered_set<Edge<T>> BuiltMstByBoruvka() const;
};

#include "graph_for_mst.inl"
#endif // GRAPH_FOR_MST_H_

