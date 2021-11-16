#include "Model.h"

namespace Graphics
{
	bool Model::Load(string_view filename)
	{
		ifstream in;
		in.open(string(filename), ifstream::in);
		if (in.fail())
		{
			return false;
		}

		string line;
		while (!in.eof())
		{
			std::getline(in, line);
			istringstream iss(line);
			if (!line.compare(0, 2, "v "))
			{
				auto & v = _vertexes.emplace_back();
				int read = std::sscanf(line.c_str(), "v %f %f %f\n", &v.x, &v.y, &v.z);
				if (read != 3)
				{
					std::cerr << "Specified .OBJ file contains unsupported format of geometric vertices (only \"v %f %f %f\" supported)!" << std::endl;
					return false;
				}
			}
			else if (!line.compare(0, 2, "f "))
			{
				auto & face = _faces.emplace_back();
				auto & v = face.vertices;
				auto & vt = face.textureVertices;
				auto & vn = face.normals;

				int read = std::sscanf(line.c_str(), "f %d/%d/%d %d/%d/%d %d/%d/%d\n",
					&v.x, &vt.x, &vn.x,
					&v.y, &vt.y, &vn.y,
					&v.z, &vt.z, &vn.z);

				if (read != 9)
				{
					std::cerr << "Specified .OBJ file contains unsupported format of face elements (only \"f v1/vt1/vn1 v2/vt2/vn2 v3/vt3/vn3\" supported)!" << std::endl;
					return false;
				}

				// in wavefront obj all indices start at 1, not zero
				auto indicesOffset = vec3(1, 1, 1);
				v = v - indicesOffset;
				vt = vt - indicesOffset;
				vn = vn - indicesOffset;
			}
			else if (!line.compare(0, 3, "vt "))
			{
				auto & vt = _textureVertexes.emplace_back();
				int read = std::sscanf(line.c_str(), "vt %f %f %f\n", &vt.x, &vt.y, &vt.z);
				if (read != 3)
				{
					std::cerr << "Specified .OBJ file contains unsupported format of texture coordinates (only \"vt %f %f %f\" supported)!" << std::endl;
					return false;
				}
			}
			else if (!line.compare(0, 3, "vn "))
			{
				auto & normal = _normals.emplace_back();
				int read = std::sscanf(line.c_str(), "vn %f %f %f\n", &normal.x, &normal.y, &normal.z);
				if (read != 3)
				{
					std::cerr << "Specified .OBJ file contains unsupported format of normal (only \"vn %f %f %f\" supported)!" << std::endl;
					return false;
				}
			}
		}

		std::cout
			<< "Loaded model data:" << '\n'
			<< "  v# " << _vertexes.size() << '\n'
			<< "  f# " << _faces.size() << '\n'
			<< " vt# " << _textureVertexes.size() << '\n'
			<< " vn# " << _normals.size() << std::endl;

		return true;
	}
}

