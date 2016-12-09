template <typename T>
bool Edge<T>::operator==(const Edge<T>& another_edge) const {
	return (from_ == another_edge.from_)*  (to_ == another_edge.to_) * (weight_ == another_edge.weight_);
}

template <typename T>
GraphForMst<T>::GraphForMst(const int& number_of_vertices, const int& number_of_edges) {
	number_of_vertices_ = number_of_vertices;
	number_of_edges_ = number_of_edges;
}

template <typename T>
void GraphForMst<T>::AddEdge(const Edge<T>& edge) {
	edges_.push_back(edge);
}

template <typename T>
void GraphForMst<T>::FillInTreeWithPoints(std::vector<std::pair<T, T>> points) {
	for (int i = 0; i < points.size(); ++i) { // adding edges into graph
		for (int j = 0; j < points.size(); ++j) {
			Edge<double> edge;
			edge.from_ = i;
			edge.to_ = j;
			edge.weight_ = sqrt(pow(points[i].first - points[j].first, 2) + pow(points[i].second - points[j].second, 2));
			if (i != j) {
				AddEdge(edge);
			}
		}
	} // added edges into graph
}

template <typename T>
std::unordered_set<Edge<T>> GraphForMst<T>::BuiltMstByBoruvka() const {
	DisjointSetUnion connected_components(number_of_vertices_);
	for (int i = 0; i < number_of_vertices_; ++i) {
		connected_components.MakeSet(i);
	} // prepared components of connection (separate vertices) for algorithm
	std::vector<Edge<T>> minimum_edge_for_component(number_of_vertices_);
	const T kInfinite = std::numeric_limits<T>::max(); // the +oo (infinity) or max for this type
	std::unordered_set<Edge<T>> edges_of_mst; // in the end it will be MST tree
	while (edges_of_mst.size() < number_of_vertices_ - 1) {
		for (int i = 0; i < number_of_vertices_; ++i) {
			minimum_edge_for_component[i].weight_ = kInfinite;
		} // have already set init edges for every component of connection
		for (Edge<T> edge : edges_) {
			if (connected_components.FindSet(edge.from_) != connected_components.FindSet(edge.to_)) {
				if (minimum_edge_for_component[connected_components.FindSet(edge.from_)].weight_ > edge.weight_) {
					minimum_edge_for_component[connected_components.FindSet(edge.from_)] = edge;
				}
				if (minimum_edge_for_component[connected_components.FindSet(edge.to_)].weight_ > edge.weight_) {
					minimum_edge_for_component[connected_components.FindSet(edge.to_)] = edge;
				}
			}
		} // have already set best edges for every component of connection
		for (int i = 0; i < number_of_vertices_; ++i) {
			if (minimum_edge_for_component[i].weight_ < kInfinite) {
				edges_of_mst.insert(minimum_edge_for_component[i]);
				connected_components.UnionSets(minimum_edge_for_component[i].from_, minimum_edge_for_component[i].to_);
			} // added new edges and union components, which were connected by this edges 
		}
	}
	return edges_of_mst;
}

template <typename T>
std::vector<int> GraphForMst<T>::GetSortedVerticesOfMstIntoCycle() const {
	std::unordered_set<Edge<double>> mst_edges = BuiltMstByBoruvka();
	std::multimap<int, int> map_of_edges; // vertex_from, vertex_to
	for (Edge<T> edge : mst_edges) {
		map_of_edges.insert(std::make_pair(edge.from_, edge.to_));
		map_of_edges.insert(std::make_pair(edge.to_, edge.from_));
	}
	std::vector<int> sorted_vertices;
	std::vector<bool> viseted_vertices(number_of_vertices_, false);
	std::stack<int> stack_of_vertices;
	stack_of_vertices.push(mst_edges.begin()->from_);
	while (!stack_of_vertices.empty()) {
		int current_vertex = stack_of_vertices.top();
		stack_of_vertices.pop();
		if (viseted_vertices[current_vertex]) { // if we are in this vertex not for the first time
			continue;
		}
		sorted_vertices.push_back(current_vertex);
		viseted_vertices[current_vertex] = true;
		std::multimap<int, int>::iterator iterator = map_of_edges.find(current_vertex);
		while (iterator != map_of_edges.end() && iterator->first == current_vertex) {
			int next_vertex = iterator->second;
			if (!viseted_vertices[next_vertex]) {
				stack_of_vertices.push(next_vertex);
			}
			++iterator;
		}
	}
	return sorted_vertices;
}


