#ifndef SPELL_H
# define SPELL_H

# include "template.h"

using namespace std;

typedef struct		s_spell
{
	string			path;
	string			name;
	string 			desc;
	t_tileset		tile;
	t_vect			sprite;
					s_spell();
					s_spell(string p_path);
}					t_spell;

#endif
