#include "taag.h"

vector<int>		g_hp = {5, 100, 200};
vector<int>		g_pa = {1, 6, 14};
vector<int>		g_pm = {1, 3, 10};
vector<int>		g_init = {2, 50, 150};
vector<int>		g_atk_phy = {1, 0, 50};
vector<int>		g_atk_mag = {1, 0, 50};
vector<int>		g_def_phy = {1, 0, 50};
vector<int>		g_def_mag = {1, 0, 50};

bool			draw_fps = true;

string			ACT_EXT = ".act";
string			ACT_PATH = "ressources/actor/";

t_color			color[4] = {t_color(0.5, 0.5, 0.5),
							t_color(0.6, 0.6, 0.6),
							t_color(1.0, 1.0, 0.7),
							t_color(0.7, 0.7, 0.7)};

int				GUI_OBJ_ID = 0;
int				ITERATOR_ID = 1;
int				SPELL_CARD_ID = 2;
