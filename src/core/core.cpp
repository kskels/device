
#include <cfw/core.hpp>
#include <cfw/util.hpp>

#include <portal.hpp>

#include <iostream>
#include <string.h>

#include <dlfcn.h>
#include <stdio.h>
#include <sys/shm.h>


int main(int argc, char* argv[])
{
    std::vector<std::string> libs;
    libs.push_back("./libcfw_log.so");

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
       cfw::component* component = create_component(&_portal, "");
       _portal.register_component(component);
    } // !for

	_portal.components().find(std::make_pair("log","1"))->second->start();	
	_portal.components().find(std::make_pair("log","1"))->second->stop();	

    return 0;
} // main

