
#ifndef CFW_UTIL_HPP
#define CFW_UTIL_HPP

#include <cfw/core.hpp>

namespace cfw
{

const id log_id = std::make_pair("log", "1");
struct log : public service {
  virtual void write(int severity, int facility, const std::string& message) = 0;
  virtual ~log() {};
};

} // namespace

#endif //!CFW_UTIL_HPP

