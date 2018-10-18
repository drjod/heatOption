#ifndef pair_HPP
#define pair_HPP

template <class F, class S> class pair
{
public: // ?????
	F first;
	S second;

public:
	pair() { first = F(); second = S();}
	pair(const F& First, const S& Second) { first = First; second = Second;}
};

#endif
