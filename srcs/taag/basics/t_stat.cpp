#include "taag.h"

s_stat::s_stat()
{
	this->hp = t_value(g_hp[1]);
	this->ini = t_value(g_init[1]);
	this->pa = t_value(g_pa[1]);
	this->pm = t_value(g_pm[1]);
	this->phy = t_element(g_atk_phy[1], g_def_phy[1]);
	this->mag = t_element(g_atk_mag[1], g_def_mag[1]);
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
