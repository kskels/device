
#include <cfw_core.hpp>
#include <iostream>


class example : public cfw_component
{
public:
	example(){};
	~example(){};
	cfw_id id() const {
		return std::make_pair<std::string,std::string>("example", "1");
	}	
	void start() {
		std::cout << "Hello from the example component" << std::endl;
	}
	void stop() {
		std::cout << "Bye bye from the example component" << std::endl;
	}
	std::vector<cfw_interface*> if_array() const {
		return _if_array;	
	}
	std::vector<cfw_interface*> dep_array() const {
		return _dep_array;
	}
private:
	std::vector<cfw_interface*> _if_array;
	std::vector<cfw_interface*> _dep_array;
};

extern "C" cfw_component* create_cfw_component() {
	return new example();
}

extern "C" void destroy_cfw_component(cfw_component* component) {
	delete static_cast<example*>(component);
}

