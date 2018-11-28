#include "taag.h"

t_entities			read_entities(t_data data)
{

	string	p_path = *((string *)(data.data[0]));
	vector<string>	tab;
	ifstream 		myfile;
	myfile.open(p_path);
	if (myfile.good() == false)
		return (s_entities());
	string	name = get_strsplit(&myfile, ":", 2)[1];
	int		index = atoi(get_strsplit(&myfile, ":", 2)[1].c_str());
	tab = get_strsplit(&myfile, ":", 3);
	t_vect	pos = t_vect(atoi(tab[1].c_str()), atoi(tab[2].c_str()));
	int		hp = atoi(get_strsplit(&myfile, ":", 2)[1].c_str());
	t_entities	entities = s_entities(name, hp);
	entities.tile_index = index;
	entities.sprite_pos = pos;
	return (entities);
}

void			save_entities(t_data data)
{
	t_entities *to_save = (t_entities *)(data.data[0]);
	string	p_path = OBJ_PATH + *((string *)(data.data[1])) + OBJ_EXT;
	ofstream myfile;
	myfile.open (p_path);
	myfile << "name:" + (to_save->name == "" ? "Default" : to_save->name) + "\n";
	myfile << "tileset: " + to_string(to_save->tile_index) + "\n";
	myfile << "sprite_pos: " + to_string(to_save->sprite_pos.x) + ":" + to_string(to_save->sprite_pos.y) + "\n";\
	myfile << "health:" + to_string(to_save->hp.max) + "\n";\
	myfile.close();
}

s_entities::s_entities()
{
	this->name = "";
	this->hp = t_value(0);
	this->tile_index = -1;
	this->sprite_pos = t_vect(-1, -1);
}

s_entities::s_entities(string p_name, int hp)
{
	this->name = "";
	this->hp = t_value(hp);
	this->tile_index = -1;
	this->sprite_pos = t_vect(-1, -1);
}
