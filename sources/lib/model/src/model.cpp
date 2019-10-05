#include "basic_defs.h"
#include "model.h"

#include <fstream>
#include <sstream>

namespace model
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
	        std::istringstream iss(line);
	        char trash;
	        if (!line.compare(0, 2, "v ")) {
	            iss >> trash;
	            geometry::Vec3f v;
	            for (int i =0;i<3;i++) iss >> v[i];
	            model->vertexes.emplace_back(v);
	        } else if (!line.compare(0, 2, "f ")) {
	            array<int, 3> face = {};
	            int itrash;
	            iss >> trash;
				for (auto & index : face)
				{
					iss >> index >> trash >> itrash >> trash >> itrash;
					index -= 1; // in wavefront .obj all indexes start at 1, not 0
				}
	            model->faces.emplace_back(face);
	        }
	    }

		return model;
	}

}
