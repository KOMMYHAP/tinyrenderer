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
			char trash;
			if (!line.compare(0, 2, "v "))
			{
				iss >> trash;
				auto & v = _vertexes.emplace_back();
				for (int i = 0; i < 3; i++) iss >> v[i];
			}
			else if (!line.compare(0, 2, "f "))
			{
				auto & face = _faces.emplace_back();

				int itrash, idx;
				iss >> trash;

				for (int i = 0; i < 3; ++i)
				{
					iss >> idx >> trash >> itrash >> trash >> itrash;
					idx--; // in wavefront obj all indices start at 1, not zero
					face[i] = idx;
				}
			}
			else if (!line.compare(0, 3, "vt "))
			{
				iss >> trash;
				auto & v = _textureVertexes.emplace_back();
				for (int i = 0; i < 3; i++) iss >> v[i];
			}
		}

		std::cout
			<< "Loaded model data:" << '\n'
			<< "  v# " << _vertexes.size() << '\n'
			<< "  f# " << _faces.size() << '\n'
			<< " vt# " << _textureVertexes.size() << std::endl;

		return true;
	}
}

