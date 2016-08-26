#ifndef QTL_NET_HTTP_RESPONSE_H_
#define QTL_NET_HTTP_RESPONSE_H_

#include <string>
#include <boost/shared_ptr.hpp>
#include <boost/asio/streambuf.hpp>

#include "header.h"

namespace qtl {
namespace net {
namespace http {

struct Response {
	typedef std::string string;

	string status;   // e.g. "200 OK"
	int status_code; // e.g. 200
	string proto;    // e.g. "HTTP/1.0"

	Header header;
	boost::shared_ptr<boost::asio::streambuf> body;

	void Write(boost::asio::streambuf& buf);
};

boost::shared_ptr<Response> ReadResponse(boost::asio::streambuf& buf);

} // namespace http
} // namespace net
} // namespace qtl

#endif // QTL_NET_HTTP_RESPONSE_H_
