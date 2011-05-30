#ifndef CFW_CORE_HPP
#define CFW_CORE_HPP

#include <string>
#include <vector>


typedef std::pair<std::string,std::string> cfw_id;

struct cfw_service {
	virtual cfw_id sid() const = 0;
	virtual cfw_id cid() const = 0; 
	virtual ~cfw_service(){};
};

struct cfw_component {
	virtual cfw_id id() const = 0;
	virtual std::vector<cfw_service*> ifs() const = 0;
	virtual std::vector<cfw_id> deps() const = 0;
	virtual void start() = 0;
	virtual void stop() = 0;
	virtual ~cfw_component(){};
};

struct cfw_portal {
	virtual std::vector<cfw_service*> services(const cfw_id& id) const = 0;
	virtual ~cfw_portal(){};
};

#endif // !CFW_CORE_HPP

