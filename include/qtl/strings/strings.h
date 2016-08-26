#ifndef QTL_STRINGS_STRINGS_H_
#define QTL_STRINGS_STRINGS_H_

#include <string>

namespace qtl {
namespace strings {

using std::string;

// may be s is of the form a c b
// if so, return a, c b (or a, b if cutc == true)
// if not, return s, ""
inline void Split(const string& s, string& a, string& b, const string& c, bool cutc=false) {
	typedef string::size_type size_type;

	size_type pos = s.find(c);
	if (pos == string::npos) {
		a = s;
		b = "";
		return;
	}
    a = s.substr(0, pos);
	if (cutc) {
		pos += c.size();
	}
	b = s.substr(pos);
}

} // namespace strings
} // namespace qtl

#endif // QTL_STRINGS_STRINGS_H_
