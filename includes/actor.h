#ifndef ACTOR_H
# define ACTOR_H

using namespace std;

#include "game_object.h"
#include "spell.h"

typedef struct	s_actor : s_game_object
{
	int			level;
	int			attrib_point;
	t_stat		stat;
	t_spell		spell[8];
				s_actor();
				s_actor(string p_name, int p_level, int p_pool, t_stat p_stat);
}				t_actor;

#endif
