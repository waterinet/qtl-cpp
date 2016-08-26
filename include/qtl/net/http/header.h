#ifndef QTL_NET_HTTP_HEADER_H_
#define QTL_NET_HTTP_HEADER_H_
#include <map>
#include <string>
#include <vector>
#include <boost/asio/streambuf.hpp>

namespace qtl {
namespace net {
namespace http {

struct Header {
	typedef std::string string;

	std::map< string, std::vector<string> > fields;

	void Add(const string& key, const string& val);
	string Get(const string& key) const;
	void Set(const string& key, const string& val);
	void Write(boost::asio::streambuf& buf) const;
};

} // namespace http
} // namespace net
} // namespace qtl

#endif // QTL_NET_HTTP_HEADER_H_
