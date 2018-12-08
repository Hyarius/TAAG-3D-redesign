#include "taag.h"

s_cell::s_cell()
{
	coord = t_vertex(0, 0, 0);
	node = NULL;
	actor = NULL;
	cursor = t_vect(0, 0);
	is_selected = t_vect(0, 0);
}

s_cell::s_cell(t_vertex p_coord, t_node *p_node, t_actor *p_actor)
{
	coord = p_coord;
	node = p_node;
	actor = p_actor;
	cursor = t_vect(0, 0);
	is_selected = t_vect(0, 0);
}
