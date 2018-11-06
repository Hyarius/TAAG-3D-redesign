#include "taag.h"

s_spell::s_spell()
{
	path = "NULL";
	name = "Empty";
	desc = "";
	tile = t_tileset();
}

s_spell::s_spell(string p_path)
{
	ifstream	myfile;
	vector<string>	tab;

	if (check_file_exist(SPELL_PATH + p_path + SPELL_EXT) == false)
	{
		path = "NULL";
		name = "Empty";
		desc = "";
		tile = t_tileset();
	}
	else
	{
		path = p_path;
		myfile.open(SPELL_PATH + p_path + SPELL_EXT);
		name = get_strsplit(&myfile, ":", 2)[1];
		desc = get_strsplit(&myfile, ":", 2)[1];
		tab = get_strsplit(&myfile, ":", 4);
		tile = t_tileset(tab[1], t_vect(atoi(tab[2].c_str()), atoi(tab[3].c_str())));
		tab = get_strsplit(&myfile, ":", 3);
		sprite = t_vect(atoi(tab[1].c_str()), atoi(tab[2].c_str()));
	}
}
