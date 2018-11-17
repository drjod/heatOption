
#ifndef DFunction_HPP
#define DFunction_HPP


//#include <map>
#include "pair.h"
#include <functional>


template <class D, class R> class Function {};
template <class D, class R> class DFunction: public Function <D, R> {};


template <class D, class R> class AtomicDFunction : public DFunction<D, R>
{
public:
	AtomicDFunction() { f = 0; }
	AtomicDFunction (const std::function<R(const D& x)>& _f) : f(_f) {}
	//AtomicDFunction (R (*_f)(const D& x)) : f(_f) {}
	AtomicDFunction(const AtomicDFunction<D, R>& f2) : f(f2.f) {}
	virtual ~AtomicDFunction() {}
	AtomicDFunction<D, R>& operator=(const AtomicDFunction<D, R>& f2)
	{ f = f2.f; return *this; }

	virtual R calculate(const D& x) const { return f(x); }  // { return (*f)(x); }
	void function(std::function<R(const D& x)> _f) { f = _f; }
	//void function(R (*_f)(const D& x)) { f = _f; }
	R add(const AtomicDFunction<D,R>& f2, const D& x) const
	{ return calculate(x) + f2.calculate(x); }
private:
	//R (*f)(const D& x);
	std::function<R(const D& x)> f;
};

template <class D1, class D2, class R> class TwoVarDFunction : public AtomicDFunction<pair<D1, D2>, R>
{
public:
	TwoVarDFunction() : AtomicDFunction<pair<D1, D2>, R>() {}
	//TwoVarDFunction (R (*_f)(const pair<D1,D2>&)) : AtomicDFunction<pair<D1, D2>, R>(_f) {}
	TwoVarDFunction (const std::function<R(const pair<D1, D2>&) >&  _f) : AtomicDFunction<pair<D1, D2>, R>(_f) {}
	TwoVarDFunction(const TwoVarDFunction<D1,D2,R>& f2) : AtomicDFunction<pair<D1, D2>, R>(f2) {}
	virtual ~TwoVarDFunction() {}

	TwoVarDFunction<D1, D2, R>& operator = (const TwoVarDFunction<D1, D2,R>& f2)
	{ AtomicDFunction<pair<D1, D2>, R>::operator=(f2); return *this; }
	R calculate2d(const D1& d1, const D2& d2) const
	{ return this->calculate(pair<D1, D2>(d1, d2));  }
};

#endif
