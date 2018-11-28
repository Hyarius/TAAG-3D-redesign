#include "taag.h"

static void			change_bool(t_data data)
{
	bool *value = ((bool *)(data.data[0]));

	if (*value == true)
		*value = false;
	else
		*value = true;
}

s_game_object_card::s_game_object_card()
{
	this->mini = NULL;
	this->minimized = true;
	this->back = NULL;
	this->sprite = NULL;
	this->name = NULL;
	this->hp = NULL;
	this->pa = NULL;
	this->pm = NULL;
	this->atk_phy = NULL;
	this->def_phy = NULL;
	this->atk_mag = NULL;
	this->def_mag = NULL;
	this->choose = NULL;
	this->place = NULL;
}

s_game_object_card::s_game_object_card(t_button *p_mini, t_button *p_back, t_tileset_button *p_sprite, t_button *p_name,
		t_iterator *p_hp, t_iterator *p_pa, t_iterator *p_pm,
		t_iterator *p_atk_phy, t_iterator *p_def_phy, t_iterator *p_atk_mag, t_iterator *p_def_mag,
		t_button *p_choose, t_button *p_place)
{
	this->mini = p_mini;
	if (this->mini != NULL)
		this->mini->button->set_funct_param(change_bool, t_data(1, &(this->minimized)));
	this->minimized = false;
	this->sprite = p_sprite;
	this->back = p_back;
	this->name = p_name;
	this->hp = p_hp;
	this->pa = p_pa;
	this->pm = p_pm;
	this->atk_phy = p_atk_phy;
	this->def_phy = p_def_phy;
	this->atk_mag = p_atk_mag;
	this->def_mag = p_def_mag;
	this->choose = p_choose;
	this->place = p_place;
}

void			s_game_object_card::draw_self()
{
	if (minimized == false)
	{
		if (this->back != NULL)
			this->back->draw_self();
		if (this->mini != NULL)
			this->mini->draw_self();
		if (this->sprite != NULL)
			this->sprite->draw_self();
		if (this->name != NULL)
			this->name->draw_self();
		if (this->hp != NULL)
			this->hp->draw_self();
		if (this->pa != NULL)
			this->pa->draw_self();
		if (this->pm != NULL)
			this->pm->draw_self();
		if (this->atk_phy != NULL)
			this->atk_phy->draw_self();
		if (this->def_phy != NULL)
			this->def_phy->draw_self();
		if (this->atk_mag != NULL)
			this->atk_mag->draw_self();
		if (this->def_mag != NULL)
			this->def_mag->draw_self();
		if (this->choose != NULL)
			this->choose->draw_self();
		if (this->place != NULL)
			this->place->draw_self();
	}
	else
	{
		if (this->mini != NULL)
			this->mini->draw_self();
	}

}

void			s_game_object_card::click(t_vect mouse)
{
	if (this->mini != NULL)
		this->mini->click(mouse);
}
