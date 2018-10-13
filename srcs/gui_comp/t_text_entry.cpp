#include "template.h"

s_text_entry::s_text_entry(	string *p_text, int p_text_color,
				t_entry_comp **p_selected_entry,
				t_vect p_coord, t_vect p_size, int border,
				t_color p_color1, t_color p_color2)
{
	text = p_text;
	text_color = p_text_color;
	coord[0] = p_coord;
	size[0] = p_size;
	coord[1] = p_coord + border;
	size[1] = p_size - (border * 2);
	coord[2] = coord[1] + t_vect(0, size[1].y / 2);
	if (text != NULL && *text != "")
		text_size = calc_text_size(*text, size[1] - border * 2);
	color[0] = p_color1;
	color[1] = p_color2;
	selected_entry = p_selected_entry;
}

void		s_text_entry::draw_self()
{
	for (int i = 0 ; i < 2 ; i++)
		draw_rectangle(coord[i], size[i], color[i]);
	if (text != NULL && *text != "")
		draw_lined_text(*text, text_size, coord[2], NORMAL, text_color);
}
