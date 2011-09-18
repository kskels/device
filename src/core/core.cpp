
#include <cfw_core.hpp>
#include <cfw_util.hpp>

#include <portal.hpp>

#include <iostream>
#include <string.h>

#include <dlfcn.h>
#include <stdio.h>
#include <sys/shm.h>


int main(int argc, char* argv[])
{
    std::vector<std::string> libs;
    libs.push_back("./libexample.so");

    portal _portal;


    int shmid2;
    key_t key2;
    void* shm2;
    std::string name_list;
    key2=ftok("tmp",'d');
    //create
    if ((shmid2 = shmget ( key2, sizeof(char)*1000, IPC_CREAT | 0666)) < 0) {
        perror("shmget2");
        return 1;
    }
    //attach
    shm2 = shmat(shmid2, (void *)0, 0) ;
    portal** list = new portal*[2];
    list[0] = &_portal;
    list[1] = 0;
    memcpy(shm2, list, sizeof(portal**));


    for (std::vector<std::string>::iterator it = libs.begin();
            it != libs.end(); ++it) {

        pid_t pid = fork();
        if (pid > 0) {

        } else if (pid == 0) {
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
            // get portal from shared memory
            portal* p = ((portal**)shm2)[1];
            cfw_component* component = create_component(p, "");
            p->register_component(component);

            while(1) {
                sleep(1000);
            }

        } else {
            // failed to fork
        }
    } // !for

	_portal.components().find(std::make_pair("example","1"))->second->start();	

    return 0;
} // main

