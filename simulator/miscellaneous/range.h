#ifndef Range_HPP
#define Range_HPP

#include <cassert>

template <typename T = double> class Range
{
public:
	Range() {}
	Range(const T& _lo, const T& _hi) : lo(_lo), hi(_hi)
		{ assert(lo <= hi); }
	Range(const Range<T>& r2) : lo(r2.lo), hi(r2.hi) {}
	Range<T>& operator = (const Range<T>& r2)
		{ lo = r2.lo; hi = r2.hi; return *this; }
	virtual ~Range() {}

	void low(const T& _lo) { lo = _lo; }
	void high(const T& _hi) { hi = _hi; }

	T low() const { return lo; }
	T high() const { return hi; }

	T spread() const { return hi-lo; }

	// Boolean functions
	bool left(const T& value) const { return value < lo; }
	bool right(const T& value) const { return value > hi; }
	bool contains(const T& value) const
		{ return (value >= lo && value <= hi); }

	// Utility functions
	//Vector<T, int> mesh(const int& nSteps) const;
private:
	T lo;
	T hi;
};

/*
template<typename T> Vector<T, int> Range<T>::mesh(const int& nSteps) const
{
	T h = (hi - lo) / nSteps;
	Vector<T, int> res(nSteps+1, 1);
	T val = lo;
	for(int i = 1; i <= nSteps+1; ++i)
	{
		res[i] = val;
		val += h;
	}
	return res;
}
*/

#endif
