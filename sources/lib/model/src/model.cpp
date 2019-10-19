#include "basic_defs.h"
#include "model.h"

#include <fstream>
#include <sstream>

namespace model::detail
{
	class Reader
	{
	public:
		Reader(std::ifstream & ifs);

		bool CanRead() const;
		void NextLine();

		bool TryReadVertexes(const string & prefix, vector<geometry::Vec3f> & output);
		bool TryReadFace(const string & prefix, vector<Face> & output);

	private:
		std::ifstream &			m_ifstream;
		string					m_iline;
		std::istringstream		m_isstream;
	};
}

namespace model
{
	std::optional<Model> LoadFromFile(const std::string& filename)
	{
		std::ifstream input {filename, std::ios_base::in};
		if (!input.is_open())
		{
			return {};
		}

		auto model = std::make_optional<Model>();

		detail::Reader reader {input};
			reader.NextLine();
		while (reader.CanRead()) 
			if (reader.TryReadVertexes("v ", model->v))
		{
			{
			}
			else if (reader.TryReadVertexes("vt ", model->vt))
			{
			}
			else if (reader.TryReadVertexes("vn ", model->vn))
			{
			}
			else if (reader.TryReadFace("f ", model->faces))
			{	
			}

	    }

		if (!input.eof())
		{
			return {};
		}

		return std::move(model);
	}

}


namespace model::detail
{
	Reader::Reader(std::ifstream& ifs)
		: m_ifstream(ifs)
	{
		NextLine();
	}

	bool Reader::CanRead() const
	{
		return m_ifstream.good();
	}

	void Reader::NextLine()
	{
		std::getline(m_ifstream, m_iline);
		m_isstream.str(m_iline);
	}

	bool Reader::TryReadVertexes(const string& prefix, vector<geometry::Vec3f>& output)
	{
		if (m_iline.compare(0, prefix.size(), prefix.c_str()) == 0)
		{
			m_isstream.seekg(prefix.size());
            geometry::Vec3f v;
            m_isstream >> v[0] >> v[1] >> v[2];
            output.emplace_back(std::move(v));
			return true;
		}
		return false;
	}

	bool Reader::TryReadFace(const string& prefix, vector<Face>& output)
	{
		if (m_iline.compare(0, prefix.size(), prefix.c_str()) == 0)
		{
			output.emplace_back();
			auto & face = output.back();

			m_isstream.seekg(prefix.size());

            char slash;
			for (int i = 0; i < 3; ++i)
			{
				m_isstream >> face.v[i] >> slash >> face.vt[i] >> slash >> face.vn[i];
				
				// wavefront obj file starts indexes at 1 instead of 0.
				face.v[i] -= 1;
				face.vt[i] -= 1;
				face.vn[i] -= 1;
			}

			return true;
		}
		return false;
	}
}
