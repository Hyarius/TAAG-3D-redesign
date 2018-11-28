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
	this->choose = NULL;
	this->place = NULL;
	this->erase = NULL;
}

s_game_object_card::s_game_object_card(t_button *p_mini, t_button *p_back, t_tileset_button *p_sprite, t_button *p_name,
		t_iterator *p_hp, t_button *p_create, t_button *p_choose, t_button *p_place, t_button *p_erase)
{
	this->mini = p_mini;
	if (this->mini != NULL)
		this->mini->button->set_funct_param(change_bool, t_data(1, &(this->minimized)));
	this->minimized = false;
	this->sprite = p_sprite;
	this->back = p_back;
	this->name = p_name;
	this->hp = p_hp;
	this->create = p_create;
	this->choose = p_choose;
	this->place = p_place;
	this->erase = p_erase;
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
		if (this->create != NULL)
			this->create->draw_self();
		if (this->choose != NULL)
			this->choose->draw_self();
		if (this->place != NULL)
			this->place->draw_self();
		if (this->erase != NULL)
			this->erase->draw_self();
	}
	else
	{
		if (this->mini != NULL)
			this->mini->draw_self();
	}

}

void			s_game_object_card::click(t_vect mouse)
{
	if (minimized == false)
	{
		if (this->create != NULL)
			this->create->click(mouse);
		if (this->choose != NULL)
			this->choose->click(mouse);
		if (this->place != NULL)
			this->place->click(mouse);
		if (this->erase != NULL)
			this->erase->click(mouse);
	}
	if (this->mini != NULL)
		this->mini->click(mouse);
}
