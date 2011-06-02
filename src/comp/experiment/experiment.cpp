
#include <cfw_core.hpp>
#include <cfw_surf.hpp>

#include <iostream>
#include <fstream>

class experiment : public cfw_component
{
public:
    experiment(cfw_portal* portal, const std::string& cfg) :
        _portal(portal), _cfg(cfg), _reader(0), _surf(0) {
        _deps.push_back(std::make_pair(cfw_pgm_reader_id, true));
        _deps.push_back(std::make_pair(cfw_surf_id, true));
    }
    ~experiment() {}
    cfw_id id() const {
        return std::make_pair("experiment", "1");
    }
    void start();
    void stop();
    std::vector<cfw_service*> services() const {
        return _services;
    }
    std::vector<std::pair<cfw_id,bool> > deps() const {
        return _deps;
    }
private:
    std::vector<cfw_service*> _services;
    std::vector<std::pair<cfw_id,bool> > _deps;
    cfw_portal* _portal;
    std::string _cfg;

    cfw_pgm_reader* _reader;
    cfw_surf* _surf;
};

void experiment::start()
{
    _reader = static_cast<cfw_pgm_reader*>(_portal->services(cfw_pgm_reader_id)[0]);
    _surf = static_cast<cfw_surf*>(_portal->services(cfw_surf_id)[0]);

    cfw_matrix* image = _reader->read("../src/comp/experiment/experiment.pgm");
    std::vector<float> keypoints = _surf->keypoints(image);
    std::vector<float> descriptors = _surf->descriptors(image);
    _reader->free(image);

    std::ofstream file("experiment.txt", std::ios::app);
    for (int i = 0; i < keypoints.size(); i+=3) {
        file << keypoints[i] << " " << keypoints[i+1] << " " << keypoints[i+2]
             << " " << std::endl;
    }
    file.close();
} // !start

void experiment::stop()
{

}

extern "C" cfw_component* cfw_create_component(cfw_portal* portal,
        const std::string& cfg)
{
    return new experiment(portal, cfg);
}

extern "C" void cfw_destroy_component(cfw_component* component)
{
    delete static_cast<experiment*>(component);
}

