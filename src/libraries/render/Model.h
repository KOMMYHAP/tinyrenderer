#pragma once

#include <vector>
#include "geometry.h"

namespace Graphics
{
	struct FaceInfo
	{
		vec3 vertices;
		vec3 textureVertices;
		vec3 normals;
	};
	
	class Model
	{
	public:
		bool Load(string_view filename);

		[[nodiscard]] const auto & Vertex(uint32_t i) const { return _vertexes[i]; }
		[[nodiscard]] const auto & TextureVertex(uint32_t i) const { return _textureVertexes[i]; }
		[[nodiscard]] const auto & Face(uint32_t i) const { return _faces[i]; }
		[[nodiscard]] const auto & Normal(uint32_t i) const { return _normals[i]; }
		
		[[nodiscard]] const auto & Vertexes() const { return _vertexes; }
		[[nodiscard]] const auto & TextureVertexes() const { return _textureVertexes; }
		[[nodiscard]] const auto & Faces() const { return _faces; }
		[[nodiscard]] const auto & Normals() const { return _normals; }

	private:
		vector<vec3> _vertexes;
		vector<vec3> _textureVertexes;
		vector<vec3> _normals;
		vector<FaceInfo> _faces;
	};
}
