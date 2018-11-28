#include "taag.h"

t_game_object			read_object(t_data data)
{

	string	p_path = *((string *)(data.data[0]));
	vector<string>	tab;
	ifstream 		myfile;
	myfile.open(p_path);
	if (myfile.good() == false)
		return (s_game_object("", s_stat(g_hp[1], g_pa[1], g_pm[1], g_init[1], t_element(g_atk_phy[1], g_def_phy[1]), t_element(g_atk_mag[1], g_def_mag[1]))));
	string	name = get_strsplit(&myfile, ":", 2)[1];
	int		index = atoi(get_strsplit(&myfile, ":", 2)[1].c_str());
	tab = get_strsplit(&myfile, ":", 3);
	t_vect	pos = t_vect(atoi(tab[1].c_str()), atoi(tab[2].c_str()));
	tab = get_strsplit(&myfile, ":", 3);
	t_vect	size = t_vect(atoi(tab[1].c_str()), atoi(tab[2].c_str()));
	int		hp = atoi(get_strsplit(&myfile, ":", 2)[1].c_str());
	int		pa = atoi(get_strsplit(&myfile, ":", 2)[1].c_str());
	int		pm = atoi(get_strsplit(&myfile, ":", 2)[1].c_str());
	int		ini = atoi(get_strsplit(&myfile, ":", 2)[1].c_str());
	int		phy_atk = atoi(get_strsplit(&myfile, ":", 2)[1].c_str());
	int		phy_def = atoi(get_strsplit(&myfile, ":", 2)[1].c_str());
	int		mag_atk = atoi(get_strsplit(&myfile, ":", 2)[1].c_str());
	int		mag_def = atoi(get_strsplit(&myfile, ":", 2)[1].c_str());
	t_game_object	object = s_game_object(name, s_stat(hp, pa, pm, ini, t_element(phy_atk, phy_def), t_element(mag_atk, mag_def)));
	object.tile_index = index;
	object.sprite_pos = pos;
	object.sprite_size = size;
	return (object);
}

void			save_object(t_data data)
{
	t_game_object *to_save = (t_game_object *)(data.data[0]);
	string	p_path = OBJ_PATH + *((string *)(data.data[1])) + OBJ_EXT;
	ofstream myfile;
	myfile.open (p_path);
	myfile << "name:" + (to_save->name == "" ? "Default" : to_save->name) + "\n";
	myfile << "tileset: " + to_string(to_save->tile_index) + "\n";
	myfile << "sprite_pos: " + to_string(to_save->sprite_pos.x) + ":" + to_string(to_save->sprite_pos.y) + "\n";
	myfile << "sprite_size: " + to_string(to_save->sprite_size.x) + ":" + to_string(to_save->sprite_size.y) + "\n";
	myfile << "health:" + to_string(to_save->stat.hp.max) + "\n";
	myfile << "action:" + to_string(to_save->stat.pa.max) + "\n";
	myfile << "mouvement:" + to_string(to_save->stat.pm.max) + "\n";
	myfile << "initiative:" + to_string(to_save->stat.ini.max) + "\n";
	myfile << "attack phy:" + to_string(to_save->stat.phy.atk) + "\n";
	myfile << "defense phy:" + to_string(to_save->stat.phy.atk) + "\n";
	myfile << "attack mag:" + to_string(to_save->stat.mag.atk) + "\n";
	myfile << "defense mag:" + to_string(to_save->stat.mag.def) + "\n";
	myfile.close();
}

s_game_object::s_game_object()
{
	this->name = "";
	this->stat = t_stat();
	this->tile_index = 0;
	this->sprite_pos = t_vect(0, 0);
	this->sprite_size = t_vect(1, 1);
}

s_game_object::s_game_object(string p_name, t_stat p_stat)
{
	this->name = p_name;
	this->stat = p_stat;
	this->tile_index = 0;
	this->sprite_pos = t_vect(0, 0);
	this->sprite_size = t_vect(1, 1);
}
