
#include <cfw/core.hpp>
#include <cfw/util.hpp>

#include <portal.hpp>

#include <iostream>
#include <string.h>

#include <dlfcn.h>
#include <stdio.h>
#include <sys/shm.h>

#include <boost/program_options.hpp>
namespace po = boost::program_options;


int main(int argc, char* argv[])
{
    // boost options parser, nice!
    try {
        po::options_description desc("Generic");
        desc.add_options()
        ("help,h", "display help message")
        ("version,v", "display version information")
        ;

        po::variables_map vm;
        po::store(po::parse_command_line(argc, argv, desc), vm);
        po::notify(vm);

        if (vm.count("help")) {
            std::cout << desc;
            return 1;
        }
        if (vm.count("version")) {
            std::cout << "0.1.1" << std::endl;
            return 0;
        }

        po::options_description env("Environment");
        env.add_options()
        ("level", po::value<int>(), "")
        ;

        po::store(po::parse_environment(env, "CFW_LOGGING_"), vm);
        po::notify(vm);

        if (vm.count("level")) {
            std::cout << "Setting logging level to "
                      << vm["level"].as<int>() << std::endl;
        }

    } catch (std::exception& e) {
        std::cout << e.what() << std::endl;
        return 1;
    }

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

