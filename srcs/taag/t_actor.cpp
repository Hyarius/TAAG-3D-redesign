#include "taag.h"

t_actor		read_actor(string name)
{
	return (s_actor());
}

void		save_actor(t_actor *to_save, string p_file_name)
{
	printf("test for %s%s in %s\n", p_file_name.c_str(), ACTOR_EXT, ACTOR_PATH);
	if (check_file_exist(ACTOR_PATH, p_file_name + ACTOR_EXT) == false)
		printf("File don't exist\n");
	else
		printf("File exist\n");
}

s_actor::s_actor()
{
	this->name = "";
	this->stat = t_stat();
	this->sprite = 0;
}

s_actor::s_actor(string p_name, int p_level, t_stat p_stat, int p_sprite)
{
	this->name = p_name;
	this->level = p_level;
	this->attrib_point = 0;
	this->stat = p_stat;
	this->sprite = p_sprite;
}
