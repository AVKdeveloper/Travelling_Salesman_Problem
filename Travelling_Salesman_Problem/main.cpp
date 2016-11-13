// This program compares the approaching solution of Travelling Salesman Problem (TSP) with the best solution
// Approaching solution is made by Minimum Stanning Tree (algorithm by Boruvka)
// 

#include <fstream>
#include <random>
#include <vector>
#include "graph_for_mst.h"
#include "box-muller_transform.h"

int main()
{

	/*
	for (int i = 2; i < 10; ++i) {
		std::vector< std::pair<double, double> > vertices();
		for (int j = 0; j < i; ++j) {
			std::pair<double, double> uniformly_distributed_values = {};
		}
	}
	*/
	
	std::fstream file;
	file.open("kruskal.in", std::fstream::in);
	int number_of_vertices, number_of_edges;
	file >> number_of_vertices >> number_of_edges; // getting init info from file
	GraphForMst<int> graph(number_of_vertices, number_of_edges);
	for (int i = 0; i < number_of_edges; ++i) {
		Edge<int> edge;
		file >> edge.from_ >> edge.to_ >> edge.weight_;
		edge.from_--;
		edge.to_--;
		graph.AddEdge(edge);
	} // end of init graph
	file.close();

	//start of the Boruvka's algorithm ->
	std::unordered_set<Edge<int>> mst_tree = graph.BuiltMstByBoruvka();
	long long sum_of_weights = 0;
	for (Edge<int> edge : mst_tree) {
		sum_of_weights += edge.weight_;
	} // counted the sum - answer for owr task

	file.open("kruskal.out", std::fstream::out);
	file << sum_of_weights; // output
	file.close();

	return 0;
}