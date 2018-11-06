#ifndef TAAG_H
# define TAAG_H

#include "template.h"
#include "structure.h"
#include "base_value.h"

void			initiate_sprite();
void			initialize_spell();

void			menu_start();
void			menu_option(t_data data);
void			menu_play(t_data data);
void			menu_player_editor(t_data data);
void			menu_map_editor(t_data data);
void			menu_quit(t_data data);
void			menu_shop(t_data data);
void			menu_map_editor(t_data data);

t_actor			read_actor(t_data data);
void			save_actor(t_data data);

void			stand(t_data data);
void			quit(t_data data);

#endif
