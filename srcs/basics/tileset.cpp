#include "template.h"

tileset			*create_tileset(string path)
{
	ifstream file;
	string line;
	vector<string> split_line;

	file.open(path);
	if (!file.good())
		error_exit("Cant open such file : " + path, 7946);
	line = get_strsplit(&file, ":", 2)[1];
	split_line = get_strsplit(&file, ":", 3);
	return (new tileset(line, atoi(split_line[1].c_str()), atoi(split_line[2].c_str())));
}

void			tileset::draw_image(t_vect tl, t_vect tr, t_vect dl, t_vect dr,
									t_vect s_tl, t_vect s_dr)
{
	t_point		tl_opengl = screen_to_opengl(tl);
	t_point		tr_opengl = screen_to_opengl(tr);
	t_point		dl_opengl = screen_to_opengl(dl);
	t_point		dr_opengl = screen_to_opengl(dr);

	draw_triangle_texture(t_point(tl_opengl.x, tl_opengl.y, 0.0, 0.0),
		t_point(tr_opengl.x, tr_opengl.y, 1.0, 0.0),
		t_point(dl_opengl.x, dl_opengl.y, 0.0, 1.0));

	draw_triangle_texture(t_point(dl_opengl.x, dl_opengl.y, 0.0, 1.0),
		t_point(dr_opengl.x, dr_opengl.y, 1.0, 1.0),
		t_point(tr_opengl.x, tr_opengl.y, 1.0, 0.0));
}

void 			tileset::draw_tile(int sprite, t_vect coord, t_vect size)
{
	glBindTexture(GL_TEXTURE_2D, texture_id);
	draw_tileset(p_coord, p_size);
}

void 			draw_centred_tileset(int sprite, t_vect coord, t_vect size)
{
	static int a = 0;

	if (a == 0 && !(a++))
		printf("still to do draw_centred_tileset\n");
}

void			set_sdl_rect(SDL_Rect *rect, int x, int y, int w, int h)
{
	rect->x = x;
	rect->y = y;
	rect->w = w;
	rect->h = h;
}

tileset::tileset(string path, int value_x, int value_y)
{
	int				i;
	t_vect			coord;

	path = path;
	image = IMG_Load(path.c_str());
	if (image == NULL)
		error_exit("Can't open a tileset : " + path, 245);
	nb_tile = t_vect(value_x, value_y);
	size = t_vect(image->w / value_x / image->w, image->h / value_y / image->h);
	sprite_list.resize(value_x * value_y);
	i = 0;
	t_vect coord = t_vect(0, 0);
	while (i < value_x * value_y)
	{
		if (coord.x >= value_x)
		{
			coord.x = 0;
			coord.y++;
		}
		sprite_list[i] = t_vect(coord.x * size.x, coord.y * size.y)
		coord = t_vect(coord.x + 1, coord.y);
		i++;
	}
	if (image->format->BytesPerPixel == 3)
	{
		internal_format = GL_RGB;
		if (image->format->Rmask == 0xff)
			format = GL_RGB;
		else
			format = GL_BGR;
	}
	else if (image->format->BytesPerPixel == 4)
	{
		internal_format = GL_RGBA;
		if (image->format->Rmask == 0xff)
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
}

int			tileset::get_sprite(int x, int y)
{
	int result;

	result = x + (nb_tile.x * y);
	if (result > nb_tile.x * nb_tile.y)
		return (0);
	return (result);
}
