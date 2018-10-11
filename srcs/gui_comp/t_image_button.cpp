#include "template.h"

s_image_button::s_image_button(string p_text, int p_text_color,
						t_image p_image, t_vect p_coord, t_vect p_size, int border)
{
	this->text = p_text;
	this->text_color = p_text_color;
	this->coord[0] = p_coord;
	this->size[0] = p_size;
	this->coord[1] = p_coord + border;
	this->size[1] = p_size - (border * 2);
	this->text_size = calc_text_size(this->text, this->size[1]);
	this->image = p_image;
	this->funct = NULL;
	this->data = NULL;
}

s_image_button::s_image_button(t_image p_image, t_vect p_coord, t_vect p_size)
{
	this->text = "";
	this->coord[0] = p_coord;
	this->size[0] = p_size;
	this->image = p_image;
	this->funct = NULL;
	this->data = NULL;
}

void		s_image_button::draw_self()
{
	this->image.draw_self(coord[0], size[0]);
	if (text != "")
		draw_centred_text(text, text_size, coord[1] + size[1] / 2, NORMAL, text_color);
}
