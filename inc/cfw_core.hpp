#ifndef CFW_CORE_HPP
#define CFW_CORE_HPP

#include <string>
#include <vector>


typedef std::pair<std::string,std::string> cfw_id;

struct cfw_interface {
	virtual cfw_id id() const = 0;
	virtual cfw_id comp_id() const = 0; 
	virtual ~cfw_interface(){};
};

struct cfw_component {
	virtual cfw_id id() const = 0;
	virtual std::vector<cfw_interface*> if_array() const = 0;
	virtual std::vector<cfw_interface*> dep_array() const = 0;
	virtual void start() = 0;
	virtual void stop() = 0;
	virtual ~cfw_component(){};
};

struct cfw_portal {
	virtual cfw_interface& interface(const cfw_id& id, const cfw_id& comp_id) const = 0;
	virtual std::vector<cfw_interface&> interface(const cfw_id& id) = 0;
	virtual ~cfw_portal(){};
};

#endif // !CFW_CORE_HPP

