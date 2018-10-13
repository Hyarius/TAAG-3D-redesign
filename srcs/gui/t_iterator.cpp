#include "template.h"

static void		increment_value(t_data data)
{
	int			*value = (int *)(data.data[0]);
	int			delta = *((int *)(data.data[1]));
	int			max = *((int *)(data.data[2]));
	string		*text = ((string *)(data.data[3]));

	if (*value + delta <= max)
	{
		*value += delta;
		*text = convert_int(*value);
	}
}

static void		decrement_value(t_data data)
{
	int			*value = (int *)(data.data[0]);
	int			delta = *((int *)(data.data[1]));
	int			min = *((int *)(data.data[2]));
	string		*text = ((string *)(data.data[3]));

	if (*value - delta >= min)
	{
		*value -= delta;
		*text = convert_int(*value);
	}
}

s_iterator::s_iterator(	t_button_comp *p_button0,
						t_button_comp *p_button1,
						t_button_comp *p_button2,
						t_button_comp *p_button3,
						int *p_value, int p_delta, int p_min, int p_max)
{
	delta = p_delta;
	min = p_min;
	max = p_max;
	text_value = to_string(*p_value);

	button[0] = p_button0;

	button[2] = p_button2;
	button[2]->text = &text_value;

	button[1] = p_button1;
	button[1]->set_funct_param(decrement_value, t_data(4, p_value, &delta, &min, button[2]->text));


	button[3] = p_button3;
	button[3]->set_funct_param(increment_value, t_data(4, p_value, &delta, &max, button[2]->text));
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
