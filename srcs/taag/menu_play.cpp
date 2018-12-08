#include "taag.h"

static void		increment_index(int *index, int delta, vector<string> *file_list, vector<string> *final_list)
{
	int				i = 0;

	final_list->clear();
	if (*index + delta >= 0 && (size_t)(*index + delta) < (*file_list).size() && (*file_list).size() > 10)
		*index += delta;
	while (i < 10)
	{
		if ((size_t)((*index) + i) >= (*file_list).size())
			(*final_list).push_back("");
		else
			(*final_list).push_back((*file_list)[i + (*index)]);
		i++;
	}
}

static void		quit_load(t_data data)
{
	string		full_path = ACT_PATH + *((string *)(data.data[1])) + ACT_EXT;
	*((t_actor *)(data.data[0])) = read_actor(t_data(&full_path));
	bool *continu = (bool *)(data.data[2]);
	*continu = true;
}

void			menu_play_load_actor(t_data data)
{
	int				index = 0;
	vector<string>	list_file = list_files(ACT_PATH, ACT_EXT);
	vector<string>	final_list;
	vector<t_button *>	button_list;
	t_gui		gui = t_gui(30, 20);
	SDL_Event	event;

	bool		continu = false;

	s_button *button = new s_button(new s_text_button(//button did you wanna quit
						get_text("player to load"), DARK_GREY, //text info
						gui.unit * t_vect(2, 2), gui.unit * t_vect(26, 16), 8, //object info
						color[0], color[1]),
						NULL, NULL);
	button->button->image_coord = button->button->image_coord - (gui.unit * t_vect(0, 6.5));
	gui.add(GUI_OBJ_ID, button);

	double b_pos[2] = {3, 16};
	double b_size[2] = {11, 11};

	size_t i = 0;
	if (list_file.size() == 0)
	{
		s_button *button = new s_button(new s_text_button(//button did you wanna quit
						get_text("no file"), DARK_GREY, //text info
						gui.unit * t_vect(7, 9), gui.unit * t_vect(16, 5), 6, //object info
						color[0], color[1]),
						stand, t_data(1, &continu));
		gui.add(GUI_OBJ_ID, button);
		i++;
	}
	else
	{
		while (i < 10)
		{
			if (i + index < list_file.size())
				final_list.push_back(list_file[i + index]);
			else
				final_list.push_back("");
			i++;
		}
		i = 0;
		while (i < 10)
		{
			double line = calc_line((i / 2) * 2 + 2, 0.33);
			s_button *button = new s_button(new s_text_button(//button did you wanna quit
				NULL, DARK_GREY, //text info
				gui.unit * t_vect(b_pos[i % 2], line), gui.unit * t_vect(b_size[i % 2], 2), 6, //object info
				color[0], color[3]),
				quit_load, t_data(5, data.data[1], &(final_list[i]), &continu));
			button->button->text = &(final_list[i]);
			button_list.push_back(button);
			gui.add(GUI_OBJ_ID, button);
			i++;
		}
	}

	while (continu == false)
	{
		prepare_screen();

		if (data.data.size() != 0)
			(*((t_gui *)(data.data[0]))).draw_self();
		gui.draw_self();

		render_screen(draw_fps);

		if (SDL_PollEvent(&(event)) == 1)
		{
			if (event.type == SDL_QUIT)
				menu_quit(&gui);
			else if (event.type == SDL_KEYUP && event.key.keysym.sym == SDLK_ESCAPE)
				continu = true;
			else if (event.type == SDL_MOUSEBUTTONUP && event.button.button == SDL_BUTTON_LEFT)
				gui.click();
			if (event.type == SDL_MOUSEWHEEL && event.wheel.y > 0)
				increment_index(&index, -2, &list_file, &final_list);
			else if (event.type == SDL_MOUSEWHEEL && event.wheel.y < 0)
				increment_index(&index, 2, &list_file, &final_list);
		}
	}
}

