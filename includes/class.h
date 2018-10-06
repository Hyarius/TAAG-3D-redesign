#ifndef CLASS_H
# define CLASS_H

class actor
{
private:
	string	name;
	t_stat	stat;
	int		sprite;
public:
	actor();
	actor(string p_name, t_stat p_stat, int p_sprite);
	void		set_name(string p_name);
	string		get_name();
	t_stat		*get_stat();
	int			*get_sprite();
};

class game_engine
{
private:
public:
	game_engine();
};

#endif
