
#ifndef CFW_CORE_HPP
#define CFW_CORE_HPP

#include <string>
#include <vector>

namespace cfw {

typedef std::pair<std::string,std::string> id;

struct service {
    virtual id sid() const = 0;
    virtual id cid() const = 0;
    virtual ~service() {};
};

struct component {
    virtual id cid() const = 0;
    virtual std::vector<service*> services() const = 0;
    virtual std::vector<std::pair<cfw::id,bool> > deps() const = 0;
    virtual void start() = 0;
    virtual void stop() = 0;
    virtual ~component() {};
};

struct portal {
    virtual std::vector<service*> services(const id& sid) const = 0;
    virtual ~portal() {};
};

} // namespace

typedef cfw::component* (*cfw_create_component_t)(cfw::portal* portal,
        const std::string& cfg);

typedef void (*cfw_destroy_component_t)(cfw::component* component);

#endif // !CFW_CORE_HPP

