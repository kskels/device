
#include <cfw_core.hpp>

#include <iostream>


class example : public cfw_component
{
public:
    example(cfw_portal* portal, const std::string& cfg) :
        _portal(portal), _cfg(cfg) {}
    ~example() {}
    cfw_id id() const {
        return std::make_pair("example", "1");
    }
    void start() {
        std::cout << "start example component" << std::endl;
    }
    void stop() {
        std::cout << "stop exmaple component" << std::endl;
    }
    std::vector<cfw_service*> services() const {
        return _services;
    }
    std::vector<std::pair<cfw_id,bool> > deps() const {
        return _deps;
    }
private:
    std::vector<cfw_service*> _services;
    std::vector<std::pair<cfw_id,bool> > _deps;
    cfw_portal* _portal;
    std::string _cfg;
};

extern "C" cfw_component* cfw_create_component(cfw_portal* portal,
        const std::string& cfg)
{
    std::cout << "init example component" << std::endl;
    return new example(portal, cfg);
}

extern "C" void cfw_destroy_component(cfw_component* component)
{
    std::cout << "terminate example component" << std::endl;
    delete static_cast<example*>(component);
}

