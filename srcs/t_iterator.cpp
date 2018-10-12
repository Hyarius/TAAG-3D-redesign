#include "template.h"

s_iterator::s_iterator(	t_button_comp *p_button0,
			t_button_comp *p_button1, gui_funct p_funct1, t_data p_data1,
			t_button_comp *p_button2, gui_funct p_funct2, t_data p_data2,
			t_button_comp *p_button3, gui_funct p_funct3, t_data p_data3)
{
	button[0] = p_button0;

	button[1] = p_button1;
	button[1]->set_funct_param(p_funct1, p_data1);

	button[2] = p_button2;
	button[2]->set_funct_param(p_funct2, p_data2);

	button[3] = p_button3;
	button[3]->set_funct_param(p_funct3, p_data3);
}

void			s_iterator::draw_self()
{
	size_t i = 0;

	while (i < 4)
	{
		button[i]->draw_self();
		i++;
	}
}

void			s_iterator::click(t_vect mouse)
{
	size_t i = 0;

	while (i < 4)
	{
		button[i]->click(mouse);
		i++;
	}
}
