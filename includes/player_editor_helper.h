#ifndef PLAYER_EDITOR_HELPER_H
# define PLAYER_EDITOR_HELPER_H

#include "template.h"

void			set_b_value();

void			menu_save_actor(t_data data);
void			menu_load_actor(t_data data);

void			create_file_entry(t_gui *gui, string *p_name, double p_line);
void			create_entry_name(t_gui *gui, t_actor *player, double p_line);
void			create_level_iterator(t_gui *gui, t_actor *player, double p_line);
void			create_health_iterator(t_gui *gui, t_actor *player, double p_line);
void			create_pa_iterator(t_gui *gui, t_actor *player, double p_line);
void			create_pm_iterator(t_gui *gui, t_actor *player, double p_line);
void			create_init_iterator(t_gui *gui, t_actor *player, double p_line);
void			create_atk_phy_iterator(t_gui *gui, t_actor *player, double p_line);
void			create_atk_mag_iterator(t_gui *gui, t_actor *player, double p_line);
void			create_def_phy_iterator(t_gui *gui, t_actor *player, double p_line);
void			create_def_mag_iterator(t_gui *gui, t_actor *player, double p_line);
void			create_pool_iterator(t_gui *gui, t_actor *player, double p_line);
void			create_save_button(t_gui *gui, t_actor *player, double p_line, string *p_path);
void			create_load_button(t_gui *gui, t_actor *player, double p_line, string *p_path);

void			create_spell_cards(t_gui *gui, t_actor *player);
#endif
