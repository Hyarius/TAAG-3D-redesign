#ifndef CLASS_H
# define CLASS_H

class player
{
private:
	t_stat	stat;
	int		sprite;
public:
	player();
	player(t_stat p_stat, int p_sprite);
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
