#ifndef INPUT_XML_HPP
#define INPUT_XML_HPP

#include <iostream>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>
#include <boost/foreach.hpp>
#include "data_set.h"
#include "Vector.cpp"

DataSet read_data_xml(std::istream& is) 
{
	using boost::property_tree::ptree;
	ptree pt;
	read_xml(is, pt);
	DataSet dataSet;
	BOOST_FOREACH(const ptree::value_type& v, pt.get_child("data_set"))
	{
		if(v.first == "european_option")
		{
			EuropeanOption* option = new EuropeanOption;
			option->r = v.second.get<double>("interest_rate");
			option->d = v.second.get<double>("dividend");
			option->sig = v.second.get<double>("volatility");
			option->f = v.second.get<double>("forcing_term");
			option->K = v.second.get<double>("strike_price");
			//option->type = v.second.get<Option::Type>("type");
			dataSet.instruments.push_back(option);
		}
			/*BOOST_FOREACH(const ptree::value_type& v, pt.get_child("domain"))
			{
			Domain domain;
				if(v.first == "underlying")
				{
					domain.underlying.low(v.second.get<double>("minimum")  );
					domain.underlying.high(v.second.get<double>("maximum")  );
				}
				if(v.first == "time")
				{
					domain.time.low(v.second.get<double>("minimum")  );
					domain.time.high(v.second.get<double>("maximum")  );
				}
				dataSet.domain = domain;
			}*/
	}
	return dataSet;
}


#endif
