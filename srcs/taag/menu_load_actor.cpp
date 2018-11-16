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
	string		full_path = ACT_PATH + *((string *)(data.data[1])) + ACT_EXT;
	*((string *)(data.data[3])) = *((string *)(data.data[1]));
	*((t_actor *)(data.data[0])) = read_actor(t_data(&full_path));
	size_t i = 0;
	t_gui	*gui = ((t_gui *)(data.data[4]));

	while (i < gui->object_list[SPELL_CARD_ID].size())
	{
		((t_spell_card *)(gui->object_list[SPELL_CARD_ID].at(i)))->set_desc_size();
		i++;
	}

	i = 0;
	while (i < gui->object_list[ITERATOR_ID].size())
	{
		((t_iterator *)(gui->object_list[ITERATOR_ID].at(i)))->set_text_value();
		i++;
	}

	i = 0;
	while (i < gui->object_list[SPRITE_SELECTOR_ID].size())
	{
		((t_sprite_selector *)(gui->object_list[SPRITE_SELECTOR_ID].at(i)))->reset_actor((t_actor *)(data.data[0]));
		i++;
	}
	bool *continu = (bool *)(data.data[2]);
	*continu = true;
}

void			menu_load_actor(t_data data)
{
	int				index = 0;
	vector<string>	list_file = list_files(ACT_PATH, ACT_EXT);
	vector<string>	final_list;

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
			double line = calc_line((i / 2) * 2 + 5, 0.15);
			s_button *button = new s_button(new s_text_button(//button did you wanna quit
				&(final_list[i]), DARK_GREY, //text info
				gui.unit * t_vect(b_pos[i % 2], line), gui.unit * t_vect(b_size[i % 2], 2), 6, //object info
				color[0], color[3]),
				quit_load, t_data(5, data.data[1], &(final_list[i]), &continu, data.data[2], data.data[0]));
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
