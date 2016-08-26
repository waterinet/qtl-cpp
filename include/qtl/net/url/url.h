#ifndef QTL_NET_URL_URL_H_
#define QTL_NET_URL_URL_H_

#include <string>
#include <boost/shared_ptr.hpp>
#include "qtl/errors/error.h"

namespace qtl {
namespace net {
namespace url {

// The general form represented is:
// scheme://[userinfo@]host/path[?query][#fragment]
// url encoding is not taken into consideration yet 
struct URL {
	typedef std::string string;

	string scheme;
	string host;
	string path;
	string query;
	string fragment;
};

boost::shared_ptr<URL> Parse(const std::string& rawurl, qtl::errors::Error& err);

} // namespace url
} // namespace net
} // namespace qtl

#endif // QTL_NET_URL_URL_H
