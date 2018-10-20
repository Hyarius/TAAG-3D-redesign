#include "taag.h"

t_actor		read_actor(string name)
{
	return (s_actor());
}

void		save_actor(t_actor *to_save)
{

}

s_actor::s_actor()
{
	this->name = "";
	this->stat = t_stat();
	this->sprite = 0;
}

s_actor::s_actor(string p_name, t_stat p_stat, int p_sprite)
{
	this->name = p_name;
	this->stat = p_stat;
	this->sprite = p_sprite;
}
