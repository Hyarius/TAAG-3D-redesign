#include "template.h"

s_text_button::s_text_button(	string p_text, int p_text_color, //text info
								t_vect p_coord, t_vect p_size, int border, //object info
								t_color p_color1, t_color p_color2) // color info
{
	this->text = p_text;
	this->text_color = p_text_color;
	this->coord[0] = p_coord;
	this->size[0] = p_size;
	this->coord[1] = p_coord + border;
	this->size[1] = p_size - (border * 2);
	this->text_size = calc_text_size(this->text, this->size[1]);
	this->color[0] = p_color1;
	this->color[1] = p_color2;
	this->funct = NULL;
	this->data = NULL;
}

void		s_text_button::draw_self()
{
	for (int i = 0 ; i < 2 ; i++)
		draw_rectangle(coord[i], size[i], color[i]);
	draw_centred_text(text, text_size, coord[0] + size[0] / 2, NORMAL, text_color);
}
