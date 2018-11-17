#include "taag.h"
#include "base_value.h"

void			control_empty(SDL_Event *event, t_gui *gui, bool *quit, t_game_engine *board, vector<t_cell *> *target)
{
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
	else if (event->type == SDL_MOUSEBUTTONUP && event->button.button == SDL_BUTTON_LEFT)
	{
		t_vect result = board->mouse_to_vect();
		t_cell	*cell = board->get_cell(result.x, result.y);
		if (cell != NULL)
		{
			target->push_back(cell);
			cell->cursor = t_vect(1, 1);
		}
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
	else if (event->type == SDL_TEXTINPUT)
		gui->entry->add_text(event->text.text);
	else if (event->type == SDL_KEYDOWN && event->key.keysym.sym == SDLK_BACKSPACE && gui->entry != NULL)
		gui->entry->delete_text();
}

void			control_selected(SDL_Event *event, t_gui *gui, bool *quit, t_game_engine *board, vector<t_cell *> *target)
{
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
		board->handle_rot(0 - event->motion.xrel);
	else if (event->type == SDL_MOUSEMOTION && event->motion.state == SDL_BUTTON_RMASK)
		board->camera->handle_move(event->motion.xrel, event->motion.yrel);
	else if (event->type == SDL_MOUSEBUTTONUP && event->button.button == SDL_BUTTON_LEFT)
	{
		t_vect result = board->mouse_to_vect();
		t_cell	*cell = board->get_cell(result.x, result.y);
		if (cell != NULL && cell->cursor == t_vect(0, 0))
		{
			target->push_back(cell);
			cell->cursor = t_vect(1, 1);
		}
		else if (cell != NULL && cell->cursor == t_vect(1, 1))
		{
			while (i < target->size() && (*target)[i] != cell)
				i++;
			target->erase (target->begin()+i);
			cell->cursor = t_vect(0, 0);
		}
		gui->click();
	}
	else if (event->type == SDL_KEYUP && event->key.keysym.sym == SDLK_UP)
	{
		while (i < target->size())
		{
			(*target)[i]->coord.z++;
			if (board->board->map_size.z < ((*target)[0])->coord.z)
				board->board->map_size.z = ((*target)[0])->coord.z;
			i++;
		}
	}
	else if (event->type == SDL_KEYUP && event->key.keysym.sym == SDLK_DOWN)
	{
		while (i < target->size())
		{
			(*target)[i]->coord.z--;
			i++;
		}
	}

	else if (event->type == SDL_MOUSEWHEEL)
	{
		if (event->wheel.y > 0 && ((*target)[0])->coord.z < 10)
		{
			while (i < target->size())
			{
				(*target)[i]->coord.z++;
				if (board->board->map_size.z < ((*target)[0])->coord.z)
					board->board->map_size.z = ((*target)[0])->coord.z;
				i++;
			}
		}
		else if (event->wheel.y < 0 && ((*target)[0])->coord.z >= 0)
		{
			while (i < target->size())
			{
				(*target)[i]->coord.z--;
				i++;
			}
		}
	}
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
		color[0], color[1]), NULL, NULL));
}

void			create_load_button(t_gui *gui, t_game_engine *board, string *p_path)
{
	gui->add(GUI_OBJ_ID, new s_button(new t_text_button(get_text("load"), DARK_GREY, //pa
		gui->unit * t_vect(20, 20 - 1 - line_height), gui->unit * t_vect(9, line_height), 3,
		color[0], color[1]), NULL, NULL));
}

void			create_generate_button(t_gui *gui, t_game_engine *board)
{
	gui->add(GUI_OBJ_ID, new s_button(new t_text_button(get_text("generate"), DARK_GREY, //pa
		gui->unit * t_vect(1, 20 - 2 - line_height), gui->unit * t_vect(9, line_height), 3,
		color[0], color[1]), NULL, NULL));
}
