#ifndef BOX-MULLER_TRANSFORM_H_
#define BOX-MULLER_TRANSFORM_H_

#include <utility>
#include <math.h>

template <typename T>
std::pair<T, T> BoxMullerTransformation(const T& value1, const T& value2);

template <typename T>
std::pair<T, T> BoxMullerTransformation(const T&, const T&) {
	// We get two values< which are uniformly distributed at (0, 1) 
	std::pair result; //at the end we will return a pair of values which sre normally distributed at R
	T logarithm = sqrt(-2 log(value1)); // we use some memory to get advance in time
	T cosinus = cos(2 * M_PI * value2); // we use memory for faster calculation of sinus then
	result.first = logarithm * cosinus;
	result.second = logarithm * sqrt(1 - cosinus*cosinus);
	return result;
}

#endif // BOX-MULLER_TRANSFORM_H_
