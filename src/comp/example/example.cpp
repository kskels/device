
#include <cfw/core.hpp>
#include <cfw/util.hpp>


class example : public cfw::component
{
public:
    example(cfw::portal* portal, const std::string& cfg) :
        _portal(portal), _cfg(cfg) {
	}

    ~example() {}
    cfw::id cid() const {
        return std::make_pair("example", "1");
    }
    void start() {
        cfw::log* log = dynamic_cast<cfw::log*>(_portal->services(cfw::log_id)[0]);
        log->write(0, 0, "Example component starts-up..");
    }
    void stop() {
        cfw::log* log = dynamic_cast<cfw::log*>(_portal->services(cfw::log_id)[0]);
        log->write(0, 0, "Example component stops-down..");
    }
    std::vector<cfw::service*> services() const {
        return _services;
    }
    std::vector<std::pair<cfw::id,bool> > deps() const {
        return _deps;
    }
private:
    std::vector<cfw::service*> _services;
    std::vector<std::pair<cfw::id,bool> > _deps;
    cfw::portal* _portal;
    std::string _cfg;
};

extern "C" cfw::component* cfw_create_component(cfw::portal* portal,
        const std::string& cfg)
{
    return new example(portal, cfg);
}

extern "C" void cfw_destroy_component(cfw::component* component)
{
    delete component;
}

