#ifndef JSON_GRAMMAR_H
#define JSON_GRAMMAR_H

#include <boost/spirit/include/qi.hpp>                                                                        
#include <boost/fusion/include/adapt_struct.hpp>
#include <boost/variant.hpp>
#include <map>
#include <string>
#include <vector>

using namespace boost::spirit;
namespace parser
{

struct Object;
struct Array;
typedef boost::variant<std::string, long, double, Object, Array, bool> Value;
typedef std::pair<std::string, Value> Pair;

struct Object : std::map<std::string, Value> {};  // !!!map, vector not virtual
struct Array : std::vector<Value> {};

}

#endif
