#include "taag.h"

s_spell_card::s_spell_card()
{
	button[0] = NULL;
	button[1] = NULL;
	button[2] = NULL;
	button[3] = NULL;
	spell = NULL;
}

s_spell_card::s_spell_card(	t_button_comp	*p_button0,
				t_button_comp	*p_button1,
				t_button_comp	*p_button2,
				t_button_comp	*p_button3,
				t_spell			*p_spell)
{
	button[0] = p_button0;
	button[1] = p_button1;
	button[2] = p_button2;
	button[3] = p_button3;
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
