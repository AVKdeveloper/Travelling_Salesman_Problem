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

#endif // BOX_MULLER_TRANSFORM_H_
