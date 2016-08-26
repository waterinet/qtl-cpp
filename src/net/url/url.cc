#include "qtl/net/url/url.h"
#include "qtl/strings/strings.h"

#include <vector>
#include <boost/algorithm/string.hpp>

namespace qtl {
namespace net {
namespace url {

using std::string;
using qtl::errors::Error;

boost::shared_ptr<URL> Parse(const string& rawurl, Error& err) {
	if (rawurl.empty()) {
		err = Error("empty rawurl");
		return boost::shared_ptr<URL>();
	}
	string remain = rawurl;
	std::vector<string> vec;
	boost::shared_ptr<URL> url = boost::shared_ptr<URL>(new URL); 
    
	if (remain.find("://") != string::npos) {
		string other;
		strings::Split(remain, url->scheme, other, "://", true);
		remain = other;
	}
	if (remain.find("#") != string::npos) {
		boost::split(vec, remain, boost::is_any_of("#"));
		if (vec.size() != 2) {
			err = Error("invalid url");
			return boost::shared_ptr<URL>();
		}
		remain = vec[0];
		url->fragment = vec[1];
		vec.clear();
	}
	if (remain.find("?") != string::npos) {
		boost::split(vec, remain, boost::is_any_of("?"));
		if (vec.size() != 2) {
			err = Error("invalid url");
			return boost::shared_ptr<URL>();
		}
		remain = vec[0];
		url->query = vec[1];
		vec.clear();
	}

	// path may be empty
	strings::Split(remain, url->host, url->path, "/");

	return url;
}

} // namespace url
} // namespace net
} // namespace qtl
