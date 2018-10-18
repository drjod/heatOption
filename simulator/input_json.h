#ifndef INPUT_JSON_H
#define INPUT_JSON_H

#include <iostream>
#include "json_grammar.h"


class Domain;
class EuropeanOption;
class DataSet;
template <typename T> class Range;


EuropeanOption* set_europeanOption(parser::Object object);
Domain set_domain(parser::Object object);
void set_range(parser::Object object, Range<double>& range, long& numberOfSteps);
void read_data_json(std::istream& is, DataSet& dataSet);

#endif
