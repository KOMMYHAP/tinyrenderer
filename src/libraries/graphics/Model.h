#pragma once

#include <vector>
#include "Vec3.h"

namespace Graphics
{
	struct FaceInfo
	{
		Math::Vec3u vertices;
		Math::Vec3u textureVertices;
		Math::Vec3u normals;
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
		vector<Math::Vec3f> _vertexes;
		vector<Math::Vec3f> _textureVertexes;
		vector<Math::Vec3f> _normals;
		vector<FaceInfo> _faces;
	};
}
