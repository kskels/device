
#ifndef CFW_UTIL_HPP
#define CFW_UTIL_HPP 

#include <cfw_core.hpp>


const cfw_id cfw_log_id = std::make_pair("cfw_log", "1"); 

struct cfw_log : public cfw_service {
	enum cfw_severity {
		error,
		warning,
		info,
		debug
	};
	virtual void write(cfw_severity severity, const std::string& message) = 0;
	virtual ~cfw_log() {};
};

#endif //!CFW_UTIL_HPP

