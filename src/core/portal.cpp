
#include <portal.hpp>

std::vector<cfw_service*> portal::services(const cfw_id& id) const
{
    // TODO: Use multimap or such and optimize this
    std::vector<cfw_service*> found_services;
    std::map<cfw_id,cfw_component*>::const_iterator cit = _components.begin();
    for (; cit != _components.end(); ++cit) {
        std::vector<cfw_service*> s = cit->second->services();
        std::vector<cfw_service*>::iterator sit = s.begin();
        for (; sit != s.end(); ++sit) {
            if ((*sit)->sid() == id) {
                found_services.push_back(*sit);
            }
        } // for
    } // for
    return found_services;
} // !services

void portal::register_component(cfw_component* component)
{
    // TODO: Handle error codes and identical component names
    _components.insert(std::make_pair<cfw_id,cfw_component*>(component->id(),component));
} // !register_component

