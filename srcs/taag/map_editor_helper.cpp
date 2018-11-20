#include "taag.h"
#include "base_value.h"
#include "map_editor_helper.h"

static int tileset_index = 1;

void			t_game_engine::update_z_coord(vector<t_cell *> *vector, double modif)
{
	size_t i = 0;

	while (i < vector->size())
	{
		if ((*vector)[i]->coord.z + modif >= -1 && (*vector)[i]->coord.z + modif < 10)
			(*vector)[i]->coord.z += modif;
		if (board->map_size.z < ((*vector)[i])->coord.z)
			board->map_size.z = ((*vector)[i])->coord.z;
		i++;
	}
}

void			t_game_engine::add_cell_to_vect(vector<t_cell *> *vector, t_cell *cell, bool motion)
{
	size_t i = 0;

	if (cell != NULL && cell->cursor == t_vect(0, 0))
	{
		vector->push_back(cell);
		cell->cursor = t_vect(1, 1);
	}
	else if (motion == false && cell != NULL && cell->cursor == t_vect(1, 1))
	{
		while (i < vector->size() && (*vector)[i] != cell)
			i++;
		vector->erase (vector->begin()+i);
		cell->cursor = t_vect(0, 0);
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
		if (event->wheel.y > 0)
			board->camera->handle_zoom(1.1);
		else if (event->wheel.y < 0)
			board->camera->handle_zoom(0.9);
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
			(*target)[i]->cursor = t_vect(0, 0);
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
			 (event->type == SDL_MOUSEWHEEL && event->wheel.y > 0 && ((*target)[0])->coord.z < 10))
		board->update_z_coord(target, 1);
	else if ((event->type == SDL_KEYUP && event->key.keysym.sym == SDLK_DOWN) ||
			 (event->type == SDL_MOUSEWHEEL && event->wheel.y < 0 && ((*target)[0])->coord.z >= 0))
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
		color[0], color[1]), menu_load_map, t_data(3, gui, board, quit)));
}

void			create_generate_button(t_gui *gui, t_game_engine *board)
{
	gui->add(GUI_OBJ_ID, new s_button(new t_text_button(get_text("generate"), DARK_GREY, //pa
		gui->unit * t_vect(1, 20 - 2 - line_height), gui->unit * t_vect(9, line_height), 3,
		color[0], color[1]), menu_map_generation, t_data(3, gui, quit, board)));
}

void			create_swap_button(t_gui *gui, vector<t_cell *> *target)
{
	int i = 0;

	double b_pos[] = {27, 28.5};
	t_vect increment = t_vect(1, 3);
	t_vect pos = t_vect(0, 0);
	while (pos.x < texture_list[1]->nb_sprite.x && pos.y < texture_list[1]->nb_sprite.y )
	{
		gui->add(GUI_OBJ_ID, new s_button(new t_tileset_button(texture_list[1], pos,
			gui->unit * t_vect(b_pos[i % 2], 2 + (((i / 2) + (i / 2) * 0.5))), gui->unit * t_vect(1, 1), 3), NULL, NULL));

		pos.x += increment.x;
		if (pos.x >= texture_list[1]->nb_sprite.x)
			pos = t_vect(0, pos.y + increment.y);

			i++;
	}
}
