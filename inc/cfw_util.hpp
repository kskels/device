
#include <cfw_core.hpp>

const cfw_id cfw_pgm_reader_id = std::make_pair("pgm_reader", "1");

struct cfw_matrix {
	virtual int width() const = 0;
	virtual int height() const = 0;
	virtual std::vector<char> data() const = 0;
	virtual ~cfw_matrix(){};
};

struct cfw_pgm_reader : public cfw_interface {
	virtual cfw_matrix* read(const std::string& path) = 0; 
	virtual ~cfw_pgm_reader(){};
};

