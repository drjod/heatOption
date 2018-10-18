#ifndef MY_MATH_H
#define MY_MATH_H

#include <cmath>

double coth(const double& value)
{
	const double tmp = exp(-2 * value);
	return (1. + tmp) / (1. - tmp);
}



#endif
