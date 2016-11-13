#ifndef PRECISE_SOLUTION_FOR_TSP_H_
#define PRECISE_SOLUTION_FOR_TSP_H_

#include <limits>
#include <vector>

template <typename T>
T FindBestHamiltonianCycle(const std::vector<std::pair<T, T>>& points);

template <typename T>
void DFS(const std::vector<std::pair<T, T>>& points, std::vector<int>& sequence_of_vertices, T& currently_length, T& min_cycle);

template <typename T>
T FindBestHamiltonianCycle(const std::vector<std::pair<T, T>>& points) {
	T min_cycle = std::numeric_limits<T>::max();
	T currently_length = 0;
	std::vector<int> sequence_of_vertices;
	sequence_of_vertices.push_back(0); //we starting with the 0th point(every point will be in sequence) 
	DFS(points, sequence_of_vertices, currently_length, min_cycle);
	return min_cycle;
}

template <typename T>
void DFS(const std::vector<std::pair<T, T>>& points, std::vector<int>& sequence_of_vertices, T& currently_length, T& min_cycle) {
	if (sequence_of_vertices.size() < points.size() - 1) { // if the next vertex will not be the last
		for (int next_vertex = 1; next_vertex < points.size(); ++next_vertex) { // trying to add new vertex
			if (find(sequence_of_vertices.begin(), sequence_of_vertices.end(), next_vertex) == sequence_of_vertices.end()) { //adding unique new vertex
				currently_length += sqrt(pow(points[next_vertex].first - points[sequence_of_vertices[sequence_of_vertices.size() - 1]].first, 2) +
					                     pow(points[next_vertex].second - points[sequence_of_vertices[sequence_of_vertices.size() - 1]].second, 2));
				sequence_of_vertices.push_back(next_vertex);
				if (currently_length < min_cycle) { // in this case we trying to continue our way
					DFS(points, sequence_of_vertices, currently_length, min_cycle);
				}
				sequence_of_vertices.pop_back();
				currently_length -= sqrt(pow(points[next_vertex].first - points[sequence_of_vertices[sequence_of_vertices.size() - 1]].first, 2) +
					pow(points[next_vertex].second - points[sequence_of_vertices[sequence_of_vertices.size() - 1]].second, 2));
			}
		}
	}
	else if (sequence_of_vertices.size() < points.size()) { // if the next vertex will be the last
		for (int next_vertex = 1; next_vertex < points.size(); ++next_vertex) { // trying to add new vertex
			if (find(sequence_of_vertices.begin(), sequence_of_vertices.end(), next_vertex) == sequence_of_vertices.end()) { //adding unique new vertex
				currently_length += sqrt(pow(points[next_vertex].first - points[sequence_of_vertices[sequence_of_vertices.size() - 1]].first, 2) +
					                     pow(points[next_vertex].second - points[sequence_of_vertices[sequence_of_vertices.size() - 1]].second, 2));
				sequence_of_vertices.push_back(next_vertex);
				// in the next line we lock our path into cycle
				currently_length += sqrt(pow(points[0].first - points[sequence_of_vertices[sequence_of_vertices.size() - 1]].first, 2) +
					                     pow(points[0].second - points[sequence_of_vertices[sequence_of_vertices.size() - 1]].second, 2));
				if (currently_length < min_cycle) { // if the new cycle is better
					// we update the best (min) cycle
					min_cycle = currently_length;
				}
				currently_length -= sqrt(pow(points[0].first - points[sequence_of_vertices[sequence_of_vertices.size() - 1]].first, 2) +
					                     pow(points[0].second - points[sequence_of_vertices[sequence_of_vertices.size() - 1]].second, 2));
				sequence_of_vertices.pop_back();
				currently_length -= sqrt(pow(points[next_vertex].first - points[sequence_of_vertices[sequence_of_vertices.size() - 1]].first, 2) +
					pow(points[next_vertex].second - points[sequence_of_vertices[sequence_of_vertices.size() - 1]].second, 2));
			}
		}
	}
}

#endif // PRECISE_SOLUTION_FOR_TSP_H_