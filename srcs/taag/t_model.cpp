#include "taag.h"
#include "base_value.h"

using namespace glm;

					s_model::s_model(string path, string name)
{
	ifstream				obj_file;
	ifstream				image_file;

	vector<string>			tab;
	vector<string>			second_tab;

	vector<unsigned int>	vertexIndex, uvIndex;

	vector<vec3> 			temp_vertices;
	vector<vec2> 			temp_uvs;

	obj_file.open(path + name);
	while (!(obj_file.eof()))
	{
		tab = get_strsplit(&obj_file, " ", -1);
		if(tab[0] == "v")
		{
			vec3 v;
			v.x = atof(tab[1].c_str());
			v.y = atof(tab[2].c_str());
			v.z = atof(tab[3].c_str());
			temp_vertices.push_back(v);
		}
		else if (tab[0] == "vt")
		{
			vec2 uv;
			uv.x = atof(tab[1].c_str());
			uv.y = atof(tab[2].c_str());
			temp_uvs.push_back(uv);
		}
		else if (tab[0] == "f")
		{
			for (size_t i = 1; i < tab.size(); i++)
			{
				second_tab = strsplit(tab[i], "/");
				vertexIndex.push_back(atoi(second_tab[0].c_str()));
				uvIndex.push_back(atoi(second_tab[1].c_str()));
			}
		}
		else if (tab[0] == "usemtl")
		{
			texture = t_image(path + "tex" + tab[1] + ".gif");
		}
		for( unsigned int i=0; i < vertexIndex.size(); i++ )
		{
			vertices.push_back(temp_vertices[vertexIndex[i] - 1]);
			uvs.push_back(temp_uvs[uvIndex[i] - 1]);
		}
	}
}

void				t_model::draw_model(mat4 MVP)
{

}
