#ifndef QTL_ERRORS_BASE_ERROR_H_
#define QTL_ERRORS_BASE_ERROR_H_

#include <string>

namespace qtl {
namespace errors {

class BaseError {
public:
	virtual ~BaseError() {}
	virtual std::string Message() const = 0;
	virtual operator bool() const = 0; 
	virtual bool operator !() const = 0; 
};

} // namespace errors
} // namespace qtl

#endif // QTL_ERRORS_BASE_ERROR_H_
