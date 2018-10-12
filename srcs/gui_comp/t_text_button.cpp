#include "template.h"

s_text_button::s_text_button(	string *p_text, int p_text_color, //text info
								t_vect p_coord, t_vect p_size, int border, //object info
								t_color p_color1, t_color p_color2) // color info
{
	text = p_text;
	text_color = p_text_color;
	coord[0] = p_coord;
	size[0] = p_size;
	coord[1] = p_coord + border;
	size[1] = p_size - (border * 2);
	if (*text != "")
		text_size = calc_text_size(*text, size[1] - border * 2);
	color[0] = p_color1;
	color[1] = p_color2;
	funct = NULL;
	data = NULL;
}

void		s_text_button::draw_self()
{
	for (int i = 0 ; i < 2 ; i++)
		draw_rectangle(coord[i], size[i], color[i]);
	if (text != NULL && *text != "")
	{
		text_size = calc_text_size(*text, size[1] - (size[0] - size[1]));
		draw_centred_text(*text, text_size, coord[0] + size[0] / 2,
							NORMAL, text_color);
	}
}
