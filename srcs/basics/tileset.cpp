#include "template.h"

/*
s_tileset			*create_s_tileset(string path)
{
	ifstream file;
	string line;
	vector<string> split_line;

	file.open(path);
	if (!file.good())
		error_exit("Cant open such file : " + path, 7946);
	line = get_strsplit(&file, ":", 2)[1];
	split_line = get_strsplit(&file, ":", 3);
	return (new s_tileset(line, atoi(split_line[1].c_str()), atoi(split_line[2].c_str())));
}
*/
void	s_tileset::draw_self(t_vect p_tl, t_vect p_tr, t_vect p_dl, t_vect p_dr, int sprite, double p_alpha)
{
	t_point		tl = screen_to_opengl(p_tl);
	t_point		tr = screen_to_opengl(p_tr);
	t_point		dl = screen_to_opengl(p_dl);
	t_point		dr = screen_to_opengl(p_dr);

	int			i;
	if (sprite >= sprite_list.size())
		i = 0;
	else
		i = sprite;

	draw_triangle_texture(	t_point(tl.x, tl.y, sprite_list[i].x, sprite_list[i].y, p_alpha),
							t_point(tr.x, tr.y, sprite_list[i].x + size.x, sprite_list[i].y, p_alpha),
							t_point(dl.x, dl.y, sprite_list[i].x, sprite_list[i].y + size.y, p_alpha));

	draw_triangle_texture(	t_point(dl.x, dl.y, sprite_list[i].x, sprite_list[i].y + size.y, p_alpha),
							t_point(dr.x, dr.y, sprite_list[i].x + size.x, sprite_list[i].y + size.y, p_alpha),
							t_point(tr.x, tr.y, sprite_list[i].x + size.x, sprite_list[i].y, p_alpha));
}


void 			s_tileset::draw_self(t_vect p_coord, t_vect p_size, int p_sprite)
{
	glBindTexture(GL_TEXTURE_2D, texture_id);
	draw_self(p_coord, p_coord + t_vect(p_size.x, 0), p_coord + t_vect(0, p_size.y), p_coord + p_size, p_sprite, 1.0);
}


void 			s_tileset::draw_self(t_vect p_coord, t_vect p_size, int p_sprite, double p_alpha)
{
	glBindTexture(GL_TEXTURE_2D, texture_id);
	draw_self(p_coord, p_coord + t_vect(p_size.x, 0), p_coord + t_vect(0, p_size.y), p_coord + p_size, p_sprite, p_alpha);
}


s_tileset::s_tileset(string p_path, t_vect p_size)
{
	surface = IMG_Load(p_path.c_str());
	if (surface == NULL)
		error_exit("Can't charge a surface into an image", 245);

	if (surface->format->BytesPerPixel == 3)
	{
		internal_format = GL_RGB;
		if (surface->format->Rmask == 0xff)
			format = GL_RGB;
		else
			format = GL_BGR;
	}
	else if (surface->format->BytesPerPixel == 4)
	{
		internal_format = GL_RGBA;
		if (surface->format->Rmask == 0xff)
			format = GL_RGBA;
		else
			format = GL_BGRA;
	}

	glGenTextures(1, &texture_id);
	glBindTexture(GL_TEXTURE_2D, texture_id);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	glTexImage2D(GL_TEXTURE_2D, 0, internal_format, surface->w,
				surface->h, 0, format,
				GL_UNSIGNED_BYTE, surface->pixels);

	glBindTexture(GL_TEXTURE_2D, 0);

	size = t_vect(1.0 / p_size.x, 1.0 / p_size.y);
	t_vect	tmp = t_vect(0, 0);
	int i;

	while (tmp.x * tmp.y < p_size.x * (p_size.y - 1))
	{
		if (tmp.x >= p_size.x)
		{
			tmp.x = 0;
			tmp.y++;
		}
		sprite_list.push_back(t_vect(tmp.x / p_size.x, tmp.y / p_size.y));
		tmp.x++;
	}
}
