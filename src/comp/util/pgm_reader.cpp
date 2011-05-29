
#include <cfw_util.hpp>

class matrix : public cfw_matrix {
public:
	
	int width() const {
		return _width;
	}
	int height() const {
		return _height;
	}
	std::vector<char> data() const {
		return _data;
	}	
private:
	int _width;
	int _height;
	std::vector<char> _data;
};


class pgm_reader : public cfw_component
{
public:
	pgm_reader(){}
	~pgm_reader(){}
	cfw_id component_id() const {
		return std::make_pair("pgm_reader", "1");
	}	
	void start() {}
	void stop() {}
	std::vector<cfw_interface*> if_array() const {
		return _if_array;	
	}
	std::vector<cfw_id> dep_array() const {
		return _dep_array;
	}
	static cfw_component* create() {
		return new pgm_reader();
	}
	static void destroy(cfw_component* component) {
		delete static_cast<pgm_reader*>(component);
	}
private:
	std::vector<cfw_interface*> _if_array;
	std::vector<cfw_id> _dep_array;
};

extern "C" cfw_component* create_cfw_component() {
	return pgm_reader::create();
}

extern "C" void destroy_cfw_component(cfw_component* component) {
	pgm_reader::destroy(component);
}

