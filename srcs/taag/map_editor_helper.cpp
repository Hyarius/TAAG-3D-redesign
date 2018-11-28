#include "taag.h"
#include "base_value.h"
#include "map_editor_helper.h"

static int tileset_index = 1;

static void		change_cell_cursor(t_data data)
{
	vector<t_cell *>	*target = ((vector<t_cell *> *)(data.data[0]));
	t_vect				*new_cursor = ((t_vect *)(data.data[1]));

	size_t i = 0;
	while (i < target->size())
	{
		(*target)[i]->cursor = *new_cursor;
		(*target)[i]->is_selected = t_vect(0, 0);
		i++;
	}
	target->clear();
}

void			t_game_engine::update_z_coord(vector<t_cell *> *vector, double modif)
{
	size_t i = 0;

	while (i < vector->size())
	{
		if ((*vector)[i]->coord.z + modif >= -1 && (*vector)[i]->coord.z + modif < 30)
			(*vector)[i]->coord.z += modif;
		if (board->map_size.z < ((*vector)[i])->coord.z)
			board->map_size.z = ((*vector)[i])->coord.z;
		i++;
	}
}

void			t_game_engine::add_cell_to_vect(vector<t_cell *> *vector, t_cell *cell, bool motion)
{
	size_t i = 0;

	if (cell != NULL && cell->is_selected == t_vect(0, 0))
	{
		vector->push_back(cell);
		cell->is_selected = t_vect(1, 1);
	}
	else if (motion == false && cell != NULL && cell->is_selected == t_vect(1, 1))
	{
		while (i < vector->size() && (*vector)[i] != cell)
			i++;
		vector->erase (vector->begin()+i);
		cell->is_selected = t_vect(0, 0);
	}
}

void			t_game_engine::reset_vector(vector<t_cell *> *target)
{
	size_t i = 0;

	while (i < target->size())
	{
		(*target)[i]->cursor = t_vect(0, 0);
		i++;
	}
	target->clear();
}

void			control_empty(SDL_Event *event, t_gui *gui, bool *quit, t_game_engine *board, vector<t_cell *> *target)
{
	t_vect mouse = board->mouse_to_vect();
	if (event->type == SDL_QUIT ||
		(event->type == SDL_KEYUP && event->key.keysym.sym == SDLK_RETURN) ||
		(event->type == SDL_KEYUP && event->key.keysym.sym == SDLK_ESCAPE))
	{
		if (gui->entry != NULL)
		{
			gui->entry = NULL;
			SDL_StopTextInput();
		}
		else
			menu_quit(t_data(3, gui, quit, board));
	}
	else if (event->type == SDL_KEYDOWN && event->key.keysym.sym == SDLK_UP)
		board->handle_vertical_rot(2);
	else if (event->type == SDL_KEYDOWN && event->key.keysym.sym == SDLK_DOWN)
		board->handle_vertical_rot(-2);
	else if (event->type == SDL_KEYDOWN && event->key.keysym.sym == SDLK_LEFT)
		board->handle_rot(2);
	else if (event->type == SDL_KEYDOWN && event->key.keysym.sym == SDLK_RIGHT)
		board->handle_rot(-2);
	else if (event->type == SDL_MOUSEBUTTONDOWN && event->button.button == SDL_BUTTON_LEFT)
	{
		board->add_cell_to_vect(target, board->get_cell(mouse.x, mouse.y), false);
		gui->click();
	}
	else if (event->type == SDL_MOUSEMOTION && event->motion.state == SDL_BUTTON_MMASK)
	{
		board->handle_rot(0 - event->motion.xrel);
		board->handle_vertical_rot(0 - event->motion.yrel);
	}
	else if (event->type == SDL_MOUSEMOTION && event->motion.state == SDL_BUTTON_RMASK)
		board->camera->handle_move(event->motion.xrel, event->motion.yrel);
	else if (event->type == SDL_MOUSEWHEEL)
	{
		if (board->camera != NULL)
		{
			if (event->wheel.y > 0)
				board->camera->handle_zoom(1.1);
			else if (event->wheel.y < 0)
				board->camera->handle_zoom(0.9);
		}
	}
	else if (gui->entry != NULL && event->type == SDL_TEXTINPUT)
		gui->entry->add_text(event->text.text);
	else if (gui->entry != NULL && event->type == SDL_KEYDOWN && event->key.keysym.sym == SDLK_BACKSPACE && gui->entry != NULL)
		gui->entry->delete_text();
}

