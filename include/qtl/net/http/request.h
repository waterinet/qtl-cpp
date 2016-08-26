#ifndef QTL_NET_HTTP_REQUEST_H_
#define QTL_NET_HTTP_REQUEST_H_

#include <string>
#include <boost/shared_ptr.hpp>
#include <boost/asio/streambuf.hpp>

#include "header.h"
#include "qtl/net/url/url.h"

namespace qtl {
namespace net {
namespace http {

struct Request {
	typedef std::string string;

	string method;
	boost::shared_ptr<url::URL> url;
	string proto;

    Header header;
	boost::shared_ptr<boost::asio::streambuf> body;

    void Write(boost::asio::streambuf& buf);
};

boost::shared_ptr<Request> ReadRequest(boost::asio::streambuf& buf);

boost::shared_ptr<Request> NewRequest(const std::string& method, const std::string& url, 
		boost::shared_ptr<boost::asio::streambuf> buf, errors::Error& err);

} // namespace http
} // namespace net
} // namespace qtl

#endif // QTL_NET_HTTP_REQUEST_H_
