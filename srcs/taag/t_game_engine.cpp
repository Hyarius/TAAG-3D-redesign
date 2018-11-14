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
		set_index_value(_index, 2, 3, 6, 7, 3, 1, 7, 5);
	}
	else if ((int)(camera->angle.z) % 360 >= 90 && (int)(camera->angle.z) % 360 < 180)
	{
		iter_coord[0] = t_vect(0, board->size.y - 1);
		iter_coord[1] = t_vect(board->size.x, -1);
		iter_coord[2] = t_vect(1, -1);
		iter_coord[3] = t_vect(iter_coord[0].x, iter_coord[0].y);
		set_index_value(_index, 3, 1, 7, 5, 0, 1, 4, 5);
	}
	else if ((int)(camera->angle.z) % 360 >= 180 && (int)(camera->angle.z) % 360 < 270)
	{
		iter_coord[0] = t_vect(board->size.x - 1, board->size.y - 1);
		iter_coord[1] = t_vect(-1, -1);
		iter_coord[2] = t_vect(-1, -1);
		iter_coord[3] = t_vect(iter_coord[0].x, iter_coord[0].y);
		set_index_value(_index, 0, 1, 4, 5, 0, 2, 4, 6);
	}
	else
	{
		iter_coord[0] = t_vect(board->size.x - 1, 0);
		iter_coord[1] = t_vect(-1, board->size.y);
		iter_coord[2] = t_vect(-1, 1);
		iter_coord[3] = t_vect(iter_coord[0].x, iter_coord[0].y);
		set_index_value(_index, 0, 2, 4, 6, 2, 3, 6, 7);
	}
}

void				s_game_engine::handle_rot(double modif)
{
	camera->handle_rot(modif);
	calc_camera();
}

void				s_game_engine::draw_board()
{
	while (iter_coord[0].x != iter_coord[1].x)
	{
		iter_coord[0].y = iter_coord[3].y;
		while (iter_coord[0].y != iter_coord[1].y)
		{
			if (board->board[iter_coord[0].x][iter_coord[0].y].node != NULL)
				draw_cell(iter_coord[0].x, iter_coord[0].y);
			iter_coord[0].y += iter_coord[2].y;
		}
		iter_coord[0].x += iter_coord[2].x;
	}
	iter_coord[0] = iter_coord[3];
}

void				s_game_engine::calc_cell(t_vect *coord, t_cell *cell, double coord_z)
{
	coord[0] = camera->vertex_to_vect(t_vertex(cell->coord.x, cell->coord.y, coord_z));
	coord[1] = camera->vertex_to_vect(t_vertex(cell->coord.x + 1.0, cell->coord.y, coord_z));
	coord[2] = camera->vertex_to_vect(t_vertex(cell->coord.x, cell->coord.y + 1.0, coord_z));
	coord[3] = camera->vertex_to_vect(t_vertex(cell->coord.x + 1.0, cell->coord.y + 1.0, coord_z));
	coord[4] = camera->vertex_to_vect(t_vertex(cell->coord.x, cell->coord.y, coord_z - 1.0));
	coord[5] = camera->vertex_to_vect(t_vertex(cell->coord.x + 1.0, cell->coord.y, coord_z - 1.0));
	coord[6] = camera->vertex_to_vect(t_vertex(cell->coord.x, cell->coord.y + 1.0, coord_z - 1.0));
	coord[7] = camera->vertex_to_vect(t_vertex(cell->coord.x + 1.0, cell->coord.y + 1.0, coord_z - 1.0));
}

int					s_game_engine::get_height_sprite(int index, int x, int y, int z)
{
	int result;
	int delta;

	if (z == 0)
		delta = 0;
	else
		delta = 1;
	result = x + (texture_list[index]->nb_sprite.x * (y + delta));
	if (result > texture_list[index]->nb_sprite.x * texture_list[index]->nb_sprite.y)
		return (0);
	return (result);
}

t_cell				*s_game_engine::get_cell(int i, int j)
{
	return (&(board->board[i][j]));
}

void				s_game_engine::draw_cell(int i, int j)
{
	t_cell				*cell;
	t_vect				coord[8];
	int					rel_height;
	int					sprite;

	cell = get_cell(i, j);
	if (cell == NULL || cell->node == NULL || cell->node->index == -1)
		return ;
	rel_height = 0;
	while (rel_height <= cell->coord.z)
	{
		calc_cell(coord, cell, rel_height + 1);
		sprite = get_height_sprite(cell->node->index, cell->node->pos.x, cell->node->pos.y, cell->coord.z - rel_height);
		draw_rectangle(coord[_index[0]], coord[_index[1]], coord[_index[2]], coord[_index[3]], color[(i % 3) + (j % 3)]);
		draw_rectangle(coord[_index[4]], coord[_index[5]], coord[_index[6]], coord[_index[7]], color[(i % 3) + (j % 3)]);
		if (rel_height == cell->coord.z)
			draw_rectangle(coord[0], coord[1], coord[2], coord[3], color[(i % 3) + (j % 3)]);
		rel_height++;
	}
}
