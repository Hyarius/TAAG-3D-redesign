#include "taag.h"

actor		read_actor(string name)
{
	return (actor());
}

void		save_actor(actor *to_save)
{
	printf("test for %s in %s%s\n", ACTOR_PATH, to_save->get_name().c_str(), ACTOR_EXT);
	if (check_file_exist(ACTOR_PATH, to_save->get_name() + ACTOR_EXT) == false)
		printf("File don't exist\n");
	else
		printf("File exist\n");
}

actor::actor()
{
	this->name = "";
	this->stat = t_stat();
	this->sprite = 0;
}

actor::actor(string p_name, t_stat p_stat, int p_sprite)
{
	this->name = p_name;
	this->stat = p_stat;
	this->sprite = p_sprite;
}

void		actor::set_name(string p_name)
{
	this->name = p_name;
}

string		actor::get_name()
{
	return (this->name);
}

t_stat		*actor::get_stat()
{
	return (&(this->stat));
}

int			*actor::get_sprite()
{
	return (&(this->sprite));
}
