
#ifndef CFW_UTIL_HPP
#define CFW_UTIL_HPP

#include <cfw_core.hpp>


const cfw_id cfw_log_id = std::make_pair("cfw_log", "1");

struct cfw_log : public cfw_service {
    // must follow RFC 3164 The BSD Syslog Protocol
    virtual void write(int severity, int facility, const std::string& message) = 0;
    virtual ~cfw_log() {};
};


const cfw_id cfw_ac_id = std::make_pair("cfw_ac", "1");

struct cfw_ac : public cfw_service {
    // add more stuff when needed
    virtual void terminate() = 0;
    virtual ~cfw_ac() {};
};

#endif //!CFW_UTIL_HPP

