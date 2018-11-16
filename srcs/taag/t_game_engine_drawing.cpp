#include "taag.h"

void				s_game_engine::draw_board()
{
	t_vect	mouse = mouse_to_vect();

	while (iter_coord[0].x != iter_coord[1].x)
	{
		iter_coord[0].y = iter_coord[3].y;
		while (iter_coord[0].y != iter_coord[1].y)
		{
			draw_cell(iter_coord[0].x, iter_coord[0].y);
			if (iter_coord[0].x == mouse.x && iter_coord[0].y == mouse.y)
				draw_mouse_cursor(iter_coord[0].x, iter_coord[0].y);
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
	double				rel_height;
	int					sprite;

	cell = get_cell(i, j);
	if (cell == NULL || cell->node == NULL || cell->node->index == -1)
		return ;
	rel_height = 0;
	calc_cell(coord, cell, cell->coord.z);
	while (rel_height <= cell->coord.z)
	{
		sprite = get_height_sprite(cell->node->index, cell->node->pos.x, cell->node->pos.y, cell->coord.z - rel_height);
		if (get_cell(i + next_cell_right.x, j + next_cell_right.y) == NULL || get_cell(i + next_cell_right.x, j + next_cell_right.y)->coord.z < cell->coord.z)
			texture_list[cell->node->index]->draw_self(	coord[i_index[0]] + t_vect(0, camera->axe_z.y * (rel_height - cell->coord.z) - 1), coord[i_index[1]] + t_vect(0, camera->axe_z.y * (rel_height - cell->coord.z) - 1),
														coord[i_index[2]] + t_vect(0, camera->axe_z.y * (rel_height - cell->coord.z)), coord[i_index[3]] + t_vect(0, camera->axe_z.y * (rel_height - cell->coord.z)), sprite, 1.0);
		if (get_cell(i + next_cell_left.x, j + next_cell_left.y) == NULL || get_cell(i + next_cell_left.x, j + next_cell_left.y)->coord.z < cell->coord.z)
			texture_list[cell->node->index]->draw_self(	coord[i_index[4]] + t_vect(0, camera->axe_z.y * (rel_height - cell->coord.z) - 1), coord[i_index[5]] + t_vect(0, camera->axe_z.y * (rel_height - cell->coord.z) - 1),
														coord[i_index[6]] + t_vect(0, camera->axe_z.y * (rel_height - cell->coord.z)), coord[i_index[7]] + t_vect(0, camera->axe_z.y * (rel_height - cell->coord.z)), sprite, 1.0);
		if (rel_height == cell->coord.z)
		{
			texture_list[cell->node->index]->draw_self(coord[0], coord[1], coord[2], coord[3], cell->node->pos, 1.0);
			if (cell->cursor.x != 0 && cell->cursor.y != 0)
				texture_list[0]->draw_self(coord[0], coord[1], coord[2], coord[3], cell->cursor, 1.0);
		}
		rel_height++;
	}
}

void				s_game_engine::draw_mouse_cursor(int i, int j)
{
	t_cell				*cell;
	t_vect				coord[8];

	cell = get_cell(i, j);
	if (cell == NULL || cell->node == NULL || cell->node->index == -1)
		return ;
	calc_cell(coord, cell, cell->coord.z);
	texture_list[0]->draw_self(coord[0], coord[1], coord[2], coord[3], t_vect(0, 1), 1.0);

}
