#include <iostream>
#include "url.h"

using namespace std;
using namespace qtl;

void UrlTest(const string& rawurl);

int main() {
	cout << "-----------------" << endl;
	UrlTest("http://www.example.com/resource/?key=value#page1");
	cout << "-----------------" << endl;
	UrlTest("http://www.example.com/resource/#page1#");
	cout << "-----------------" << endl;
	UrlTest("http://www.example.com/resource/??key=value");
	cout << "-----------------" << endl;
	UrlTest("http://www.example.com/");
	cout << "-----------------" << endl;
	UrlTest("http://www.example.com");
	cout << "-----------------" << endl;
	UrlTest("www.example.com");
	cout << "-----------------" << endl;
	UrlTest("http://127.0.0.1:60002/v1/push");
}

void UrlTest(const string& rawurl) {
	cout << rawurl << endl;

	errors::Error err;
    boost::shared_ptr<net::url::URL> url = 
		net::url::Parse(rawurl, err);
	if (err) {
		cout << "error: " << err.Message() << endl;
		return;
	}
    
	cout << "scheme  : " << url->scheme << endl;
	cout << "host    : " << url->host << endl;
	cout << "path    : " << url->path << endl;
	cout << "query   : " << url->query << endl;
	cout << "fragment: " << url->fragment << endl;
}
