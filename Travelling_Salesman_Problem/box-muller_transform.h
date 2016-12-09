#ifndef BOX_MULLER_TRANSFORM_H_
#define BOX_MULLER_TRANSFORM_H_

#include <utility>
#include <cmath>

template <typename T>
std::pair<T, T> BoxMullerTransformation(const T& value1, const T& value2);

template <typename T>
std::pair<T, T> BoxMullerTransformation(const T& value1, const T& value2) {
	// We get two values< which are uniformly distributed at (0, 1) 
	std::pair<T, T> result; //at the end we will return a pair of values which sre normally distributed at R
	T logarithm = sqrt(-2 * log(value1)); // we use some memory to get advance in time
	T cosinus = cos(2 * 3.14159265358979323846 * value2); // we use memory for faster calculation of sinus then
	result.first = logarithm * cosinus;
	result.second = logarithm * sqrt(1 - cosinus*cosinus);
	return result;
}

template <typename T>
std::vector<std::pair<T, T>> GetVectorOfUniformlyDistributedPoints(const int& points_quantity, const int& test_number) {
	std::vector<std::pair<double, double>> points(points_quantity);
	for (int i = 0; i < points_quantity; ++i) { // generating random points 
		points[i] = BoxMullerTransformation<T>(1 - rand() / ((T)RAND_MAX + 1), 1 - rand() / ((T)RAND_MAX + 1));
	} // generated random points
	return points;
}

template<typename T>
T FindLengthOfCycle(std::vector<std::pair<T, T>> points, std::vector<int> order_of_points) {
	T length_of_way = 0;
	for (int i = 0; i < points.size() - 1; ++i) {
		length_of_way += sqrt(pow(points[order_of_points[i]].first - points[order_of_points[i + 1]].first, 2) +
			                  pow(points[order_of_points[i]].second - points[order_of_points[i + 1]].second, 2));
	}
	length_of_way += sqrt(pow(points[order_of_points[0]].first - points[order_of_points[points.size() - 1]].first, 2) +
		                  pow(points[order_of_points[0]].second - points[order_of_points[points.size() - 1]].second, 2));
	return length_of_way;
}

#endif // BOX_MULLER_TRANSFORM_H_
