#include "taag.h"
#include "player_editor_helper.h"

static void		increment_value(t_data data)
{
	int *index = ((int *)(data.data[0]));

	if ((*index) + 1 < node_list.size())
		(*index)++;
}

static void		decrement_value(t_data data)
{
	int *index = ((int *)(data.data[0]));

	if ((*index) > 0)
		(*index)--;
}

s_node_selector::s_node_selector(t_button_comp *p_button1, t_button_comp *p_button2, t_button_comp *p_button3, t_button_comp *p_button4, int *p_index, t_gui *gui)
{
	button[0] = p_button1;
	button[1] = p_button2;
	button[2] = p_button3;
	button[3] = p_button4;
	index = p_index;
	if (button[1] != NULL)
		button[1]->set_funct_param(decrement_value, t_data(1, index));
	if (button[3] != NULL)
		button[3]->set_funct_param(increment_value, t_data(1, index));
}

void			s_node_selector::draw_self()
{
	size_t i = 0;

	while (i < 4)
	{
		if (button[i] != NULL)
		{
			button[i]->draw_self();
			if (i == 2)
				texture_list[node_list[*index]->index]->draw_self(button[i]->coord[1], button[i]->size[1], node_list[*index]->pos);
		}
		i++;
	}
}

void			s_node_selector::click(t_vect mouse)
{
	size_t i = 1;

	while (i < 4)
	{
		if (button[i] != NULL)
			button[i]->click(mouse);
		i++;
	}
}
