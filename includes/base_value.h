#include "include.h"

extern vector<int>			g_hp;
extern vector<int>			g_pa;
extern vector<int>			g_pm;
extern vector<int>			g_init;
extern vector<int>			g_atk_phy;
extern vector<int>			g_atk_mag;
extern vector<int>			g_def_phy;
extern vector<int>			g_def_mag;

extern bool					draw_fps;

extern mat4					camera;
extern mat4					projection;

extern GLuint				M_Matrix_ID;
extern GLuint				M_Texture_ID;
extern GLuint				T_Texture_ID;
extern GLuint				C_Matrix_ID;

extern t_color				color[4];

extern map<string, t_spell>	spell_list;
extern vector<t_tileset *>	tile_list;
extern vector<t_tileset *>	texture_list;

extern string				ACT_EXT;
extern string				ACT_PATH;
extern string				SPELL_EXT;
extern string				SPELL_PATH;

extern int					GUI_OBJ_ID;
extern int					ITERATOR_ID;
extern int					SPRITE_SELECTOR_ID;
extern int					SPELL_CARD_ID;
extern int					SPRITE_IMAGE_ID;
