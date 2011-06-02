
#ifndef CFW_SURF_HPP
#define CFW_SURF_HPP

#include <cfw_core.hpp>


struct cfw_matrix {
    virtual int width() const = 0;
    virtual int height() const = 0;
    virtual std::vector<char> data() const = 0;
    virtual ~cfw_matrix() {};
};


const cfw_id cfw_pgm_reader_id = std::make_pair("cfw_pgm_reader", "1");

struct cfw_pgm_reader : public cfw_service {
    virtual cfw_matrix* read(const std::string& path) = 0;
    virtual void free(cfw_matrix* matrix) = 0;
    virtual ~cfw_pgm_reader() {};
};


const cfw_id cfw_surf_id = std::make_pair("cfw_surf", "1");

struct cfw_surf : public cfw_service {
    virtual std::vector<float> keypoints(cfw_matrix* image) const = 0;
    virtual std::vector<float> descriptors(cfw_matrix* image) const = 0;
    virtual ~cfw_surf() {};
};

#endif // !CFW_SURF_HPP

