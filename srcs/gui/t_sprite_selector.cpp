#include "taag.h"

s_sprite_selector::s_sprite_selector(t_button_comp *p_button1, t_button_comp *p_button2, int *p_index, t_vect *p_selected, t_vect p_increment)
{
	button[0] = p_button1;
	button[1] = p_button2;
	if (button[1] != NULL)
		button[1]->set_funct_param(NULL, NULL);
	index = p_index;
	sprite_selected = p_selected;
	increment = p_increment;
}

void			s_sprite_selector::draw_self()
{
	if (button[0] != NULL)
		button[0]->draw_self();
	if (button[1] != NULL)
		button[1]->draw_self();
	if (button[1] != NULL)
	{
		printf("printf at %f / %f\n", button[1]->coord[1].x, button[1]->coord[1].y);
		printf("sized at %f / %f\n", button[1]->size[1].x, button[1]->size[1].y);
		printf("index %d\n", *index);
		printf("sprite %f / %f\n", sprite_selected->x, sprite_selected->y);
		tile_list[*index]->draw_self(button[1]->coord[1], button[1]->size[1], *sprite_selected);
	}
}

void			s_sprite_selector::click(t_vect mouse)
{
	button[1]->click(mouse);
}
