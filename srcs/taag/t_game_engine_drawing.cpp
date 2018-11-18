#include "taag.h"

int				test = 0;

void				s_game_engine::draw_board()
{
	t_vect				coord[8];
	t_vect	mouse = mouse_to_vect();

	calc_cell(coord);
	while (iter_coord[0].x != iter_coord[1].x)
	{
		iter_coord[0].y = iter_coord[3].y;
		while (iter_coord[0].y != iter_coord[1].y)
		{
			draw_cell(iter_coord[0].x, iter_coord[0].y, coord);
			if (iter_coord[0].x == mouse.x && iter_coord[0].y == mouse.y)
				draw_mouse_cursor(iter_coord[0].x, iter_coord[0].y, coord);
			iter_coord[0].y += iter_coord[2].y;
		}
		iter_coord[0].x += iter_coord[2].x;
	}
	iter_coord[0] = iter_coord[3];
}

void				s_game_engine::calc_cell(t_vect *coord)
{
	coord[0] = camera->vertex_to_vect(t_vertex(0.0, 0.0, 0.0));
	coord[1] = camera->vertex_to_vect(t_vertex(1.0, 0.0, 0.0));
	coord[2] = camera->vertex_to_vect(t_vertex(0.0, 1.0, 0.0));
	coord[3] = camera->vertex_to_vect(t_vertex(1.0, 1.0, 0.0));
	coord[4] = camera->vertex_to_vect(t_vertex(0.0, 0.0, 1.0));
	coord[5] = camera->vertex_to_vect(t_vertex(1.0, 0.0, 1.0));
	coord[6] = camera->vertex_to_vect(t_vertex(0.0, 1.0, 1.0));
	coord[7] = camera->vertex_to_vect(t_vertex(1.0, 1.0, 1.0));
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

void				s_game_engine::draw_cell(int i, int j, t_vect *coord)
{
	t_cell				*cell;
	t_vect				modif;
	double				rel_height;
	int					sprite;
	bool				left = true;
	bool				right = true;

	cell = get_cell(i, j);
	if (cell == NULL || cell->node == NULL || cell->node->index == -1)
		return ;
	rel_height = cell->coord.z;
	if (get_cell(i + next_cell_right.x, j + next_cell_right.y) != NULL && get_cell(i + next_cell_right.x, j + next_cell_right.y)->coord.z >= cell->coord.z)
		right = false;
	if (get_cell(i + next_cell_left.x, j + next_cell_left.y) != NULL && get_cell(i + next_cell_left.x, j + next_cell_left.y)->coord.z >= cell->coord.z)
		left = false;
	while (rel_height >= 0)
	{
		sprite = get_height_sprite(cell->node->index, cell->node->pos.x, cell->node->pos.y, rel_height);
		modif = t_vect(camera->axe_x.x * i - camera->axe_y.x * j, camera->axe_x.y * i - camera->axe_y.y * j + camera->axe_z.y * (cell->coord.z - rel_height));
		if (right == true)
			texture_list[cell->node->index]->draw_self(	coord[i_index[0]] + modif + t_vect(0, 2), coord[i_index[1]] + modif + t_vect(0, 2), coord[i_index[2]] + modif, coord[i_index[3]] + modif, sprite, 1.0);
		if (left == true)
			texture_list[cell->node->index]->draw_self(	coord[i_index[4]] + modif + t_vect(0, 2), coord[i_index[5]] + modif + t_vect(0, 2), coord[i_index[6]] + modif, coord[i_index[7]] + modif, sprite, 1.0);
		rel_height--;
	}
	modif = t_vect(camera->axe_x.x * i - camera->axe_y.x * j, camera->axe_x.y * i - camera->axe_y.y * j + camera->axe_z.y * (cell->coord.z - rel_height));
	if (test == 0)
		texture_list[cell->node->index]->draw_self(		coord[0] + modif, coord[1] + modif, coord[2] + modif, coord[3] + modif, cell->node->pos, 1.0);
	if (cell->cursor != t_vect(0, 0))
		texture_list[0]->draw_self(coord[0] + modif, coord[1] + modif, coord[2] + modif, coord[3] + modif, cell->cursor, 1.0);
}

void				s_game_engine::draw_mouse_cursor(int i, int j, t_vect *coord)
{
	t_cell				*cell;
	t_vect				modif;

	cell = get_cell(i, j);
	if (cell == NULL || cell->node == NULL || cell->node->index == -1)
		return ;
	modif = t_vect(camera->axe_x.x * i - camera->axe_y.x * j, camera->axe_x.y * i - camera->axe_y.y * j + camera->axe_z.y * (cell->coord.z + 1));
	texture_list[0]->draw_self(coord[0] + modif, coord[1] + modif, coord[2] + modif, coord[3] + modif, t_vect(0, 1), 1.0);

}
