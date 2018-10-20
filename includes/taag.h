#ifndef TAAG_H
# define TAAG_H

#include "template.h"

void		menu_start();
void		menu_option(t_data data);
void		menu_play(t_data data);
void		menu_player_editor(t_data data);
void		menu_map_editor(t_data data);
void		menu_quit(t_data data);
void		menu_shop(t_data data);
void		menu_map_editor(t_data data);

t_actor		read_actor(string p_name);
void		save_actor(t_actor *p_save, string p_file_name);

#endif
