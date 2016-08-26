#include "qtl/net/http/response.h"
#include <iostream>
#include <boost/format.hpp>
#include <boost/make_shared.hpp>

namespace qtl {
namespace net {
namespace http {

void Response::Write(boost::asio::streambuf& buf) {
	std::ostream resp_stream(&buf);
    resp_stream << proto << " " << status << "\r\n";
	header.Write(buf);
	resp_stream << body.get(); // content of body is consumed
}

boost::shared_ptr<Response> ReadResponse(boost::asio::streambuf& buf) {
	using namespace boost;
	std::istream resp_stream(&buf);
	shared_ptr<Response> resp(new Response);

	std::string status_str;
	std::string line;
	resp_stream >> resp->proto;
	resp_stream >> resp->status_code;
	resp_stream >> status_str;
    resp->status = boost::str(format("%d %s") % status_str % resp->status_code);
	std::getline(resp_stream, line); // comsume whatever left in the status line
	// read until blank line
	while (std::getline(resp_stream, line) && line != "\r") {
		// TODO
	}
	resp->body = boost::make_shared<boost::asio::streambuf>(); 
	resp_stream >> resp->body.get();
	return resp;
}

} // namespace http
} // namespace net
} // namespace qtl
