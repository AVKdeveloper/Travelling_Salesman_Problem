// This program compares the approaching solution of Travelling Salesman Problem (TSP) with the precise answer.
// We get some poins (x, y). x and y are normally distributed on R.
// Approaching solution is made by approaching using Minimum Stanning Tree (algorithm by Boruvka), which requires O(ElogV).
// Precise answer is made using DFS to get round all points, which requires O(n!).
// Statistics of comparing is in "Statistics.out" file.

#include <fstream>
#include <random>
#include <vector>
#include <cstdlib>
#include <iostream>
#include <numeric>
#include <cassert>
#include "graph_for_mst.h"
#include "box-muller_transform.h"
#include "precise_solution_for_tsp.h"

int main()
{
	const int kMaxVerticesQuantity = 10;
	const int kTestQuantity = 5;
	const bool kDetailedReport = true; // Write datils of every test in console? 

	std::fstream file;
	file.open("Statistics.out", std::fstream::out);
	file << "Here is statistics on comparing the precise answer and approaching answer:\n";
	file << "Quantity of points Average precise answer Average approaching answer Difference\n";
	for (int vertices_quantity = 3; vertices_quantity <= kMaxVerticesQuantity; ++vertices_quantity) { // for different quantities of vertices
		std::vector<double> precise_answers(kTestQuantity);
		std::vector<double> approaching_answers(kTestQuantity);
		for (int test_number = 0; test_number < kTestQuantity; ++test_number) {
			std::vector<std::pair<double, double>> points(vertices_quantity);
			points = GetVectorOfUniformlyDistributedPoints<double>(vertices_quantity, kDetailedReport, test_number);
			GraphForMst<double> graph(vertices_quantity, vertices_quantity*(vertices_quantity-1));
			graph.FillInTreeWithPoints(points);
			double approaching_answer = FindLengthOfCycle<double>(points, graph.GetSortedVerticesOfMstIntoCycle());
			double precise_answer = FindBestHamiltonianCycle(points); 
			if (kDetailedReport) {
				std::cout << "Approaching answer(using mst tree): " << approaching_answer << "\n";
				std::cout << "Precise answer(using DFS): " << precise_answer << "\n\n";
			}
			assert(approaching_answer >= precise_answer); // check that the best answer is better than approaching
			approaching_answers[test_number] = approaching_answer;
			precise_answers[test_number] = precise_answer;
		}
		double average_precise_answer = std::accumulate(precise_answers.begin(), precise_answers.end(), 0.0) / precise_answers.size();
		double average_approaching_answer = std::accumulate(approaching_answers.begin(), approaching_answers.end(), 0.0) / approaching_answers.size();
		file << vertices_quantity << "                  " << average_precise_answer << "                " << average_approaching_answer <<
			    "                    " << (average_approaching_answer - average_precise_answer) / average_precise_answer << " % \n";
	}
	file.close();
	if (kDetailedReport) {
		system("pause");
	}
	return 0;
}