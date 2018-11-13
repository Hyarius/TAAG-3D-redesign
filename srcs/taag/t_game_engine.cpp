#include "taag.h"


					s_game_engine::s_game_engine()
{
	board = NULL;
	camera = NULL;
}

					s_game_engine::s_game_engine(string p_path)
{
	board = new s_game_board(p_path);
	camera = new s_camera(60, 0, 45);
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
	}
	else if ((int)(camera->angle.z) % 360 >= 90 && (int)(camera->angle.z) % 360 < 180)
	{
		iter_coord[0] = t_vect(0, board->size.y - 1);
		iter_coord[1] = t_vect(board->size.x, -1);
		iter_coord[2] = t_vect(1, -1);
		iter_coord[3] = t_vect(iter_coord[0].x, iter_coord[0].y);
	}
	else if ((int)(camera->angle.z) % 360 >= 180 && (int)(camera->angle.z) % 360 < 270)
	{
		iter_coord[0] = t_vect(board->size.x - 1, board->size.y - 1);
		iter_coord[1] = t_vect(-1, -1);
		iter_coord[2] = t_vect(-1, -1);
		iter_coord[3] = t_vect(iter_coord[0].x, iter_coord[0].y);
	}
	else
	{
		iter_coord[0] = t_vect(board->size.x - 1, 0);
		iter_coord[1] = t_vect(-1, board->size.y);
		iter_coord[2] = t_vect(-1, 1);
		iter_coord[3] = t_vect(iter_coord[0].x, iter_coord[0].y);
	}
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
	coord[1] = camera->vertex_to_vect(t_vertex(cell->coord.x + 1, cell->coord.y, coord_z));
	coord[2] = camera->vertex_to_vect(t_vertex(cell->coord.x, cell->coord.y + 1, coord_z));
	coord[3] = camera->vertex_to_vect(t_vertex(cell->coord.x + 1, cell->coord.y + 1, coord_z));
	coord[4] = camera->vertex_to_vect(t_vertex(cell->coord.x, cell->coord.y, coord_z - 1));
	coord[5] = camera->vertex_to_vect(t_vertex(cell->coord.x + 1, cell->coord.y, coord_z - 1));
	coord[6] = camera->vertex_to_vect(t_vertex(cell->coord.x, cell->coord.y + 1, coord_z - 1));
	coord[7] = camera->vertex_to_vect(t_vertex(cell->coord.x + 1, cell->coord.y + 1, coord_z - 1));
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
		calc_cell(coord, cell, rel_height);
		sprite = get_height_sprite(cell->node->index, cell->node->pos.x, cell->node->pos.y, cell->coord.z - rel_height);
		if (rel_height == cell->coord.z)
		{
			printf("print de la surface\n");
		}
		else
		{
			printf("print d'un mur\n");
		}
		rel_height++;
	}
}
