#include "taag.h"

string					SPELL_EXT = ".spell";
string					SPELL_PATH = "ressources/spell/";
map<string, t_spell>	spell_list;

void		initialize_spell()
{
	vector<string> spell_files = list_files(SPELL_PATH, SPELL_EXT);
	size_t i = 0;

	spell_list["NULL"] = s_spell();
	while (i < spell_files.size())
	{
		spell_list[spell_files[i]] = s_spell(SPELL_PATH + spell_files[i] + SPELL_EXT);
		i++;
	}
}

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

	if (check_file_exist(p_path) == false)
	{
		path = "NULL";
		name = "Empty";
		desc = "";
		tile = t_tileset();
	}
	else
	{
		path = p_path;
		myfile.open(p_path);
		name = get_strsplit(&myfile, ":", 2)[1];
		desc = get_strsplit(&myfile, ":", 2)[1];
		tab = get_strsplit(&myfile, ":", 4);
		tile = t_tileset(tab[1], t_vect(atoi(tab[2].c_str()), atoi(tab[3].c_str())));
		tab = get_strsplit(&myfile, ":", 3);
		sprite = t_vect(atoi(tab[1].c_str()), atoi(tab[2].c_str()));
	}
}
