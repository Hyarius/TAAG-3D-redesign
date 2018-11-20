#ifndef MAP_EDITOR_HELPER_H
# define MAP_EDITOR_HELPER_H

#include "taag.h"

void			control_empty(SDL_Event *event, t_gui *gui, bool *quit, t_game_engine *board, vector<t_cell *> *target);
void			control_selected(SDL_Event *event, t_gui *gui, bool *quit, t_game_engine *board, vector<t_cell *> *target);

void			create_file_entry(t_gui *gui, string *p_name);
void			create_save_button(t_gui *gui, t_game_engine *board, string *p_path);
void			create_load_button(t_gui *gui, t_game_engine *board, string *p_path);
void			create_generate_button(t_gui *gui, t_game_engine *board);
void			create_swap_button(t_gui *gui, vector<t_cell *> *target);

void			menu_map_generation(t_data data);
void			menu_save_map(t_data data);
void			menu_load_map(t_data data);

#endif
