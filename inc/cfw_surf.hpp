#ifndef CFW_SURF_HPP
#define CFW_SURF_HPP

#include <cfw_core.hpp>

const cfw_id cfw_surf_id = std::make_pair("surf", "1");

struct cfw_surf : public cfw_interface {
	virtual std::vector<float> extract() const = 0; 
	virtual ~cfw_surf(){}; 
};

#endif // !CFW_SURF_HPP

