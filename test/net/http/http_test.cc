#include <iostream>

#include "qtl/net/http/client.h"
#include <boost/make_shared.hpp>

using namespace std;
using namespace qtl;

void RequestTest();
void ResponseTest();
void HttpClientTest();
void HttpClientTest2();
void HttpClientTest3();

int main() {
	cout << "-----RequestTest-----" << endl; 
	RequestTest();
	cout << "-----ResponseTest-----" << endl;
	ResponseTest();
	//cout << "-----HttpClientTest-----" << endl;
	//HttpClientTest();
	cout << "-----HttpClientTest2-----" << endl;
	HttpClientTest2();
	cout << "-----HttpClientTest3-----" << endl;
	HttpClientTest3();
}

void RequestTest() {
	net::http::Request req;
	errors::Error url_err;
    req.method = "GET";
	req.url = net::url::Parse("/tutorials/other/top-20-mysql-best-practices/", url_err);
	if (url_err) {
		cout << "url: " << url_err.Message() << endl;
		return;
	}
    req.proto = "HTTP/1.1";
    req.header.Set("Host", "net.tutsplus.com");
    req.header.Add("Accept-Encoding", "gzip");
    req.header.Add("Accept-Encoding", "deflate");
    
    boost::asio::streambuf buf;
    req.Write(buf); 
    cout << &buf;
}

void ResponseTest() {
	boost::asio::streambuf buf;
	std::ostream resp_stream(&buf);
	resp_stream << "HTTP/1.x 200 OK\r\n";
	resp_stream << "Transfer-Encoding: chunked\r\n";

	boost::shared_ptr<net::http::Response> resp = net::http::ReadResponse(buf);
	cout << "status code: [" << resp->status_code <<  "]" << endl;
	cout << "[" << resp->proto << " " << resp->status << "]" << endl;
}

void HttpClientTest() {
	boost::shared_ptr<net::http::Request> req = 
		boost::shared_ptr<net::http::Request>(new net::http::Request);
	errors::Error url_err;
	req->method = "GET";
	req->url = net::url::Parse("/", url_err);
	if (url_err) {
		cout << "url: " << url_err.Message() << endl;
		return;
	}
	req->proto = "HTTP/1.1";
	req->header.Set("Host", "www.baidu.com");
	req->header.Set("Connection", "close");
	req->header.Add("Accept", "text/html");
	req->header.Add("Accept", "application/xhtml+xml");

	net::http::Client client;
	errors::Error err;
	boost::shared_ptr<net::http::Response> resp = client.Do(req, err);
    if (err) {
		cout << "error: " << err.Message() << endl;
		return;
	}
	if (resp->status_code != 200) {
		cout << "status code: " << resp->status_code << endl;
		return;
	}
	cout << resp->proto << " " << resp->status << endl;
	cout << resp->body.get() << endl;;
	cout << "http request success" << endl;
}

void HttpClientTest2() {
    net::http::Client client;
    errors::Error err;
    boost::shared_ptr<net::http::Response> resp = client.Get("http://cn.bing.com/search?q=donet", err);
    if (err) {
        cout << "error: " << err.Message() << endl;
        return;
    }
    if (resp->status_code != 200) {
        cout << "status code: " << resp->status_code << endl;
        return;
    }
    cout << resp->proto << " " << resp->status << endl;
    cout << resp->body.get() << endl;;
    cout << "http request success" << endl;
}
void HttpClientTest3() {
	string str = "[{\"metric\": \"test-metric\", \"endpoint\": \"test-endpoint\", \"timestamp\": 1472142514,"
		"\"step\": 60,\"value\": 1,\"counterType\": \"GAUGE\",\"tags\": \"idc=lg,project=xx\"}]";
	net::http::Client client;
	errors::Error err;
	boost::shared_ptr<boost::asio::streambuf> buf = boost::make_shared<boost::asio::streambuf>();
    std::ostream os(buf.get());
	os << str;
	boost::shared_ptr<net::http::Response> resp = client.Post("http://127.0.0.1:60002/v1/push", 
			"application/json", buf, err);
    if (err) { 
        cout << "error: " << err.Message() << endl;
        return;
    } 
    cout << resp->proto << " " << resp->status << endl;
    cout << resp->body.get() << endl;
	if (resp->status_code == 200) {
        cout << "http request success" << endl;
	}
}
