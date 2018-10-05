#include "taag.h"

player::player()
{
	this->stat = t_stat();
	this->sprite = 0;
}

player::player(t_stat p_stat, int p_sprite)
{
	this->stat = p_stat;
	this->sprite = p_sprite;
}

t_stat		*player::get_stat()
{
	return (&(this->stat));
}

int			*player::get_sprite()
{
	return (&(this->sprite));
}