void			control_selected(SDL_Event *event, t_gui *gui, bool *quit, t_game_engine *board, vector<t_cell *> *target)
{
	t_vect mouse = board->mouse_to_vect();
	size_t i = 0;
	if (event->type == SDL_QUIT)
		menu_quit(t_data(3, gui, quit, board));
	else if (event->type == SDL_KEYUP && event->key.keysym.sym == SDLK_ESCAPE)
	{
		while (i < target->size())
		{
			(*target)[i]->is_selected = t_vect(0, 0);
			i++;
		}
		target->clear();
	}
	else if (event->type == SDL_MOUSEMOTION && event->motion.state == SDL_BUTTON_MMASK)
	{
		board->handle_rot(0 - event->motion.xrel);
		board->handle_vertical_rot(0 - event->motion.yrel);
	}
	else if (event->type == SDL_MOUSEMOTION && event->motion.state == SDL_BUTTON_RMASK)
		board->camera->handle_move(event->motion.xrel, event->motion.yrel);
	else if (event->type == SDL_MOUSEMOTION && event->button.button == SDL_BUTTON_LEFT)
		board->add_cell_to_vect(target, board->get_cell(mouse.x, mouse.y), true);
	else if (event->type == SDL_MOUSEBUTTONDOWN && event->button.button == SDL_BUTTON_LEFT)
	{
		board->add_cell_to_vect(target, board->get_cell(mouse.x, mouse.y), false);
		gui->click();
	}
	else if ((event->type == SDL_KEYUP && event->key.keysym.sym == SDLK_UP) ||
			 (event->type == SDL_MOUSEWHEEL && event->wheel.y > 0))
		board->update_z_coord(target, 1);
	else if ((event->type == SDL_KEYUP && event->key.keysym.sym == SDLK_DOWN) ||
			 (event->type == SDL_MOUSEWHEEL && event->wheel.y < 0))
		board->update_z_coord(target, -1);
}

void			create_file_entry(t_gui *gui, string *p_name)
{
	s_entry *entry = new s_entry(new t_text_entry(get_text("entry file_name"),
				p_name, DARK_GREY,//name
				&(gui->entry),
				gui->unit * t_vect(1, 1),
				gui->unit * t_vect(9, line_height),
				3, color[0], color[1], color[2]));
	entry->entry->set_front(MAP_PATH);
	entry->entry->set_back(MAP_EXT);
	entry->entry->draw_funct = draw_centred_text;
	entry->entry->coord[2] = gui->unit * t_vect(5.5, 1 + line_height / 2);
	gui->add(GUI_OBJ_ID, entry);
}

void			create_save_button(t_gui *gui, t_game_engine *board, string *p_path)
{
	gui->add(GUI_OBJ_ID, new s_button(new t_text_button(get_text("save"), DARK_GREY, //pa
		gui->unit * t_vect(1, 20 - 1 - line_height), gui->unit * t_vect(9, line_height), 3,
		color[0], color[1]), menu_save_map, t_data(3, gui, board, p_path)));
}

void			create_load_button(t_gui *gui, t_game_engine *board, string *p_path)
{
	gui->add(GUI_OBJ_ID, new s_button(new t_text_button(get_text("load"), DARK_GREY, //pa
		gui->unit * t_vect(20, 20 - 1 - line_height), gui->unit * t_vect(9, line_height), 3,
		color[0], color[1]), menu_load_map, t_data(4, gui, board, p_path, quit)));
}

void			create_erase_button(t_gui *gui, string *p_path)
{
	gui->add(GUI_OBJ_ID, new s_button(new t_text_button(get_text("erase"), DARK_GREY, //pa
		gui->unit * t_vect(10.5, 20 - 1 - line_height), gui->unit * t_vect(9, line_height), 3,
		color[0], color[1]), menu_delete_map, t_data(2, gui, p_path)));
}

void			create_generate_button(t_gui *gui, t_game_engine *board)
{
	gui->add(GUI_OBJ_ID, new s_button(new t_text_button(get_text("generate"), DARK_GREY, //pa
		gui->unit * t_vect(1, 20 - 2 - line_height), gui->unit * t_vect(9, line_height), 3,
		color[0], color[1]), menu_map_generation, t_data(3, gui, quit, board)));
}

