#ifndef CORE_PORTAL_HPP
#define CORE_PORTAL_HPP

#include <cfw/core.hpp>

#include <map>

class portal : public cfw::portal
{
public:
    std::vector<cfw::service*> services(const cfw::id& id) const;
    void register_component(cfw::component* component);
	std::map<cfw::id,cfw::component*> components() const;

private:
    std::map<cfw::id,cfw::component*> _components;
};

#endif // !CORE_PORTAL_HPP

