
#include <cfw_core.hpp>
#include <cfw_surf.hpp>
#include <cfw_util.hpp>

#include <iostream>


class example : public cfw_component
{
public:
	example(){
		_dep_array.push_back(cfw_surf_id);
		_dep_array.push_back(cfw_pgm_reader_id);
	}
	~example(){}
	cfw_id component_id() const {
		return std::make_pair("example", "1");
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
	std::vector<cfw_id> dep_array() const {
		return _dep_array;
	}
	static cfw_component* create() {
		return new example();
	}
	static void destroy(cfw_component* component) {
		delete static_cast<example*>(component);
	}
private:
	std::vector<cfw_interface*> _if_array;
	std::vector<cfw_id> _dep_array;
};

extern "C" cfw_component* create_cfw_component() {
	return example::create();
}

extern "C" void destroy_cfw_component(cfw_component* component) {
	example::destroy(component);
}

