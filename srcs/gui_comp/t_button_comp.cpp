#include "template.h"

void		s_button_comp::set_funct_param(gui_funct p_funct, t_data p_data, d_funct p_draw_funct)
{
	this->funct = p_funct;
	this->data = p_data;
	if (p_draw_funct != NULL)
		this->draw_funct = p_draw_funct;
}

void		s_button_comp::click(t_vect mouse)
{
	if (mouse > this->coord[0] && mouse < this->coord[0] + this->size[0])
		if (this->funct != NULL)
			this->funct(this->data);
}