static void		change_block_texture(t_data data)
{
	vector<t_cell *>	*target = (vector<t_cell *> *)(data.data[0]);
	t_node				*new_node = (t_node *)(data.data[1]);

	size_t i = 0;
	while (i < target->size())
	{
		(*target)[i]->node = new_node;
		i++;
	}
}

void			create_swap_button(t_gui *gui, vector<t_cell *> *target)
{
	size_t i = 0;
	static int tmp = 0;

	double b_pos[] = {27, 28.5};
	t_vect increment = t_vect(1, 3);
	t_vect pos = t_vect(0, 0);
	while (i < node_list.size())
	{
		gui->add(GUI_OBJ_ID, new s_button(new t_tileset_button(&texture_list, &tmp, pos,
			gui->unit * t_vect(b_pos[i % 2], 2 + (((i / 2) + (i / 2) * 0.5))), gui->unit * t_vect(1, 1), 3), change_block_texture, t_data(2, target, node_list[i])));
		pos.x += increment.x;
		if (pos.x >= texture_list[1]->nb_sprite.x)
			pos = t_vect(0, pos.y + increment.y);
		i++;
	}
}

void			create_spawn_selector_button(t_gui *gui, vector<t_cell *> *target)
{
	static int tmp = 0;
	static t_vect pos = t_vect(1, 3);
	gui->add(GUI_OBJ_ID, new s_button(new t_tileset_button(&texture_list, &tmp, pos,
		gui->unit * t_vect(1, 2), t_vect(gui->unit.y, gui->unit.y), 3), change_cell_cursor, t_data(2, target, &pos)));
	static t_vect pos2 = t_vect(2, 3);
	gui->add(GUI_OBJ_ID, new s_button(new t_tileset_button(&texture_list, &tmp, pos2,
		gui->unit * t_vect(1 + (gui->unit.y / gui->unit.x) + 0.2, 2), t_vect(gui->unit.y, gui->unit.y), 3), change_cell_cursor, t_data(2, target, &pos2)));
	static t_vect pos3 = t_vect(0, 0);
	gui->add(GUI_OBJ_ID, new s_button(new t_tileset_button(&texture_list, &tmp, pos3,
		gui->unit * t_vect(1 + (gui->unit.y / gui->unit.x) * 2 + 0.4, 2), t_vect(gui->unit.y, gui->unit.y), 3), change_cell_cursor, t_data(2, target, &pos3)));
}

