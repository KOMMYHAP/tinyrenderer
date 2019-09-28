#pragma once

#include <string>
#include <vector>
#include <array>
#include <optional>
#include "geometry.h"

namespace model
{
	struct Model;
	
	std::optional<Model> LoadFromFile(const std::string & filename);

	struct Model
	{
		using face_t = array<int, 3>;

		vector<face_t>				faces;
		vector<geometry::Vec3f>	vertexes;
	};
}
