#include "graph_for_mst.h"

bool Edge::operator==(const Edge& another_edge) const {
	return (from_ == another_edge.from_)*  (to_ == another_edge.to_) * (weight_ == another_edge.weight_);
}

GraphForMst::GraphForMst(const int& number_of_vertices, const int& number_of_edges) {
	number_of_vertices_ = number_of_vertices;
	number_of_edges_ = number_of_edges;
}

void GraphForMst::AddEdge(const Edge& edge) {
	edges_.push_back(edge);
}

std::unordered_set<Edge> GraphForMst::BuiltMstByBoruvka() const {
	DisjointSetUnion connected_components(number_of_vertices_);
	for (int i = 0; i < number_of_vertices_; ++i) {
		connected_components.MakeSet(i);
	} // prepared components of connection for algorithm
	std::vector<Edge> minimum_edge_for_component(number_of_vertices_);
	const int kInfinite = 200000; // the +oo (infinite)
	std::unordered_set<Edge> edges_of_mst; // in the end it will be MST tree
	while (edges_of_mst.size() < number_of_vertices_ - 1) {
		for (int i = 0; i < number_of_vertices_; ++i) {
			minimum_edge_for_component[i].weight_ = kInfinite;
		} // heve set init edges for every component of connection
		for (Edge edge : edges_) {
			if (connected_components.FindSet(edge.from_) != connected_components.FindSet(edge.to_)) {
				if (minimum_edge_for_component[connected_components.FindSet(edge.from_)].weight_ > edge.weight_) {
					minimum_edge_for_component[connected_components.FindSet(edge.from_)] = edge;
				}
				if (minimum_edge_for_component[connected_components.FindSet(edge.to_)].weight_ > edge.weight_) {
					minimum_edge_for_component[connected_components.FindSet(edge.to_)] = edge;
				}
			}
		} // have set best edges for every component of connection
		for (int i = 0; i < number_of_vertices_; ++i) {
			if (minimum_edge_for_component[i].weight_ < kInfinite) {
				edges_of_mst.insert(minimum_edge_for_component[i]);
				connected_components.UnionSets(minimum_edge_for_component[i].from_, minimum_edge_for_component[i].to_);
			} // added new edges and union components, which were connected by this edges 
		}
	}
	return edges_of_mst;
}


