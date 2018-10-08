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

void		s_text_button::set_funct_param(gui_funct p_funct, t_data p_data)
{
	this->funct = p_funct;
	this->data = p_data;
}

void		s_text_button::draw_self()
{
	int i = 0;

	while (i < 2)
	{
		draw_rectangle(coord[i], size[i], color[i]);
		i++;
	}
	draw_centred_text(text, text_size, coord[0] + size[0] / 2, NORMAL, text_color);
}

void		s_text_button::click(t_vect mouse)
{
	if (mouse > this->coord[0] && mouse < this->coord[0] + this->size[0])
		if (this->funct != NULL)
			this->funct(this->data);
}
