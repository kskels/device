
#include <cfw_core.hpp>
#include <cfw_util.hpp>

#include <portal.hpp>

#include <iostream>
#include <dlfcn.h>


int main(int argc, char* argv[])
{
    std::vector<std::string> libs;
    libs.push_back("./libpgm-reader.so");
    libs.push_back("./libopencv-surf.so");
    libs.push_back("./libexperiment.so");

    portal _portal;
    for (std::vector<std::string>::iterator it = libs.begin();
            it != libs.end(); ++it) {

        void* handle = dlopen((*it).c_str(), RTLD_LAZY);
        if (!handle) {
            std::cerr << "Cannot open library: " << dlerror() << std::endl;
            return 1;
        }

        cfw_create_component_t create_component = (cfw_create_component_t) dlsym(handle, "cfw_create_component");
        if (!create_component) {
            std::cerr << "Cannot load symbol 'create_cfw_component': " << dlerror() << std::endl;
            dlclose(handle);
            return 1;
        }

        cfw_component* component = create_component(&_portal, "");
        _portal.register_component(component);
        std::cout << "[info]: starting " << component->id().first << "~" << component->id().second << std::endl;
        component->start();
    } // !for

    //for (std::vector<cfw_component*>::iterator it = _components.end();
            //it != _components.begin(); --it) {

        //cfw_destroy_component_t destroy_component = (cfw_destroy_component_t) dlsym(handle, "cfw_destroy_component");
        //if (!destroy_component) {
            //std::cerr << "Cannot load symbol 'destroy_component': " << dlerror() << std::endl;
            //dlclose(handle);
            //return 1;
        //}

        //destroy_component(component);
    //}

    return 0;
} // main

