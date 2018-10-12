#include "template.h"

s_button::s_button(t_button_comp *p_button, gui_funct p_funct, t_data p_data)
{
	int i = 0;

	this->button = p_button;
	this->button->set_funct_param(p_funct, p_data);
}

void			s_button::draw_self()
{
	this->button->draw_self();
}

void			s_button::click(t_vect mouse)
{
	this->button->click(mouse);
}
