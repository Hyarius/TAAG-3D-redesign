#ifndef STRUCTURE_H
# define STRUCTURE_H

using namespace std;

#include "gui_object.h"

typedef struct		s_node
{
	string			name;
	int				cost;

	int				index;
	t_vect			pos;

					s_node(string p_path);
}					t_node;

typedef struct		s_cell
{
	t_vertex		coord;
	t_vect			cursor;
	t_node			*node;
	t_actor			*actor;
					s_cell();
					s_cell(t_vertex p_coord, t_node *p_node, t_actor *p_actor);
}					t_cell;

typedef struct		s_game_board
{
	vector<vector<s_cell>>	board;
	t_vertex		map_size;
					s_game_board();
					s_game_board(string p_path);
}					t_game_board;

typedef struct		s_camera
{
	t_vertex		angle;
	t_vertex		axe_x;
	t_vertex		axe_y;
	t_vertex		axe_z;
	t_vect			offset;
	t_vect			target;
	t_vertex		sprite_unit;
	double			zoom;
					s_camera();
					s_camera(int angle_x, int angle_y, int angle_z);
	void 			calc_axe();
	void			handle_rot(double delta);
	void			handle_vertical_rot(double delta);
	void			handle_zoom(double modif);
	void			handle_move(int motion_x, int motion_y);
	t_vect			coord_to_vect(double x, double y, double z);
	t_vect			coord_to_vect(int x, int y, int z);
	t_vect			vertex_to_vect(t_vertex source);
}					t_camera;

typedef struct		s_game_engine
{
	t_camera		*camera;
	t_game_board	*board;
	t_vect			iter_coord[4];
	int				i_index[8];
	t_vect			next_cell_left;
	t_vect			next_cell_right;
					s_game_engine();
					s_game_engine(string p_path);
	void			calc_camera();
	void			handle_rot(double modif);
	void			handle_vertical_rot(double modif);
	void			draw_board();
	void			draw_mouse_cursor(int i, int j);
	void			draw_cell(int i, int j);
	void			calc_cell(t_vect *coord, t_cell *cell, double coord_z);
	int				get_height_sprite(int index, int x, int y, int z);
	t_cell			*get_cell(int i, int j);
	int				test_cell(t_vect mouse, int x, int y, int z);
	t_vect			mouse_to_vect();
}					t_game_engine;

#endif
