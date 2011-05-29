
#include <cfw_util.hpp>

#include <fstream>

class matrix : public cfw_matrix
{
public:
    matrix(int width, int height, std::vector<char> data) :
        _width(width), _height(height), _data(data) {
    }
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

class pgm_reader_if : cfw_pgm_reader
{
    pgm_reader_if() {};
    ~pgm_reader_if() {};
    cfw_matrix* read(const std::string& path) {

        std::ifstream f(path.c_str(), std::ios_base::in|std::ios_base::binary);
        if (!f.is_open()) {
            throw "Failed to open the file";
        }

        // Read the header
        char magic[2] = {'0', '0'};
        f.read(magic, 2);
        if ((magic[0]!='P') || (magic[1]!='5')) {
            throw "Invalid magic number. Not a PGM file?";
        }

        // Read width&height
        int width;
        int height;
        int maxval;
        f>>width;
        f>>height;
        f>>maxval;
        if (maxval!=255) {
            throw "Maximal value != 255";
        }
        if (f.eof()) {
            throw "Unexpected EOF";
        }

        // Skip white space
        char c;
        f.get(c);
        if (f.eof()) {
            throw "Unexpected EOF";
        }

        std::vector<char> data;
        // Read the image, line by line
        char cc;
        for (int i=0; i<height; ++i) {
            f.read(&cc, 1);
            if (f.fail()) {
                throw "Unexpected EOF";
            }
            data.push_back(cc);
        } // for

        // Close
        f.close();

        matrix* m = new matrix(width, height, data);
        return m;
    }
	void free(cfw_matrix* data) {
		delete static_cast<matrix*>(data);		
	}
};

class pgm_reader : public cfw_component
{
public:
    pgm_reader() {}
    ~pgm_reader() {}
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

