
#include <portal.hpp>

std::vector<cfw::service*> portal::services(const cfw::id& id) const
{
    std::vector<cfw::service*> found_services;
    std::map<cfw::id,cfw::component*>::const_iterator cit = _components.begin();
    for (; cit != _components.end(); ++cit) {
        std::vector<cfw::service*> s = cit->second->services();
        std::vector<cfw::service*>::iterator sit = s.begin();
        for (; sit != s.end(); ++sit) {
            if ((*sit)->sid() == id) {
                found_services.push_back(*sit);
            }
        } // for
    } // for
    return found_services;
}

void portal::register_component(cfw::component* component)
{
    _components.insert(std::make_pair<cfw::id,cfw::component*>(component->cid(),component));
} 


std::map<cfw::id,cfw::component*> portal::components() const
{
	return _components;
}

