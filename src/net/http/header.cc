#include "qtl/net/http/header.h"
#include <iostream>
#include <boost/foreach.hpp>
#include <boost/algorithm/string/join.hpp>

namespace qtl {
namespace net {
namespace http {

using std::string;

// Add adds the key, value pair to the header. It appends to any existing values associated with key.
void Header::Add(const string& key, const string& val) {
	fields[key].push_back(val);
}

// Get gets the first value associated with the given key. 
// If there are no values associated with the key, Get returns "". 
string Header::Get(const string& key) const {
    std::map< string, std::vector<string> >::
		const_iterator it = fields.find(key);
	if (it == fields.end() || it->second.empty()) {
		return "";
	}
    return it->second.front();
}

// Set sets the header entries associated with key to the single element value. 
// It replaces any existing values associated with key.
void Header::Set(const string& key, const string& val) {
	fields[key].clear();
	fields[key].push_back(val);
}

// Write writes header to a streambuf
void Header::Write(boost::asio::streambuf& buf) const {
	using namespace boost::algorithm;
	typedef std::map< string, std::vector<string> >::value_type value_type;
	std::ostream header_stream(&buf);
    BOOST_FOREACH(const value_type& f, fields) {
		if (f.second.size() > 0) {
		    header_stream << f.first << ": " << join(f.second, ",") << "\r\n";
		}
	}
	header_stream << "\r\n";
}

} // namespace http
} // namespace net
} // namespace qtl
