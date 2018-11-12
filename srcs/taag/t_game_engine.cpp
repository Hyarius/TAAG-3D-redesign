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
	if (angle.z % 360 >= 0 && angle.z % 360 < 90)
	{
		iter_coord[0] = t_vect(0, 0);
		iter_coord[1] = t_vect(map_size.x, map_size.y);
		iter_coord[2] = t_vect(1, 1);
		iter_coord[3] = t_vect(iter_coord[0].x, iter_coord[0].y);
	}
	else if (angle.z % 360 >= 90 && angle.z % 360 < 180)
	{
		iter_coord[0] = t_vect(0, map_size.y - 1);
		iter_coord[1] = t_vect(map_size.x, -1);
		iter_coord[2] = t_vect(1, -1);
		iter_coord[3] = t_vect(iter_coord[0].x, iter_coord[0].y);
	}
	else if (angle.z % 360 >= 180 && angle.z % 360 < 270)
	{
		iter_coord[0] = t_vect(map_size.x - 1, map_size.y - 1);
		iter_coord[1] = t_vect(-1, -1);
		iter_coord[2] = t_vect(-1, -1);
		iter_coord[3] = t_vect(iter_coord[0].x, iter_coord[0].y);
	}
	else
	{
		iter_coord[0] = t_vect(map_size.x - 1, 0);
		iter_coord[1] = t_vect(-1, map_size.y);
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

void				s_game_engine::calc_cell(t_vect *coord, t_cell *cell, int coord_z)
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

int					s_game_engine::get_height_sprite(int x, int y, int z)
{
	int result;
	int delta;

	if (z == 0)
		delta = 0;
	else
		delta = 1;
	result = x + (this->nb_tile.x * (y + delta));
	if (result > this->nb_tile.x * this->nb_tile.y)
		return (0);
	return (result);
}

t_cell				*s_game_engine::get_cell(int i, int j)
{
	return (&(board.board[i][j]);
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
		coord = this->calc_cell(coord, cell, rel_height);
		sprite = cell->node->tile->get_height_sprite(cell->node->sprite_pos.x, cell->node->sprite_pos.y, cell->coord.z - rel_height);
		if (rel_height == cell->coord.z)
		{
			draw_wall(cell, cell->node->tile->get_height_sprite(cell->node->sprite_pos.x, cell->node->sprite_pos.y, cell->coord.z - (rel_height - 1)), coord);
			draw_uv_texture(cell->node->tile, sprite, coord[0], coord[1], coord[2], coord[3]);
		}
		else
			draw_wall(cell, cell->node->tile->get_height_sprite(cell->node->sprite_pos.x, cell->node->sprite_pos.y, cell->coord.z - (rel_height - 1)), coord);
		rel_height++;
	}
}
