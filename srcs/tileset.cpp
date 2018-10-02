#include "template.h"

using namespace std;

tileset				*create_tileset(string path)
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

static SDL_Rect		*create_rect_list(int size)
{
	SDL_Rect *tmp;

	if (!(tmp = (SDL_Rect *)malloc(sizeof(SDL_Rect) * size)))
		error_exit("Can't malloc a SDL_Rect", 165);
	return (tmp);
}

tileset::tileset(string path, int value_x, int value_y)
{
	int				i;
	t_vect			coord;

	this->path = path;
	this->surface = IMG_Load(path.c_str());
	if (this->surface == NULL)
		error_exit("Can't open a tileset : " + path, 245);
	this->nb_tile = t_vect(value_x, value_y);
	this->sprite_list = create_rect_list(value_x * value_y);
	i = 0;
	coord = t_vect(0, 0);
	while (i < value_x * value_y)
	{
		if (coord.x >= value_x)
		{
			coord.x = 0;
			coord.y++;
		}
		set_sdl_rect(&(sprite_list[i]), coord.x * this->nb_tile.x,
						coord.y * this->nb_tile.y, this->nb_tile.x, this->nb_tile.y);
		coord = t_vect(coord.x + 1, coord.y);
		i++;
	}
}

void				tileset::draw_sprite(int sprite, t_vect tl, t_vect tr, t_vect dl, t_vect dr)
{
	t_point		tl_opengl = screen_to_opengl(tl);
	t_point		tr_opengl = screen_to_opengl(tr);
	t_point		dl_opengl = screen_to_opengl(dl);
	t_point		dr_opengl = screen_to_opengl(dr);

	SDL_Rect	*img = this->get_rect(sprite);

	double x1, y1, x2, y2;

	x1 = (img->x) / (double)this->get_surface()->w;
	y1 = (img->y) / (double)this->get_surface()->h;
	x2 = (img->x + img->w) / (double)this->get_surface()->w;
	y2 = (img->y + img->h) / (double)this->get_surface()->h;

	t_triangle a = t_triangle(t_point(dl_opengl.x, dl_opengl.y, x1, y1),
		t_point(dr_opengl.x, dr_opengl.y, x2, y1),
		t_point(tl_opengl.x, tl_opengl.y, x1, y2));

	t_triangle b = t_triangle(t_point(tl_opengl.x, tl_opengl.y, x1, y2),
		t_point(tr_opengl.x, tr_opengl.y, x2, y2),
		t_point(dr_opengl.x, dr_opengl.y, x2, y1));

	draw_triangle_texture(a);
	draw_triangle_texture(b);
}

void				tileset::reload_texture()
{
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, this->get_surface()->w, this->get_surface()->h, 0, GL_RGBA, GL_UNSIGNED_BYTE, this->get_surface()->pixels);
}

GLuint				tileset::get_texture_id()
{
	return (this->texture_id);
}

GLuint				tileset::get_texture_info()
{
	return (this->texture_info);
}

GLenum				tileset::get_format()
{
	return (this->format);
}

GLint				tileset::get_internal_format()
{
	return (this->internal_format);
}

SDL_Rect			*tileset::get_rect(int sprite)
{
	return (&(this->sprite_list[sprite]));
}

SDL_Surface			*tileset::get_surface()
{
	return (this->surface);
}

int					tileset::get_sprite(int x, int y)
{
	int result;

	result = x + (this->nb_tile.x * y);
	if (result > this->nb_tile.x * this->nb_tile.y)
		return (0);
	return (result);
}
