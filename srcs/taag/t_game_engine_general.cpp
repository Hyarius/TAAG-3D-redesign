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
	camera = new s_camera(60, 0, 45);
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
	}
	else if ((int)(camera->angle.z) % 360 >= 90 && (int)(camera->angle.z) % 360 < 180)
	{
		iter_coord[0] = t_vect(0, board->size.y - 1);
		iter_coord[1] = t_vect(board->size.x, -1);
		iter_coord[2] = t_vect(1, -1);
		iter_coord[3] = t_vect(iter_coord[0].x, iter_coord[0].y);
		set_index_value(i_index, 3, 1, 7, 5, 0, 1, 4, 5);
	}
	else if ((int)(camera->angle.z) % 360 >= 180 && (int)(camera->angle.z) % 360 < 270)
	{
		iter_coord[0] = t_vect(board->size.x - 1, board->size.y - 1);
		iter_coord[1] = t_vect(-1, -1);
		iter_coord[2] = t_vect(-1, -1);
		iter_coord[3] = t_vect(iter_coord[0].x, iter_coord[0].y);
		set_index_value(i_index, 0, 1, 4, 5, 0, 2, 4, 6);
	}
	else
	{
		iter_coord[0] = t_vect(board->size.x - 1, 0);
		iter_coord[1] = t_vect(-1, board->size.y);
		iter_coord[2] = t_vect(-1, 1);
		iter_coord[3] = t_vect(iter_coord[0].x, iter_coord[0].y);
		set_index_value(i_index, 0, 2, 4, 6, 2, 3, 6, 7);
	}
}

void				s_game_engine::handle_rot(double modif)
{
	camera->handle_rot(modif);
	calc_camera();
}

t_cell				*s_game_engine::get_cell(int i, int j)
{
	return (&(board->board[i][j]));
}
