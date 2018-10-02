#ifndef STRUCTURE_H
# define STRUCTURE_H

using namespace std;

typedef struct		s_thread_data
{
	void			*data0;
	void			*data1;
	void			*data2;
	void			*data3;
}					t_thread_data;

typedef struct		s_node
{
	string			name;
	class tileset	*tile;
	t_vect			sprite_pos;
	int				cost;
					s_node(string path);
}					t_node;

typedef struct		s_cursor
{
	int				cursor_sprite;
	t_vect			coord;
	t_vect			*get_coord();
	void			set_coord(int p_x, int p_y);
	void			modify_coord(int p_x, int p_y);
}					t_cursor;

typedef struct		s_cell
{
	t_vertex		coord;
	t_node			*node;
	class actor		*p_actor;
	int				cursor_sprite;
	int				dist;
	int				range;
					s_cell(int x, int y, int z, t_node *p_node);
}					t_cell;

#endif
