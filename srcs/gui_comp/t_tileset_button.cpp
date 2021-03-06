#include "template.h"
#include "base_value.h"

s_tileset_button::s_tileset_button(string *p_text, int p_text_color,
							vector<t_tileset *> *p_tile, int *p_index, t_vect p_selected,
							t_vect p_coord, t_vect p_size, int border)
{
	text = p_text;
	text_color = p_text_color;
	coord[0] = p_coord;
	size[0] = p_size;
	coord[1] = p_coord + border;
	size[1] = p_size - (border * 2);
	coord[2] = coord[1] + size[1] / 2;
	if (text != NULL && *text != "")
		text_size = calc_text_size(*text, size[1] - border * 2);
	tile = p_tile;
	index = p_index;
	selected = p_selected;
	funct = NULL;
	data = NULL;
	draw_funct = draw_centred_text;
}

s_tileset_button::s_tileset_button(vector<t_tileset *> *p_tile, int *p_index, t_vect p_selected,
							t_vect p_coord, t_vect p_size, int border)
{
	text = NULL;
	coord[0] = p_coord;
	size[0] = p_size;
	coord[1] = p_coord + border;
	size[1] = p_size - (border * 2);
	coord[2] = coord[1] + size[1] / 2;
	tile = p_tile;
	index = p_index;
	selected = p_selected;
	funct = NULL;
	data = NULL;
	draw_funct = draw_centred_text;
}

void			s_tileset_button::draw_self()
{
	draw_rectangle(coord[0], size[0], color[0]);
	draw_rectangle(coord[1], size[1], color[3]);
	if (*index >= 0 && selected.x >= 0 && selected.y >= 0)
		((*tile)[*index])->draw_self(coord[1], size[1], selected);
	if (text != NULL && *text != "")
	{
		if (text_size == -1 || size[1].x > calc_text_len(*text, text_size)
							|| size[1].y > get_char(text_size, BLACK, 'M')->surface->h)
			text_size = calc_text_size(*text, size[1] - (size[0] - size[1]));
		this->draw_funct(*text, text_size, coord[2], text_color);
	}
}
