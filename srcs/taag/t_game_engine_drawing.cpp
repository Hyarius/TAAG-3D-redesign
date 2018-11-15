#include "taag.h"

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

	if (z < 2)
		delta = 1;
	else
		delta = 2;
	result = x + (texture_list[index]->nb_sprite.x * (y + delta));
	if (result > texture_list[index]->nb_sprite.x * texture_list[index]->nb_sprite.y)
		return (0);
	return (result);
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
		texture_list[cell->node->index]->draw_self(coord[i_index[0]], coord[i_index[1]],
													coord[i_index[2]], coord[i_index[3]],
													sprite, 1.0);
		texture_list[cell->node->index]->draw_self(coord[i_index[4]], coord[i_index[5]],
													coord[i_index[6]], coord[i_index[7]],
													sprite, 1.0);
		if (rel_height == cell->coord.z)
		texture_list[cell->node->index]->draw_self(coord[0], coord[1], coord[2], coord[3], cell->node->pos, 1.0);
		rel_height++;
	}
}
