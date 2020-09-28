#pragma once

#include <vector>
#include "Vec3.h"

namespace Graphics
{
	class Model
	{
	public:
		bool Load(string_view filename);

		[[nodiscard]] auto VertsN() const { return _vertexes.size(); }
		[[nodiscard]] auto FacesN() const { return _faces.size(); }

		[[nodiscard]] const auto & Vert(int i) const { return _vertexes[i]; }
		[[nodiscard]] const auto & Face(int idx) const { return _faces[idx]; }

		[[nodiscard]] const auto & Faces() const { return _faces; }
		[[nodiscard]] const auto & Vertexes() const { return _vertexes; }

	private:
		vector<Math::Vec3f> _vertexes;
		vector<Math::Vec3f> _textureVertexes;
		vector<Math::Vec3i> _faces;
	};
}
