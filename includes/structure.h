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
					s_spell_card(t_spell *p_spell, t_vect coord, t_vect size, gui_funct p_funct, t_data p_data);
	void			draw_self();
	void			click(t_vect mouse);
}					t_spell_card;

#endif
