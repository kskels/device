
#include <cfw/core.hpp>

#include <iostream>
#include <list>
#include <tr1/functional>


namespace cfw {

class log {
public:
	void write(const std::string& message) {
		std::cout << message << std::endl;
	}	
};

class write 
{
public:
	write(log* l) : _log(l) {}
	void operator()(const std::string& message) {
		_log->write(message);
	}	
private:
	log* _log;
};

}




class example : public cfw_component
{
public:
    example(cfw_portal* portal, const std::string& cfg) :
        _portal(portal), _cfg(cfg) {
		_methods.push_back(cfw::write(&_log));
	
		// "example-1.log" // logging method
		void* method(void* args); 
	}

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
	typedef std::tr1::function<void(const std::string&)> method_t;
	std::list<method_t> _methods;

	cfw::log _log;

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

