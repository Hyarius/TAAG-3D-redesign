#include "taag.h"

s_game_object::s_game_object()
{
	this->name = "";
	this->tile_index = 0;
	this->sprite_pos = t_vect(0, 0);
}

s_game_object::s_game_object(string p_name)
{
	this->name = p_name;
	this->tile_index = 0;
	this->sprite_pos = t_vect(0, 0);
}
