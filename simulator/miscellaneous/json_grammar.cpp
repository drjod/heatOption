#include <boost/spirit/include/qi.hpp>
#include <boost/fusion/include/adapt_struct.hpp>
#include "json_grammar.h"

using namespace boost::spirit;

namespace parser
{



template<typename Iterator, typename Skipper>
struct JSON_grammar : qi::grammar<Iterator, Value(), Skipper>
{
	JSON_grammar() : JSON_grammar::base_type{value}
	{
		object = '{' >> -(pair % ',') >> '}';
		pair = string >> ':' >> value;
		array = '[' >> -(value % ',') >> ']';
		value = string | qi::double_ | qi::long_ | object | array | "true" | "false" | "null";
		string = qi::lexeme[ '"' >> *(qi::char_ - qi::char_('"')) >> '"'];
	}

	qi::rule<std::string::iterator, parser::Object(), Skipper> object;
	qi::rule<std::string::iterator, parser::Pair(), qi::space_type> pair;
	qi::rule<std::string::iterator, parser::Array(), qi::space_type> array;
	qi::rule<std::string::iterator, parser::Value(), qi::space_type> value;
	qi::rule<std::string::iterator, std::string(), qi::space_type> string;
};

struct JSONPrinter : public boost::static_visitor<>
{
	mutable int indentation;
	JSONPrinter() { indentation = 0; }
	void indent() const { std::cout << std::string(indentation, ' '); }
	void operator()(const std::string& v) const { std::cout << '"' << v << '"'; }
	void operator()(const double& v) const { std::cout << v; }
	void operator()(const long& v) const { std::cout << v; }
	//void operator()(const Pair& v) const {  indent(); std::cout << v.first << " => "; }
	void operator()(const Object& v) const;
	void operator()(const Array& v) const;
	void operator()(const bool& v) const { std::cout << (v ? "true": "false"); }
};


void JSONPrinter::operator()(const Object& v) const
{ 
	for(auto it = v.begin(); it != v.end(); ++it)
	{
		std::cout << it->first << " => ";
		boost::apply_visitor(JSONPrinter(), it->second);
		std::cout << '\n';
	}
}
void JSONPrinter::operator()(const Array& v) const
{
	std::cout << '[';
	int i = 0;
	for(auto it = v.begin(); it != v.end(); ++it, ++i)
	{
		boost::apply_visitor(JSONPrinter(), *it);
		if(i != v.size()-1) std::cout << ", ";
	}
	std::cout << ']';
}

}  // end namespace parser


BOOST_FUSION_ADAPT_STRUCT
(
	parser::Pair,
	(std::string, first)
	(parser::Value, second)
)

/* 
Grammar rules:

object
	{}
	{ members }
members
	pair
	pair , members
pair
	string : value
array
	[]
	[ elements ]
elements
	value
	value, elements
value
	string
	number
	object
	array
	"true"
	"false"
	"null"
*/
