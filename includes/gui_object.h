#ifndef GUI_OBJECT_H
# define GUI_OBJECT_H

# include "template_gui_structure.h"

#include "actor.h"
#include "spell.h"

using namespace std;

typedef struct		s_iterator : t_gui_obj
{
	t_button_comp	*button[4]; //0 - description | 1 - button minus | 2 - value | 3 - button plus
	string			text_value;
	int				*value;
	int				*pool;
	int				cost;
	int				delta;
	int				min;
	int				max;

					s_iterator(	t_button_comp *p_button0,
								t_button_comp *p_button1,
								t_button_comp *p_button2,
								t_button_comp *p_button3,
								int *p_value, int p_delta, int p_min, int p_max,
								int	*p_pool, int p_cost, int *p_level);
	void			set_text_value();
	void			draw_self();
	void			click(t_vect mouse);
}					t_iterator;

typedef struct		s_sprite_selector : t_gui_obj
{
	t_button_comp	*button[4]; //0 - description | 1 - button image
	t_vect			*sprite_selected;
	t_vect			increment;
	int				*index;

					s_sprite_selector(	t_button_comp *p_button1, t_button_comp *p_button2,
										t_button_comp *p_button3, t_button_comp *p_button4,
										int *p_index, t_vect *p_selected, t_vect p_increment, t_gui *gui);
	void			draw_self();
	void			click(t_vect mouse);
	void			reset_actor(struct s_actor *actor);
}					t_sprite_selector;

typedef struct		s_node_selector : t_gui_obj
{
	t_button_comp	*button[4]; //0 - description | 1 - button image
	int				*index;

					s_node_selector(t_button_comp *p_button1, t_button_comp *p_button2,
									t_button_comp *p_button3, t_button_comp *p_button4, int *p_index, t_gui *gui);
	void			draw_self();
	void			click(t_vect mouse);
}					t_node_selector;

typedef struct		s_spell_card : t_gui_obj
{
	t_button_comp	*button[4]; //0 - background | 1 - image | 2 - name
	t_spell			*spell;//spell of the card
	int				desc_size;

					s_spell_card();
					s_spell_card(t_spell *p_spell, t_vect coord, t_vect size, gui_funct p_funct, t_data p_data);
	void			set_desc_size();
	void			draw_self();
	void			click(t_vect mouse);
	void			verify();
}					t_spell_card;

typedef struct		s_game_object_card : t_gui_obj
{
	t_button		*mini;
	bool			minimized;
	t_button		*back;
	t_tileset_button
					*sprite;
	t_button		*name;
	t_iterator		*hp;
	t_button		*create;
	t_button		*choose;
	t_button		*place;
	t_button		*erase;
					s_game_object_card();
					s_game_object_card(t_button *p_mini, t_button *p_back, t_tileset_button *p_sprite, t_button *p_name,
							t_iterator *p_hp, t_button *p_create, t_button *p_choose, t_button *p_place, t_button *p_erase);
	void			draw_self();
	void			click(t_vect mouse);
}					t_game_object_card;

#endif
