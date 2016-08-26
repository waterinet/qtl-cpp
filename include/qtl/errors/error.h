#ifndef QTL_ERRORS_ERROR_H_
#define QTL_ERRORS_ERROR_H_

#include "base_error.h"

namespace qtl {
namespace errors {

class Error : public BaseError {
public:
    Error() {}
	Error(const std::string& s) : msg_(s) {}
	Error(const Error& e) : msg_(e.msg_) {}

    std::string Message() const { return msg_; }
	operator bool() const { return !msg_.empty(); }
	bool operator !() const { return msg_.empty(); }
	Error& operator=(const Error& e) {
		msg_ = e.msg_;
		return *this;
	}
private:
	std::string msg_;
};

} // namespace errors
} // namespace qtl

#endif // QTL_ERRORS_ERROR_H_
