#include "template.h"

s_image_entry::s_image_entry(	string *p_text, int p_text_color,
								t_entry_comp **p_selected_entry,
								t_image p_image, t_vect p_coord, t_vect p_size, int border)
{
	text = p_text;
	text_color = p_text_color;
	coord[0] = p_coord;
	size[0] = p_size;
	coord[1] = p_coord + border;
	size[1] = p_size - (border * 2);
	coord[2] = coord[1] + t_vect(0, size[1].y / 2);
	if (*text != "")
		text_size = calc_text_size(*text, size[1] - border * 2);
	selected_entry = p_selected_entry;
	image = p_image;
}

void		s_image_entry::draw_self()
{
	image.draw_self(coord[0], size[0]);
	if (text != NULL && *text != "")
		draw_lined_text(*text, text_size, coord[2], NORMAL, text_color);
}
