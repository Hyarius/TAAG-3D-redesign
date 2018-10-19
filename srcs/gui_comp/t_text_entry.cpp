#include "template.h"

s_text_entry::s_text_entry(	string *p_desc, string *p_text, int p_text_color,
				t_entry_comp **p_selected_entry,
				t_vect p_coord, t_vect p_size, int border,
				t_color p_color1, t_color p_color2, t_color p_color3)
{
	desc = p_desc;
	text = p_text;
	text_color = p_text_color;
	coord[0] = p_coord;
	size[0] = p_size;
	coord[1] = p_coord + border;
	size[1] = p_size - (border * 2);
	coord[2] = coord[1] + t_vect(0, size[1].y / 2);
	if (desc != NULL && *desc != "")
		desc_size = calc_text_max_size(*desc, NORMAL, size[1] - border * 2);
	text_size = calc_text_max_size("M", NORMAL, size[1] - border * 2);
	color[0] = p_color1;
	color[1] = p_color2;
	color[2] = p_color3;
	selected_entry = p_selected_entry;
}

void		s_text_entry::draw_self()
{
	if (*(selected_entry) != this)
		draw_rectangle(coord[0], size[0], color[0]);
	else
		draw_rectangle(coord[0], size[0], color[2]);
	draw_rectangle(coord[1], size[1], color[1]);
	if (text != NULL && *text == "" && desc != NULL && *desc != "")
		draw_lined_text(*desc, desc_size, coord[2], NORMAL, text_color);
	if (text != NULL && *text != "")
		draw_lined_text(*text, text_size, coord[2], NORMAL, text_color);
}
