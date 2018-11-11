#include "taag.h"
#include "base_value.h"

using namespace glm;

					s_model::s_model(string path, string name)
{
	ifstream				obj_file;

	size_t					i;
	vector<string>			tab;
	vector<string>			second_tab;

	vector<unsigned int>	vertexIndex, uvIndex;

	vector<vec3> 			temp_vertices;
	vector<vec2> 			temp_uvs;

	obj_file.open(path + name);
	if (!(obj_file.is_open()))
		error_exit("can't open the model " + path + name, 1564);
	while (!(obj_file.eof()))
	{
		tab = get_strsplit(&obj_file, " ", -1);
		if (tab.size() >= 1)
		{
			if (tab[0] == "v")
			{
				vec3 v;
				v.x = (float)(atof(tab[1].c_str()));
				v.y = (float)(atof(tab[2].c_str()));
				v.z = (float)(atof(tab[3].c_str()));
				temp_vertices.push_back(v);
			}
			else if (tab[0] == "vt")
			{
				vec2 uv;
				uv.x = (float)(atof(tab[1].c_str()));
				uv.y = (float)(atof(tab[2].c_str()));
				temp_uvs.push_back(uv);
			}
			else if (tab[0] == "f")
			{
				i = 1;
				while (i < tab.size())
				{
					second_tab = strsplit(tab[i], "/");
					vertexIndex.push_back(atoi(second_tab[0].c_str()));
					uvIndex.push_back(atoi(second_tab[1].c_str()));
					i++;
				}
			}
			else if (tab[0] == "usemtl")
			{
				texture = t_image(path + "tex/" + tab[1]);
			}
		}
		
	}
	for (i = 0; i < vertexIndex.size(); i++)
	{
		printf("point %d - vertice %d\n", i, vertexIndex[i]);
		vertices.push_back(temp_vertices[vertexIndex[i] - 1]);
		uvs.push_back(temp_uvs[uvIndex[i] - 1]);
	}
	obj_file.close();
}

void				t_model::draw_model(mat4 MVP)
{
	glBindVertexArray(get_vertex_array());

	glBindBuffer(GL_ARRAY_BUFFER, get_vertex_buffer());
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(vec3), &vertices[0], GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, get_texture_buffer());
	glBufferData(GL_ARRAY_BUFFER, uvs.size() * sizeof(vec4), &uvs[0], GL_STATIC_DRAW);

	glUseProgram(get_program_matrix());

	glUniformMatrix4fv(M_Matrix_ID, 1, GL_FALSE, &MVP[0][0]);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture.texture_id);
	glUniform1i(M_Texture_ID, 0);

	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, get_vertex_buffer());
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);

	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, get_texture_buffer());
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, NULL);

	glDrawArrays(GL_TRIANGLES, 0, vertices.size());

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
}
