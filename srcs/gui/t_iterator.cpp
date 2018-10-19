#include "template.h"

static void		increment_value(t_data data)
{
	int			*value = (int *)(data.data[0]);
	int			delta = *((int *)(data.data[1]));
	int			max = *((int *)(data.data[2]));
	int			*pool = (int *)(data.data[3]);
	int			cost = *((int *)(data.data[4]));

	if (pool == NULL || *pool - cost < 0)
		return ;
	if (value != NULL && *value + delta <= max)
	{
		*value += delta;
		*pool -= cost;
	}
}

static void		decrement_value(t_data data)
{
	int			*value = (int *)(data.data[0]);
	int			delta = *((int *)(data.data[1]));
	int			min = *((int *)(data.data[2]));
	int			*pool = (int *)(data.data[3]);
	int			cost = *((int *)(data.data[4]));

	if (pool == NULL)
		return ;
	if (value != NULL && *value - delta >= min)
	{
		*value -= delta;
		*pool += cost;
	}
}

s_iterator::s_iterator(	t_button_comp *p_button0,
						t_button_comp *p_button1,
						t_button_comp *p_button2,
						t_button_comp *p_button3,
						int *p_value, int p_delta, int p_min, int p_max,
						int	*p_pool, int p_cost)
{
	value = p_value;
	pool = p_pool;
	cost = p_cost;
	delta = p_delta;
	min = p_min;
	max = p_max;

	button[0] = p_button0;
	button[0]->set_funct_param(NULL, NULL, draw_lined_text);
	button[0]->coord[2] = button[0]->coord[1] + t_vect(0, button[0]->size[1].y / 2);
	button[1] = p_button1;
	if (button[1] != NULL)
		button[1]->set_funct_param(decrement_value, t_data(5, p_value, &delta, &min, p_pool, &cost), NULL);
	button[2] = p_button2;
	if (value != NULL)
	{
		text_value = to_string(*value);
		button[2]->text = &text_value;
	}
	button[3] = p_button3;
	if (button[3] != NULL)
		button[3]->set_funct_param(increment_value, t_data(5, p_value, &delta, &max, p_pool, &cost), NULL);
}

void			s_iterator::draw_self()
{
	size_t i = 0;

	text_value = to_string(*value);
	while (i < 4)
	{
		if (button[i] != NULL)
			button[i]->draw_self();
		i++;
	}
}

void			s_iterator::click(t_vect mouse)
{
	size_t i = 0;

	while (i < 4)
	{
		if (button[i] != NULL)
			button[i]->click(mouse);
		i++;
	}
}
