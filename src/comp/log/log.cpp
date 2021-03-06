
#include <cfw/util.hpp>
#include <cfw/core.hpp>

#include <vector>
#include <iostream>


class log : public cfw::log
{
public:
  cfw::id sid() const {
    return cfw::log_id;
  }
  void write(int severity, int facility, const std::string& message) {
    std::cout << message << std::endl;
  }
};

class component : public cfw::component
{
public:
  component(cfw::portal* portal, const std::string& cfg) :
    _portal(portal), _cfg(cfg) {
    _services.push_back(&_log);
  }
  ~component() {};
  cfw::id cid() const {
    return cfw::log_id;
  }
  void start() {
    _log.write(0, 0, "Log component starts-up..");
  }
  void stop() {
    _log.write(0, 0, "Log component stops-down..");
  }
  std::vector<cfw::service*> services() const {
    return _services;
  }
  std::vector<std::pair<cfw::id, bool> > deps() const {
    return _deps;
  }
private:
  cfw::portal* _portal;
  std::string _cfg;
  std::vector<cfw::service*> _services;
  std::vector<std::pair<cfw::id,bool> > _deps;
  log _log;
};

extern "C" cfw::component* cfw_create_component(cfw::portal* portal,
    const std::string& cfg)
{
  return new component(portal, cfg);
}

extern "C" void cfw_destroy_component(cfw::component* component)
{
  delete component;
}

