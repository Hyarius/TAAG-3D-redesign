#include "taag.h"

s_stat::s_stat()
{
	this->hp = t_value();
	this->ini = t_value();
	this->pa = t_value();
	this->pm = t_value();
	this->phy = t_element();
	this->mag = t_element();
}

s_stat::s_stat(t_value p_hp, t_value p_pa, t_value p_pm, t_value p_ini, t_element p_phy, t_element p_mag)
{
	this->hp = p_hp;
	this->ini = p_ini;
	this->pa = p_pa;
	this->pm = p_pm;
	this->phy = p_phy;
	this->mag = p_mag;
}
