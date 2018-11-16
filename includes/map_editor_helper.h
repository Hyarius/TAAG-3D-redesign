#ifndef MAP_EDITOR_HELPER_H
# define MAP_EDITOR_HELPER_H

#include "taag.h"

void			control_empty(SDL_Event *event, t_gui *gui, bool *quit, t_game_engine *board, t_cell **target);
void			control_selected(SDL_Event *event, t_gui *gui, bool *quit, t_game_engine *board, t_cell **target);

void			create_file_entry(t_gui *gui, string *p_name);
void			create_save_button(t_gui *gui, t_game_engine *board, string *p_path);
void			create_load_button(t_gui *gui, t_game_engine *board, string *p_path);
void			create_generate_button(t_gui *gui, t_game_engine *board);

#endif
