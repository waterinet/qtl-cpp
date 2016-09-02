#ifndef QTL_NET_HTTP_CLIENT_H_
#define QTL_NET_HTTP_CLIENT_H_

#include <boost/shared_ptr.hpp>

#include "request.h"
#include "response.h"
#include "qtl/errors/error.h"

#include <boost/asio/io_service.hpp>

namespace qtl {
namespace net {
namespace http {

class Client {
public:
    typedef qtl::errors::Error Error;

	Client();
	boost::shared_ptr<Response> Do(boost::shared_ptr<Request> req, Error& err);
	boost::shared_ptr<Response> Get(const std::string& url_str, Error& err);
	boost::shared_ptr<Response> Post(const std::string& url_str, const std::string& body_type, 
			boost::shared_ptr<boost::asio::streambuf> body, Error& err);

private:

    boost::asio::io_service ios_;
};

} // namespace http
} // namespace net
} // namespace qtl

#endif // QTL_NET_HTTP_CLIENT_H_
