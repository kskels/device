
#include <cfw_core.hpp>
#include <cfw_util.hpp>

#include <iostream>
#include <dlfcn.h>

int main(int argc, char* argv[]) 
{
	void* handle = dlopen("./libpgm_reader.so", RTLD_LAZY);
    
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

	std::vector<cfw_interface*> if_array = component->if_array();
	cfw_pgm_reader* reader = static_cast<cfw_pgm_reader*>(if_array[0]);
	cfw_matrix* matrix = reader->read("test_image.pgm");
	reader->free(matrix);
		
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