void			create_object_editor(t_gui *gui, t_game_object *object)
{
	t_vect		coord = t_vect(1, 3.33);
	t_vect		size = t_vect(6, 10);

	coord = t_vect(1.25, 3.5);
	size = t_vect(0.4, 0.4);
	t_button *mini = new s_button(new t_text_button(get_text("close"), BLACK,
		gui->unit * coord, gui->unit * size, 2, color[0], color[3]), NULL, NULL);

	coord = t_vect(1.25, 4);
	size = t_vect(4, line_height);
	t_button *name = new s_button(new t_text_button(&(object->name), BLACK,
		gui->unit * coord, gui->unit * size, 2, color[0], color[1]), NULL, NULL);

	coord = t_vect(5.5, 3.6);
	t_tileset_button *sprite = new t_tileset_button(&tile_list, &(object->tile_index), object->sprite_pos,
				gui->unit * coord, t_vect(gui->unit.y * 1.25, gui->unit.y * 1.25), 3);

	coord = t_vect(1.25, 4 + line_height + 0.2);
	size = t_vect(4, line_height / 2);
	t_vect	coord2 = t_vect(coord.x + size.x + 0.25, coord.y);
	t_vect size2 = t_vect(1, line_height / 2);
	t_iterator *hp = new s_iterator(new t_text_button(get_text("health"), BLACK,
		gui->unit * coord, gui->unit * size, 2, color[0], color[1]),
		NULL,
		new t_text_button(NULL, DARK_GREY,
			gui->unit * coord2, gui->unit * size2, 2, color[0], color[1]),
		NULL,
		&(object->stat.hp.max), 0, 0, 0,
		NULL, 0, NULL);

	coord = t_vect(coord.x, coord.y + size.y + 0.2);
	coord2 = t_vect(coord2.x, coord2.y + size2.y + 0.2);
	t_iterator *pa = new s_iterator(new t_text_button(get_text("pa"), BLACK,
		gui->unit * coord, gui->unit * size, 2, color[0], color[1]),
		NULL,
		new t_text_button(NULL, DARK_GREY,
			gui->unit * coord2, gui->unit * size2, 2, color[0], color[1]),
		NULL,
		&(object->stat.pa.max), 0, 0, 0,
		NULL, 0, NULL);;

	coord = t_vect(coord.x, coord.y + size.y + 0.2);
	coord2 = t_vect(coord2.x, coord2.y + size2.y + 0.2);
	t_iterator *pm = new s_iterator(new t_text_button(get_text("pm"), BLACK,
		gui->unit * coord, gui->unit * size, 2, color[0], color[1]),
		NULL,
		new t_text_button(NULL, DARK_GREY,
			gui->unit * coord2, gui->unit * size2, 2, color[0], color[1]),
		NULL,
		&(object->stat.pm.max), 0, 0, 0,
		NULL, 0, NULL);;

	coord = t_vect(coord.x, coord.y + size.y + 0.2);
	coord2 = t_vect(coord2.x, coord2.y + size2.y + 0.2);
	t_iterator *atk_phy = new s_iterator(new t_text_button(get_text("atk_phy"), BLACK,
		gui->unit * coord, gui->unit * size, 2, color[0], color[1]),
		NULL,
		new t_text_button(NULL, DARK_GREY,
			gui->unit * coord2, gui->unit * size2, 2, color[0], color[1]),
		NULL,
		&(object->stat.phy.atk), 0, 0, 0,
		NULL, 0, NULL);;

	coord = t_vect(coord.x, coord.y + size.y + 0.2);
	coord2 = t_vect(coord2.x, coord2.y + size2.y + 0.2);
	t_iterator *def_phy = new s_iterator(new t_text_button(get_text("def_phy"), BLACK,
		gui->unit * coord, gui->unit * size, 2, color[0], color[1]),
		NULL,
		new t_text_button(NULL, DARK_GREY,
			gui->unit * coord2, gui->unit * size2, 2, color[0], color[1]),
		NULL,
		&(object->stat.phy.def), 0, 0, 0,
		NULL, 0, NULL);;

	coord = t_vect(coord.x, coord.y + size.y + 0.2);
	coord2 = t_vect(coord2.x, coord2.y + size2.y + 0.2);
	t_iterator *atk_mag = new s_iterator(new t_text_button(get_text("atk_mag"), BLACK,
		gui->unit * coord, gui->unit * size, 2, color[0], color[1]),
		NULL,
		new t_text_button(NULL, DARK_GREY,
			gui->unit * coord2, gui->unit * size2, 2, color[0], color[1]),
		NULL,
		&(object->stat.mag.atk), 0, 0, 0,
		NULL, 0, NULL);;

	coord = t_vect(coord.x, coord.y + size.y + 0.2);
	coord2 = t_vect(coord2.x, coord2.y + size2.y + 0.2);
	t_iterator *def_mag = new s_iterator(new t_text_button(get_text("def_mag"), BLACK,
		gui->unit * coord, gui->unit * size, 2, color[0], color[1]),
		NULL,
		new t_text_button(NULL, DARK_GREY,
			gui->unit * coord2, gui->unit * size2, 2, color[0], color[1]),
		NULL,
		&(object->stat.mag.def), 0, 0, 0,
		NULL, 0, NULL);;

	size = t_vect(5.5, line_height / 1.5);
	coord = t_vect(1.25, coord.y + size.y + 0.2);
	t_button *choose = new s_button(new t_text_button(get_text("choose object"), BLACK,
		gui->unit * coord, gui->unit * size, 2, color[0], color[1]), NULL, NULL);

	coord = t_vect(1.25, coord.y + size.y + 0.2);
	t_button *place = new s_button(new t_text_button(get_text("place object"), BLACK,
		gui->unit * coord, gui->unit * size, 2, color[0], color[1]), NULL, NULL);

	size = t_vect(6, coord.y + size.y + 0.2 - 3.33);
	coord = t_vect(1, 3.33);
	t_button 	*back = new s_button(new t_text_button(NULL, BLACK,
		gui->unit * coord, gui->unit * size, 2, color[0], color[1]), NULL, NULL);

	gui->add(GUI_OBJ_ID, new s_game_object_card(mini, back, sprite, name, hp, pa, pm, atk_phy, def_phy, atk_mag, def_mag, choose, place));

}