void		create_player_selector_red(t_gui *gui, vector <t_actor> *actor_red)
{
	t_text_button *tmp = new t_text_button(get_text("red team comp"), DARK_GREY, //text info
									gui->unit * 1, gui->unit * t_vect(6, 18), 8, //object info
									color[0], color[1]);
	tmp->image_coord.y = tmp->image_coord.y - gui->unit.y * 8.5;
	gui->add(GUI_OBJ_ID, new s_button(tmp, NULL, NULL));

	size_t i = 0;
	while (i < actor_red->size())
	{
		tmp = new t_text_button(NULL, DARK_GREY, //text info
				gui->unit * t_vect(1.5, 2.0 + (double)i * 2), gui->unit * t_vect(5, line_height * 2), 8, //object info
				color[0], color[3]);
		gui->add(GUI_OBJ_ID, new s_button(tmp, menu_play_load_actor, t_data(3, gui, &((*actor_red)[i]), NULL)));
		tmp = new t_text_button(&((*actor_red)[i].name), DARK_GREY, //text info
				gui->unit * t_vect(1.5, 2.0 + (double)i * 2), gui->unit * t_vect(5, line_height), 8, //object info
				t_color(0, 0, 0, 0), t_color(0, 0, 0, 0));
		gui->add(GUI_OBJ_ID, new s_button(tmp, NULL, NULL));

		gui->add(ITERATOR_ID, new s_iterator(new t_text_button(get_text("level"), DARK_GREY, //pool point
			gui->unit * t_vect(1.5, 2.0 + (double)i * 2 + line_height), gui->unit * t_vect(3, line_height), 8,
			t_color(0, 0, 0, 0), t_color(0, 0, 0, 0)),
			NULL,
			new t_text_button(NULL, DARK_GREY,
			gui->unit * t_vect(3, 2.0 + (double)i * 2 + line_height), gui->unit * t_vect(2, line_height), 3,
			t_color(0, 0, 0, 0), t_color(0, 0, 0, 0)),
			NULL,
			&((*actor_red)[i].level), 0, 0, 0,
			NULL, 0, NULL));
		i++;
	}
}

void		create_player_selector_blue(t_gui *gui, vector <t_actor> *actor_blue)
{
	t_text_button *tmp = new t_text_button(get_text("blue team comp"), DARK_GREY, //text info
									gui->unit * t_vect(23, 1), gui->unit * t_vect(6, 18), 8, //object info
									color[0], color[1]);
	tmp->image_coord.y = tmp->image_coord.y - gui->unit.y * 8.5;
	gui->add(GUI_OBJ_ID, new s_button(tmp, NULL, NULL));

	size_t i = 0;
	while (i < actor_blue->size())
	{
		tmp = new t_text_button(NULL, DARK_GREY, //text info
				gui->unit * t_vect(23.5, 2.0 + (double)i * 2), gui->unit * t_vect(5, line_height * 2), 8, //object info
				color[0], color[3]);
		gui->add(GUI_OBJ_ID, new s_button(tmp, NULL, NULL));
		tmp = new t_text_button(&((*actor_blue)[i].name), DARK_GREY, //text info
				gui->unit * t_vect(23.5, 2.0 + (double)i * 2), gui->unit * t_vect(5, line_height), 8, //object info
				t_color(0, 0, 0, 0), t_color(0, 0, 0, 0));
		gui->add(GUI_OBJ_ID, new s_button(tmp, NULL, NULL));

		gui->add(ITERATOR_ID, new s_iterator(new t_text_button(get_text("level"), DARK_GREY, //pool point
			gui->unit * t_vect(23.5, 2.0 + (double)i * 2 + line_height), gui->unit * t_vect(3, line_height), 8,
			t_color(0, 0, 0, 0), t_color(0, 0, 0, 0)),
			NULL,
			new t_text_button(NULL, DARK_GREY,
			gui->unit * t_vect(25, 2.0 + (double)i * 2 + line_height), gui->unit * t_vect(2, line_height), 3,
			t_color(0, 0, 0, 0), t_color(0, 0, 0, 0)),
			NULL,
			&((*actor_blue)[i].level), 0, 0, 0,
			NULL, 0, NULL));
		i++;
	}
}

void		menu_play(t_data data)
{
	SDL_Event		event;
	bool			quit = false;
	t_gui			gui = t_gui(30, 20);
	vector <t_actor>	actor_red;
	vector <t_actor>	actor_blue;

	actor_red.resize(8);

	actor_blue.resize(8);

	gui.add(GUI_OBJ_ID, new s_button(new s_image_button( t_image(t_color(0.2, 0.2, 0.2)), t_vect(0, 0), get_win_size()), NULL, NULL));

	create_player_selector_red(&gui, &actor_red);
	create_player_selector_blue(&gui, &actor_blue);

	while (quit == false)
	{
		prepare_screen();

		gui.draw_self();

		render_screen(draw_fps);

		if (SDL_PollEvent(&(event)) == 1)
		{
			if (event.type == SDL_QUIT)
				menu_quit(&gui);
			else if ((event.type == SDL_KEYUP && event.key.keysym.sym == SDLK_RETURN) || (event.type == SDL_KEYUP && event.key.keysym.sym == SDLK_ESCAPE))
				menu_quit(t_data(2, &gui, &quit));
			else if (event.type == SDL_TEXTINPUT)
				gui.entry->add_text(event.text.text);
			else if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_BACKSPACE && gui.entry != NULL)
				gui.entry->delete_text();
			else if (event.type == SDL_MOUSEBUTTONUP && event.button.button == SDL_BUTTON_LEFT)
				gui.click();
		}
	}
}
