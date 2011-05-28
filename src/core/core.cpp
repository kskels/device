
#include <cfw_core.hpp>

#include <iostream>
#include <dlfcn.h>

int main(int argc, char* argv[]) 
{
	void* handle = dlopen("./libexample.so", RTLD_LAZY);
    
    if (!handle) {
        std::cerr << "Cannot open library: " << dlerror() << std::endl;
        return 1;
    }

	typedef cfw_component* (*create_cfw_component_t)();
	create_cfw_component_t create_cfw_component = (create_cfw_component_t) dlsym(handle, "create_cfw_component");
	if (!create_cfw_component) {
		std::cerr << "Cannot load symbol 'create_cfw_component': " << dlerror() << std::endl;
		dlclose(handle);
		return 1;
	}
	
	cfw_component* component = create_cfw_component();	
	
	std::cout << "id: " << component->component_id().first << "~" << component->component_id().second << std::endl;
	component->start();
	component->stop();

		
	typedef void (*destroy_cfw_component_t)(cfw_component*);
	destroy_cfw_component_t destroy_cfw_component = (destroy_cfw_component_t) dlsym(handle, "destroy_cfw_component");
	if (!destroy_cfw_component) {
		std::cerr << "Cannot load symbol 'destroy_component': " << dlerror() << std::endl;
		dlclose(handle);
		return 1;
	}

	destroy_cfw_component(component);

	return 0;
} // main

