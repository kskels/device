
#include <cfw_core.hpp>
#include <cfw_util.hpp>
#include <cfw_surf.hpp>

#include <cv.h>

#include <iostream>


class surf_service : public cfw_surf
{
public:
    surf_service() : _surf(cv::SURF(100, 4, 2, true)) {};
    ~surf_service() {};

    cfw_id sid() const {
        return cfw_surf_id;
    }
    cfw_id cid() const {
        return std::make_pair("opencv_surf", "1");
    }

    std::vector<float> keypoints(cfw_matrix* image) const {
        cv::Mat mat(image->height(), image->width(), 0);
        std::vector<char> data = image->data();
        for (int i(0); i != data.size(); ++i) {
            mat.data[i] = data[i];
        }
        std::vector<cv::KeyPoint> k;
        _surf(mat, mat, k);
        std::vector<float> kk;
        for (std::vector<cv::KeyPoint>::iterator it = k.begin(); it != k.end(); ++it) {
            kk.push_back((*it).pt.x);
            kk.push_back((*it).pt.y);
            kk.push_back((*it).size);
        }
        return kk;
    }

    std::vector<float> descriptors(cfw_matrix* image) const {
        cv::Mat mat(image->height(), image->width(), 0);
        std::vector<char> data = image->data();
        for (int i(0); i != data.size(); ++i) {
            mat.data[i] = data[i];
        }
        std::vector<float> d;
        std::vector<cv::KeyPoint> k;
        _surf(mat, mat, k, d);
        return d;
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
        const std::string& cfg)
{
    return new opencv_surf(portal, cfg);
}

extern "C" void cfw_destroy_component(cfw_component* component)
{
    delete static_cast<opencv_surf*>(component);
}

