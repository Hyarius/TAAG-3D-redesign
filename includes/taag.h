#ifndef TAAG_H
# define TAAG_H

#include "template.h"

void			menu_start();
void			menu_option(t_data data);
void			menu_play(t_data data);
void			menu_player_editor(t_data data);
void			menu_map_editor(t_data data);
void			menu_quit(t_data data);
void			menu_shop(t_data data);
void			menu_map_editor(t_data data);
void			menu_save_actor(t_data data);

t_actor			read_actor(t_data data);
void			save_actor(t_data data);

void			create_entry_name(t_gui *gui, t_actor *player, int p_line);
void			create_level_iterator(t_gui *gui, t_actor *player, int p_line);
void			create_health_iterator(t_gui *gui, t_actor *player, int p_line);
void			create_pa_iterator(t_gui *gui, t_actor *player, int p_line);
void			create_pm_iterator(t_gui *gui, t_actor *player, int p_line);
void			create_init_iterator(t_gui *gui, t_actor *player, int p_line);
void			create_atk_phy_iterator(t_gui *gui, t_actor *player, int p_line);
void			create_atk_mag_iterator(t_gui *gui, t_actor *player, int p_line);
void			create_def_phy_iterator(t_gui *gui, t_actor *player, int p_line);
void			create_def_mag_iterator(t_gui *gui, t_actor *player, int p_line);
void			create_pool_iterator(t_gui *gui, t_actor *player, int p_line);
void			create_save_button(t_gui *gui, t_actor *player, int p_line, string *p_path);


void			stand(t_data data);
void			quit(t_data data);

#endif
