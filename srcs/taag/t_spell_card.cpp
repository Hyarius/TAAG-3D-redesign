#include "taag.h"

s_spell_card::s_spell_card()
{
	button[0] = NULL;
	button[1] = NULL;
	button[2] = NULL;
	button[3] = NULL;
	spell = NULL;
}

s_spell_card::s_spell_card(t_spell *p_spell, t_vect p_coord, t_vect p_size, gui_funct p_funct, t_data p_data)
{
	t_button_comp	*button0 = NULL;
	t_button_comp	*button1 = NULL;
	t_button_comp	*button2 = NULL;
	t_button_comp	*button3 = NULL;

	button0 = new t_text_button(NULL, DARK_GREY, //text info
						p_coord, p_size, 4, //object info
						t_color(0.5, 0.5, 0.5), t_color(0.6, 0.6, 0.6));
	button1 = new t_text_button(NULL, DARK_GREY, //text info
						p_coord + p_size.x / 20, t_vect(p_size.x - p_size.x / 10, p_size.x - p_size.x / 10), 4, //object info
						t_color(0.5, 0.5, 0.5), t_color(1.0, 1.0, 0.7));
	button2 = new t_text_button(NULL, DARK_GREY, //text info
						t_vect(0, 0), t_vect(0, 0), 0, //object info
						t_color(0.5, 0.5, 0.5), t_color(0.6, 0.6, 0.6));
	button3 = new t_text_button(NULL, DARK_GREY, //text info
						t_vect(0, 0), t_vect(0, 0), 0, //object info
						t_color(0.5, 0.5, 0.5), t_color(0.6, 0.6, 0.6));

	button[0] = button0;
	button[1] = NULL;
	button[2] = NULL;
	button[3] = NULL;
	spell = p_spell;
}

void			s_spell_card::draw_self()
{
	size_t i = 0;

	while (i < 4)
	{
		if (button[i] != NULL)
			button[i]->draw_self();
		i++;
	}
}

void			s_spell_card::click(t_vect mouse)
{
	size_t i = 0;

	while (i < 4)
	{
		if (button[i] != NULL)
			button[i]->click(mouse);
		i++;
	}
}
