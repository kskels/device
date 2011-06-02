
#include <cfw_core.hpp>
#include <cfw_util.hpp>
#include <cfw_surf.hpp>

#include <cv.h>

#include <iostream>


class surf_service : public cfw_surf {
public:
    surf_service(){};
    ~surf_service(){};

    cfw_id sid() const {
        return cfw_surf_id;
    }   
    cfw_id cid() const {
        return std::make_pair("opencv_surf", "1");
    }

    std::vector<float> extract(cfw_matrix* image) const {
        cv::Mat mat(image->height(), image->width(), image->data()[0]);
        std::vector<float> descriptors;
        std::vector<cv::KeyPoint> keypoints;
        _surf(mat, mat, keypoints, descriptors);  
        return descriptors;
    } 

private:
    cv::SURF _surf;
};

class opencv_surf : public cfw_component
{
public:
    opencv_surf(cfw_portal* portal, const std::string& cfg) :
        _portal(portal), _cfg(cfg) {
        _deps.push_back(std::make_pair(cfw_log_id,false));
        _services.push_back(&_surf);
    }
    ~opencv_surf() {}
    cfw_id id() const {
        return std::make_pair("opencv-surf", "1");
    }
    void start() {
    }
    void stop() {
    }
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
    surf_service _surf;
};

extern "C" cfw_component* cfw_create_component(cfw_portal* portal,
        const std::string& cfg) {
    return new opencv_surf(portal, cfg);
}

extern "C" void cfw_destroy_component(cfw_component* component) {
    delete static_cast<opencv_surf*>(component);
}

