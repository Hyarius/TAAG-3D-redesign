#include "template.h"

s_image_button::s_image_button(string *p_text, int p_text_color,
						t_image p_image, t_vect p_coord, t_vect p_size, int border)
{
	text = p_text;
	text_color = p_text_color;
	coord[0] = p_coord;
	size[0] = p_size;
	coord[1] = p_coord + border;
	size[1] = p_size - (border * 2);
	if (*text != "")
		text_size = calc_text_size(*text, size[1] - border * 2);
	image = p_image;
	funct = NULL;
	data = NULL;
}

s_image_button::s_image_button(t_image p_image, t_vect p_coord, t_vect p_size)
{
	text = NULL;
	coord[0] = p_coord;
	size[0] = p_size;
	image = p_image;
	funct = NULL;
	data = NULL;
}

void		s_image_button::draw_self()
{
	image.draw_self(coord[0], size[0]);
	if (text != NULL && *text != "")
	{
		text_size = calc_text_size(*text, size[1] - (size[0] - size[1]));
		draw_centred_text(*text, text_size, coord[1] + size[1] / 2, NORMAL, text_color);
	}
}
