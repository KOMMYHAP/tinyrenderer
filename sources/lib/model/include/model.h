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

	// Face contains indexes of appropriative arrays
	struct Face
	{
		array<int, 3>		v;		// vertexes
		array<int, 3>		vt;		// texture vertexes
		array<int, 3>		vn;		// normal vertexes
	};

	// Model contains 
	// - faces (arrays of indexes)
	// - v (vertexes)
	// - vt (vertex texture coordinate)
	// - vn (vertex normal)
	struct Model
	{
		vector<Face>				faces;
		vector<geometry::Vec3f>		v;
		vector<geometry::Vec3f>		vt;
		vector<geometry::Vec3f>		vn;
	};
}
