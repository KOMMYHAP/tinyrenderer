#include "model.h"

#include <fstream>
#include <sstream>

namespace ObjModel
{
	std::optional<Model> LoadFromFile(const std::string& filename)
	{
		std::ifstream input {filename, std::ios_base::in};
		if (!input.is_open())
		{
			return {};
		}

		std::string line;
		auto model = std::make_optional<Model>();

		while (!input.eof()) {
	        std::getline(input, line);
	        std::istringstream iss(line.c_str());
	        char trash;
	        if (!line.compare(0, 2, "v ")) {
	            iss >> trash;
	            Vec3f v;
	            for (int i =0;i<3;i++) iss >> v.raw[i];
	            model->vertexes.emplace_back(std::move(v));
	        } else if (!line.compare(0, 2, "f ")) {
	            std::vector<int> f;
	            int itrash, idx;
	            iss >> trash;
	            while (iss >> idx >> trash >> itrash >> trash >> itrash) {
	                idx--; // in wavefront obj all indices start at 1, not zero
	                f.push_back(idx);
	            }
	            model->faces.emplace_back(std::move(f));
	        }
	    }

		return model;
	}

}
