#include "taag.h"

static void		increment_value(t_data data)
{
	int *index = *((int **)(data.data[0]));
	t_vect *selected = *((t_vect **)(data.data[1]));
	t_vect	increment = *((t_vect *)(data.data[2]));

	selected->x += increment.x;
	if (tile_list[*index]->nb_sprite.x <= selected->x)
	{
		selected->x = 0;
		selected->y += increment.y;
	}
	if (tile_list[*index]->nb_sprite.y <= selected->y)
	{
		selected->x = 0;
		selected->y = 0;
		(*index)++;
	}
	if (*index >= tile_list.size())
		*index = 0;
}

static void		decrement_value(t_data data)
{
	int *index = *((int **)(data.data[0]));
	t_vect *selected = *((t_vect **)(data.data[1]));
	t_vect	increment = *((t_vect *)(data.data[2]));

	selected->x -= increment.x;
	if (selected->x < 0)
	{
		selected->x = tile_list[*index]->nb_sprite.x - increment.x;
		selected->y -= increment.y;
	}
	if (selected->y < 0)
	{
		selected->x = tile_list[*index]->nb_sprite.x - increment.x;
		selected->y = tile_list[*index]->nb_sprite.y - increment.y;
		(*index)--;
	}
	if (*index < 0)
		*index = tile_list.size() - 1;
}

s_sprite_selector::s_sprite_selector(t_button_comp *p_button1, t_button_comp *p_button2, t_button_comp *p_button3, t_button_comp *p_button4, int *p_index, t_vect *p_selected, t_vect p_increment)
{
	button[0] = p_button1;
	button[1] = p_button2;
	button[2] = p_button3;
	button[3] = p_button4;
	if (button[1] != NULL)
		button[1]->set_funct_param(decrement_value, t_data(3, &index, &sprite_selected, &increment));
	if (button[2] != NULL)
		button[2]->set_funct_param(NULL, NULL);
	if (button[3] != NULL)
		button[3]->set_funct_param(increment_value, t_data(3, &index, &sprite_selected, &increment));
	index = p_index;
	sprite_selected = p_selected;
	increment = p_increment;
}

void			s_sprite_selector::draw_self()
{
	size_t i = 0;

	while (i < 4)
	{
		if (button[i] != NULL)
		{
			button[i]->draw_self();
			if (i == 2)
				tile_list[*index]->draw_self(button[i]->coord[1], button[i]->size[1], *sprite_selected);
		}
		i++;
	}
}

void			s_sprite_selector::click(t_vect mouse)
{
	size_t i = 1;

	while (i < 4)
	{
		if (button[i] != NULL)
			button[i]->click(mouse);
		i++;
	}
}

void			s_sprite_selector::reset_actor(t_actor *actor)
{
	index = &(actor->tile_index);
	sprite_selected = &(actor->sprite_pos);
}