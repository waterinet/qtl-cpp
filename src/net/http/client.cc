#include "qtl/net/http/client.h"
#include "qtl/net/url/url.h"
#include "qtl/strings/strings.h"

#include <iostream>
#include <boost/asio.hpp>

namespace qtl {
namespace net {
namespace http {

using std::string;
using boost::asio::ip::tcp;

Client::Client() {
}

boost::shared_ptr<Response> Client::Do(boost::shared_ptr<Request> req, Error& err) {
	if (!req) {
		err = Error("request is null");
		return boost::shared_ptr<Response>();
	}

	// A string identifying a location.
	// May be a descriptive name or a numeric address string.
	string host; 	
	// A string identifying the requested service. 
	// This may be a descriptive name or a numeric string corresponding to a port number.
	string service; 
	strings::Split(req->header.Get("Host"), host, service, ":", true);
	if (host.empty()) {
		err = Error("host is empty");
		return boost::shared_ptr<Response>();
	}
	if (service.empty()) {
		service = "http";
	}
	boost::system::error_code ec;
	tcp::resolver resolver(ios_);
	tcp::resolver::query query(host, service);
	tcp::resolver::iterator endpoint_iterator = resolver.resolve(query, ec);
	if (ec) {
		err = Error("fail to resolve host: " + ec.message());
		return boost::shared_ptr<Response>();
	}
	
	tcp::socket socket(ios_);
	boost::asio::connect(socket, endpoint_iterator, ec);
	if (ec) {
		err = Error("fail to connect to server: " + ec.message());
		return boost::shared_ptr<Response>();
	}

	boost::shared_ptr<Response> resp;
	try {
		boost::asio::streambuf request_buf;
		req->Write(request_buf);
		boost::asio::write(socket, request_buf);

		boost::asio::streambuf response_buf;
		boost::asio::read(socket, response_buf, boost::asio::transfer_all(), ec);
		if (ec != boost::asio::error::eof) {
			throw boost::system::system_error(ec);
		}
		resp = ReadResponse(response_buf); 

	} catch (std::exception& e) {
		err = Error("fail to issue http request: " + string(e.what()));
		return boost::shared_ptr<Response>();
	}
    
	err = Error();
	return resp;
}

boost::shared_ptr<Response> Client::Get(const std::string& url_str, Error& err) {
	boost::shared_ptr<boost::asio::streambuf> buf; // empty buf
    boost::shared_ptr<Request> req = NewRequest("GET", url_str, buf, err);
	if (err) {
		return boost::shared_ptr<Response>();
	}
	return Do(req, err);
}

boost::shared_ptr<Response> Client::Post(const std::string& url_str, const std::string& body_type, 
		boost::shared_ptr<boost::asio::streambuf> body, Error& err) {
	 boost::shared_ptr<Request> req = NewRequest("POST", url_str, body, err);
	 if (err) {
		 return boost::shared_ptr<Response>();
	 }
	 req->header.Set("Content-Type", body_type);
	 return Do(req, err);
}

} // namespace http
} // namespace net
} // namespace qtl
