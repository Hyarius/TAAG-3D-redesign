#include "taag.h"
#include "player_editor_helper.h"

static void		increment_index(int *index, int delta, vector<string> *file_list, vector<string> *final_list)
{
	int				i = 0;

	final_list->clear();
	if (*index + delta >= 0 && (size_t)(*index + delta) < (*file_list).size() && (*file_list).size() > 10)
		*index += delta;
	while (i < 10)
	{
		if ((size_t)(*index + i) >= (*file_list).size())
			(*final_list).push_back("");
		else
			(*final_list).push_back((*file_list)[i + *index]);
		i++;
	}
}

static void		quit_load(t_data data)
{
	t_game_engine	*board = (t_game_engine *)(data.data[0]);
	string			*path = (string *)(data.data[1]);
	string			*saved_path = (string *)(data.data[2]);
	bool *continu = (bool *)(data.data[3]);

	(*board) = t_game_engine(MAP_DESC_PATH + (*path) + MAP_DESC_EXT);
	*saved_path = *path;
	*continu = true;
}

void			menu_load_map(t_data data) //t_data(3, gui, board, quit)
{
	int				index = 0;
	vector<string>	list_file = list_files(MAP_DESC_PATH, MAP_DESC_EXT);
	vector<string>	final_list;

	t_gui		gui = t_gui(30, 20);
	SDL_Event	event;

	bool		continu = false;

	s_button *button = new s_button(new s_text_button(//button did you wanna quit
						get_text("map to load"), DARK_GREY, //text info
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
				quit_load, t_data(4, data.data[1], &(final_list[i]), data.data[2], &continu));
			button->button->text = &(final_list[i]);
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
