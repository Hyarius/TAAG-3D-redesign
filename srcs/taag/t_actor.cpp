#include "taag.h"

t_actor		read_actor(t_data data)
{
	string	p_path = *((string *)(data.data[0]));
	vector<string>	tab;
	ifstream 		myfile;
	myfile.open(p_path);
	string	name = get_strsplit(&myfile, ":", 2)[1];
	string	tile = get_strsplit(&myfile, ":", 2)[1];
	tab = get_strsplit(&myfile, ":", 3);
	t_vect	pos = t_vect(atoi(tab[1].c_str()), atoi(tab[1].c_str()));
	tab = get_strsplit(&myfile, ":", 3);
	t_vect	size = t_vect(atoi(tab[1].c_str()), atoi(tab[1].c_str()));
	int		level = atoi(get_strsplit(&myfile, ":", 2)[1].c_str());
	int		point = atoi(get_strsplit(&myfile, ":", 2)[1].c_str());
	int		hp = atoi(get_strsplit(&myfile, ":", 2)[1].c_str());
	int		pa = atoi(get_strsplit(&myfile, ":", 2)[1].c_str());
	int		pm = atoi(get_strsplit(&myfile, ":", 2)[1].c_str());
	int		ini = atoi(get_strsplit(&myfile, ":", 2)[1].c_str());
	int		phy_atk = atoi(get_strsplit(&myfile, ":", 2)[1].c_str());
	int		phy_def = atoi(get_strsplit(&myfile, ":", 2)[1].c_str());
	int		mag_atk = atoi(get_strsplit(&myfile, ":", 2)[1].c_str());
	int		mag_def = atoi(get_strsplit(&myfile, ":", 2)[1].c_str());
	return (s_actor(name, level, point, s_stat(hp, pa, pm, ini, t_element(phy_atk, phy_def), t_element(mag_atk, mag_def))));
}

void		save_actor(t_data data)
{
	t_actor *to_save = (t_actor *)(data.data[0]);
	string	p_path = *((string *)(data.data[1]));
	ofstream myfile;
	myfile.open (p_path);
	myfile << "name:" + to_save->name + "\n";
	myfile << "tileset: NULL\n";
	myfile << "sprite_pos: 0:0\n";
	myfile << "sprite_size: 0:0\n";
	myfile << "level:" + to_string(to_save->level) + "\n";
	myfile << "point:" + to_string(to_save->attrib_point) + "\n";
	myfile << to_string(to_save->stat.hp.max) + ":" + to_string(to_save->stat.pa.max)
				+ ":" + to_string(to_save->stat.pm.max) + ":" + to_string(to_save->stat.ini.max)
				+ ":" + to_string(to_save->stat.phy.atk) + ":" + to_string(to_save->stat.phy.def)
				+ ":" + to_string(to_save->stat.mag.atk) + ":" + to_string(to_save->stat.mag.def) + "\n";
	myfile << "NULL\n";
	myfile << "NULL\n";
	myfile << "NULL\n";
	myfile << "NULL\n";
	myfile << "NULL\n";
	myfile << "NULL\n";
	myfile << "NULL\n";
	myfile << "NULL\n";
	myfile.close();
}

s_actor::s_actor()
{
	this->name = "";
	this->level = 1;
	this->attrib_point = 0;
	this->stat = t_stat();
}

s_actor::s_actor(string p_name, int p_level, int p_pool, t_stat p_stat)
{
	this->name = p_name;
	this->level = p_level;
	this->attrib_point = p_pool;
	this->stat = p_stat;
}
