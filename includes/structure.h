#ifndef STRUCTURE_H
# define STRUCTURE_H

using namespace std;

typedef struct	s_value
{
	int			cur;
	int			max;
				s_value();
				s_value(int p_max);
				s_value(int p_cur, int p_max);
void			operator = (int p_value);
}				t_value;

typedef struct	s_element
{
	int			atk;
	int			def;
	s_element();
	s_element(int p_atk, int p_def);
}				t_element;

typedef struct	s_stat
{
	t_value		hp;
	t_value		ini;
	t_value		pa;
	t_value		pm;
	t_element	phy;
	t_element	mag;
				s_stat();
				s_stat(t_value p_hp, t_value p_pa, t_value p_pm, t_value p_ini, t_element p_phy, t_element p_mag);
}				t_stat;

typedef struct	s_actor
{
	string		name;
	int			level;
	int			attrib_point;
	t_stat		stat;
				s_actor();
				s_actor(string p_name, int p_level, int p_pool, t_stat p_stat);
}				t_actor;

#endif
