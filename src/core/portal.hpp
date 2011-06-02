#ifndef CORE_PORTAL_HPP
#define CORE_PORTAL_HPP

#include <cfw_core.hpp>

#include <map>

class portal : public cfw_portal
{
public:
    std::vector<cfw_service*> services(const cfw_id& id) const;
    void register_component(cfw_component* component);
private:
    std::map<cfw_id,cfw_component*> _components;
};

#endif // !CORE_PORTAL_HPP

