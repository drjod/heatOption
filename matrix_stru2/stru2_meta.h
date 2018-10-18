#ifndef STRU2_MATRIX_META_H
#define STRU2_MATRIX_META_H


constexpr bool All() { return true; }                                                                                                              
template<typename...Args> constexpr bool All(bool b, Args... args) { return b && All(args...); }

constexpr bool Some() { return false; }                                                                       
template<typename...Args> constexpr bool Some(bool b, Args... args) { return b || Some(args...); }

template<typename... Args> constexpr bool Requesting_element()
{ return All(std::is_convertible<Args, size_type>::value...); }

template<typename... Args> constexpr bool Requesting_slice()                                                                             
{ 
	return All((std::is_convertible<Args, size_type>::value || std::is_same<Args, slice>::value)...) 
				&& Some(std::is_same<Args, slice>::value...);
} 

#endif
