#ifndef STRUCTURE_H
# define STRUCTURE_H

using namespace std;

#include "actor.h"
#include "spell.h"

typedef struct		s_spell_card : t_gui_obj
{
	t_button_comp	*button[4]; //0 - background | 1 - image | 2 - name | 3 - description
	t_spell			*spell;//spell of the card

					s_spell_card();
					s_spell_card(	t_button_comp	*p_button0,
									t_button_comp	*p_button1,
									t_button_comp	*p_button2,
									t_button_comp	*p_button3,
									t_spell			*p_spell);
	void			draw_self();
	void			click(t_vect mouse);
}					t_spell_card;

#endif
