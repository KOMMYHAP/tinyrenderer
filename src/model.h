#pragma once

#include <vector>
#include "geometry.h"

class Model
{
public:
	Model(string_view filename);

	[[nodiscard]] auto VertsN() const { return _vertexes.size(); }
	[[nodiscard]] auto FacesN() const { return _faces.size(); }

	[[nodiscard]] auto & Vert(int i) const { return _vertexes[i]; }
	[[nodiscard]] auto & Face(int idx) const { return _faces[idx]; }

	[[nodiscard]] auto & Faces() const { return _faces; }
	[[nodiscard]] auto & Vertexes() const { return _vertexes; }
	
private:
	vector<Vec3f> _vertexes;
	vector<Vec3f> _textureVertexes;
	vector<Vec3i> _faces;
};
