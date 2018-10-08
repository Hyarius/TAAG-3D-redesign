#include "template.h"

s_image_button::s_image_button(t_image p_image, t_vect p_coord, t_vect p_size)
{
	this->image = p_image;
	this->coord = p_coord;
	this->size = p_size;
	this->funct = NULL;
	this->data = NULL;
}

void		s_image_button::set_funct_param(gui_funct p_funct, t_data p_data)
{
	this->funct = p_funct;
	this->data = p_data;
}

void		s_image_button::draw_self()
{
	this->image.draw_self(coord, size);
}

void		s_image_button::click(t_vect mouse)
{
	if (mouse > this->coord && mouse < this->coord + this->size)
		if (this->funct != NULL)
			this->funct(this->data);
}
