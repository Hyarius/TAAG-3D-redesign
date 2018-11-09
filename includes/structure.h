#ifndef STRUCTURE_H
# define STRUCTURE_H

using namespace std;
using namespace glm;

#include "gui_object.h"

typedef struct		s_model
{
	vector<vec3>	vertices;
	vector<vec2>	uvs;
	t_image			texture;
					s_model(string path, string name);
	void			draw_model(mat4 MVP);
}					t_model;

#endif
