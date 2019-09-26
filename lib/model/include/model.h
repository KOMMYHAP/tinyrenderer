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
		using face_t = std::array<int, 3>;

		std::vector<face_t>				faces;
		std::vector<geometry::Vec3f>	vertexes;
	};
}
