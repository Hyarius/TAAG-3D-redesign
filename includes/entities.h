#ifndef OBJECT_H
# define OBJECT_H

using namespace std;

#include "game_object.h"
#include "spell.h"

typedef struct	s_entities : s_game_object
{
	s_value		hp;
				s_entities();
				s_entities(string p_name, int hp);
}				t_entities;

#endif
