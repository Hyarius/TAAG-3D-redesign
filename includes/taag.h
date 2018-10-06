#ifndef TAAG_H
# define TAAG_H

#include "template.h"
#include "class.h"

void		menu_start(void *value);
void		play(void *value);
void		menu_player_editor(void *value);
void		menu_spell_editor(void *value);
void		menu_map_editor(void *value);
void		menu_shop(void *value);
void		menu_option(void *value);
void		menu_quit(void *value);
void		menu_quit();

actor		read_actor(string name);
void		save_actor(actor *to_save);

#endif
