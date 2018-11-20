#include "taag.h"

int			test = 0;

void				s_game_engine::draw_board()
{
	int			index = -1;
	t_vect		previous_coord;
	t_vect		mouse = mouse_to_vect();

	while (iter_coord[0].x != iter_coord[1].x)
	{
		iter_coord[0].y = iter_coord[3].y;
		while (iter_coord[0].y != iter_coord[1].y)
		{
			if (index != -1 && index != get_cell(iter_coord[0].x, iter_coord[0].y)->node->index)
			{
				render_triangle_texture(texture_list[get_cell(previous_coord.x, previous_coord.y)->node->index]->texture_id);
				index = get_cell(iter_coord[0].x, iter_coord[0].y)->node->index;
			}
			else if (index == -1)
				index = index = get_cell(iter_coord[0].x, iter_coord[0].y)->node->index;
			draw_cell(iter_coord[0].x, iter_coord[0].y);
			previous_coord = t_vect(iter_coord[0].x, iter_coord[0].y);
			if (iter_coord[0].x == mouse.x && iter_coord[0].y == mouse.y)
				draw_mouse_cursor(iter_coord[0].x, iter_coord[0].y);
			iter_coord[0].y += iter_coord[2].y;
		}
		iter_coord[0].x += iter_coord[2].x;
	}
	iter_coord[0] = iter_coord[3];
	render_triangle_texture(texture_list[get_cell(previous_coord.x, previous_coord.y)->node->index]->texture_id);
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
	t_cell				*cell = get_cell(i, j);
	t_cell				*right_cell = get_cell(i + next_cell_right.x, j + next_cell_right.y);
	t_cell				*left_cell = get_cell(i + next_cell_left.x, j + next_cell_left.y);
	t_vect				coord[8];
	double				rel_height;
	int					sprite;

	if (cell == NULL || cell->node == NULL || cell->node->index == -1)
		return ;
	rel_height = 0;
	while (rel_height <= cell->coord.z)
	{
		calc_cell(coord, cell, rel_height);
		sprite = get_height_sprite(cell->node->index, cell->node->pos.x, cell->node->pos.y, cell->coord.z - rel_height);
		if (right_cell == NULL || right_cell->coord.z < rel_height)
			texture_list[cell->node->index]->prepare_print(coord[i_index[0]], coord[i_index[1]], coord[i_index[2]], coord[i_index[3]], sprite, 1.0);
		if (left_cell == NULL || left_cell->coord.z < rel_height)
			texture_list[cell->node->index]->prepare_print(coord[i_index[4]], coord[i_index[5]], coord[i_index[6]], coord[i_index[7]], sprite, 1.0);
		rel_height++;
	}
	if (test == 0)
	{
		calc_cell(coord, cell, cell->coord.z);
		if (cell->coord.z != -1)
			texture_list[cell->node->index]->prepare_print(coord[0], coord[1], coord[2], coord[3], cell->node->pos, 1.0);
		if (cell->cursor.x != 0 && cell->cursor.y != 0)
		{
			render_triangle_texture(texture_list[cell->node->index]->texture_id);
			texture_list[0]->draw_self(coord[0], coord[1], coord[2], coord[3], cell->cursor, 1.0);
		}
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
	render_triangle_texture(texture_list[cell->node->index]->texture_id);
	texture_list[0]->draw_self(coord[0], coord[1], coord[2], coord[3], t_vect(0, 1), 1.0);

}
