#include "taag.h"

vector<int>				g_hp = {5, 100, 200};
vector<int>				g_pa = {1, 6, 14};
vector<int>				g_pm = {1, 3, 10};
vector<int>				g_init = {2, 50, 150};
vector<int>				g_atk_phy = {1, 0, 50};
vector<int>				g_atk_mag = {1, 0, 50};
vector<int>				g_def_phy = {1, 0, 50};
vector<int>				g_def_mag = {1, 0, 50};

bool					draw_fps = true;

t_color					color[4] = {t_color(0.5, 0.5, 0.5),
							t_color(0.6, 0.6, 0.6),
							t_color(1.0, 1.0, 0.7),
							t_color(0.7, 0.7, 0.7)};

string					ACT_EXT = ".act";
string					ACT_PATH = "ressources/actor/";
string					SPELL_EXT = ".spell";
string					SPELL_PATH = "ressources/spell/";
string					SPRITE_EXT = ".spr";
string					SPRITE_PATH = "ressources/charset/";
string					TEXTURE_EXT = ".tex";
string					TEXTURE_PATH = "ressources/tileset/";
string					NODE_EXT = ".node";
string					NODE_PATH = "ressources/node/";
string					MAP_EXT = ".map";
string					MAP_PATH = "ressources/map/";
string					OBJ_EXT = ".act";
string					OBJ_PATH = "ressources/object/";

map<string, t_spell>	spell_list;
vector<t_tileset *>		tile_list;
vector<t_tileset *>		texture_list;
vector<t_node *>		node_list;

int						GUI_OBJ_ID = 0;
int						ITERATOR_ID = 1;
int						SPELL_CARD_ID = 2;
int						SPRITE_SELECTOR_ID = 3;
int						SPRITE_IMAGE_ID = 4;

void			initiate_sprite()
{
	ifstream		file;
	vector<string>	sprite_files = list_files(SPRITE_PATH, SPRITE_EXT);
	size_t			i = 0;
	string			path;
	vector<string>	line;
	t_vect			size;

	while (i < sprite_files.size())
	{
		file.open(SPRITE_PATH + sprite_files[i] + SPRITE_EXT);
		path = get_strsplit(&file, ":", 2)[1];
		line = get_strsplit(&file, ":", 3);
		size = t_vect(atoi(line[1].c_str()), atoi(line[2].c_str()));
		tile_list.push_back(new t_tileset(path, size));
		file.close();
		i++;
	}
}

void			initiate_texture()
{
	ifstream		file;
	vector<string>	texture_files = list_files(TEXTURE_PATH, TEXTURE_EXT);
	size_t			i = 0;
	string			path;
	vector<string>	line;
	t_vect			size;

	while (i < texture_files.size())
	{
		file.open(TEXTURE_PATH + texture_files[i] + TEXTURE_EXT);
		path = get_strsplit(&file, ":", 2)[1];
		line = get_strsplit(&file, ":", 3);
		size = t_vect(atoi(line[1].c_str()), atoi(line[2].c_str()));
		texture_list.push_back(new t_tileset(path, size));
		file.close();
		i++;
	}
}

void		initialize_spell()
{
	vector<string> spell_files = list_files(SPELL_PATH, SPELL_EXT);
	size_t i = 0;

	spell_list["NULL"] = s_spell();
	while (i < spell_files.size())
	{
		spell_list[spell_files[i]] = s_spell(spell_files[i]);
		i++;
	}
}

void		initialize_node()
{
	vector<string>	node_files = list_files(NODE_PATH, NODE_EXT);
	size_t			i = 0;

	while (i < node_files.size())
	{
		node_list.push_back(new t_node(NODE_PATH + node_files[i] + NODE_EXT));
		i++;
	}
}
