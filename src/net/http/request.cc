#include "qtl/net/http/request.h"
#include <iostream>
#include <boost/lexical_cast.hpp>

namespace qtl {
namespace net {
namespace http {

void Request::Write(boost::asio::streambuf& buf) {
	std::ostream req_stream(&buf);
    req_stream << method << " " << url->path;
	if (!url->query.empty()) {
		req_stream << "?" << url->query;
	}
	req_stream << " " << proto << "\r\n";
	header.Write(buf);
    req_stream << body.get(); // content of body is consumed 
}

boost::shared_ptr<Request> ReadRequest(boost::asio::streambuf&) {
    // TODO
	return boost::shared_ptr<Request>();
}

boost::shared_ptr<Request> NewRequest(const std::string& method, const std::string& url_str,
		boost::shared_ptr<boost::asio::streambuf> buf, errors::Error& err) {
	errors::Error url_err;
	boost::shared_ptr<url::URL> url = url::Parse(url_str, url_err);
    if (url_err) {
        err = url_err;
        return boost::shared_ptr<Request>();
    }
	boost::shared_ptr<Request> req = boost::shared_ptr<Request>(new Request);
    req->method = method.empty() ? "GET" : method;
    req->proto = "HTTP/1.1";
    req->url = url;
    req->header.Set("Host", url->host);
    req->header.Set("Connection", "close");
    req->header.Add("Accept", "*/*");
	if (buf) {
		req->header.Set("Content-Length", boost::lexical_cast<std::string>(buf->size()));
	    req->body = buf;
	}

	return req;
}

} // namespace http
} // namespace net
} // namespace qtl
