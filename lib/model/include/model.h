#pragma once

#include <string>
#include <vector>
#include <optional>
#include "geometry.h"

namespace ObjModel
{
	struct Model;
	
	std::optional<Model> LoadFromFile(const std::string & filename);

	struct Model
	{
		using face_t = std::vector<int>;

		std::vector<face_t>		faces;
		std::vector<Vec3f>		vertexes;
	};
}
