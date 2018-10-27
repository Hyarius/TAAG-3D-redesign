#ifndef SPELL_H
# define SPELL_H

# include "template.h"

using namespace std;

typedef struct		s_spell
{
	string			name;
	string 			desc;
	t_image			image;
					s_spell();
}					t_spell;

#endif
