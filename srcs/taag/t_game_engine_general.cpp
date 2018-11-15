#include "taag.h"

static void			set_index_value(int *index, int a, int b, int c, int d, int e, int f, int g, int h)
{
	index[0] = a;
	index[1] = b;
	index[2] = c;
	index[3] = d;
	index[4] = e;
	index[5] = f;
	index[6] = g;
	index[7] = h;
}

					s_game_engine::s_game_engine()
{
	board = NULL;
	camera = NULL;
}

					s_game_engine::s_game_engine(string p_path)
{
	board = new s_game_board(p_path);
	camera = new s_camera(60, 0, 270);
	camera->target = t_vect(board->size.x / 2.0, board->size.y / 2.0);
	calc_camera();
}

void					s_game_engine::calc_camera()
{
	if ((int)(camera->angle.z) % 360 >= 0 && (int)(camera->angle.z) % 360 < 90)
	{
		iter_coord[0] = t_vect(0, 0);
		iter_coord[1] = t_vect(board->size.x, board->size.y);
		iter_coord[2] = t_vect(1, 1);
		iter_coord[3] = t_vect(iter_coord[0].x, iter_coord[0].y);
		set_index_value(i_index, 2, 3, 6, 7, 3, 1, 7, 5);
		next_cell_left = t_vect(1, 0);
		next_cell_right = t_vect(0, 1);
	}
	else if ((int)(camera->angle.z) % 360 >= 90 && (int)(camera->angle.z) % 360 < 180)
	{
		iter_coord[0] = t_vect(0, board->size.y - 1);
		iter_coord[1] = t_vect(board->size.x, -1);
		iter_coord[2] = t_vect(1, -1);
		iter_coord[3] = t_vect(iter_coord[0].x, iter_coord[0].y);
		set_index_value(i_index, 3, 1, 7, 5, 0, 1, 4, 5);
		next_cell_left = t_vect(0, -1);
		next_cell_right = t_vect(1, 0);
	}
	else if ((int)(camera->angle.z) % 360 >= 180 && (int)(camera->angle.z) % 360 < 270)
	{
		iter_coord[0] = t_vect(board->size.x - 1, board->size.y - 1);
		iter_coord[1] = t_vect(-1, -1);
		iter_coord[2] = t_vect(-1, -1);
		iter_coord[3] = t_vect(iter_coord[0].x, iter_coord[0].y);
		set_index_value(i_index, 0, 1, 4, 5, 0, 2, 4, 6);
		next_cell_left = t_vect(-1, 0);
		next_cell_right = t_vect(0, -1);
	}
	else
	{
		iter_coord[0] = t_vect(board->size.x - 1, 0);
		iter_coord[1] = t_vect(-1, board->size.y);
		iter_coord[2] = t_vect(-1, 1);
		iter_coord[3] = t_vect(iter_coord[0].x, iter_coord[0].y);
		set_index_value(i_index, 0, 2, 4, 6, 2, 3, 6, 7);
		next_cell_left = t_vect(0, 1);
		next_cell_right = t_vect(-1, 0);
	}
}

void				s_game_engine::handle_rot(double modif)
{
	camera->handle_rot(modif);
	calc_camera();
}

t_cell				*s_game_engine::get_cell(int i, int j)
{
	if (i < 0 || j < 0 || i >= board->size.x || j >= board->size.y)
		return (NULL);
	return (&(board->board[i][j]));
}

int					s_game_engine::test_cell(t_vect mouse, int x, int y, int z)
{

	return (1);
}

t_vect				s_game_engine::mouse_to_vect()
{
	t_vect		mouse = get_mouse_coord();

	t_vect		coord[4];

	for (int i = 0; i < 4;i++)
		coord[i] = iter_coord[i];

	while (coord[0].x != coord[1].x)
	{
		coord[0].y = coord[3].y;
		while (coord[0].y != coord[1].y)
		{
			printf("coord = [%.2f] / [%.2f]\n", coord[0].x, coord[0].y);
			coord[0].y += coord[2].y;
		}
		coord[0].x += coord[2].x;
	}
	return (mouse);
}