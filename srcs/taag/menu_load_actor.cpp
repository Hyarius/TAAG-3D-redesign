#include "taag.h"
#include "player_editor_helper.h"

static double	calc_line(double line, double space)
{
	double result;

	result = (double)line + (double)line * (double)space;
	return (result);
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
	bool *continu = (bool *)(data.data[2]);
	*continu = true;
}

void			menu_load_actor(t_data data)
{
	vector<string> list_file = list_files(ACT_PATH, ACT_EXT);

	t_gui		gui = t_gui(30, 20);
	SDL_Event	event;

	bool		continu = false;

	s_button *button = new s_button(new s_text_button(//button did you wanna quit
						get_text("player to load"), DARK_GREY, //text info
						gui.unit * t_vect(2, 2), gui.unit * t_vect(26, 16), 8, //object info
						color[0], color[1]),
						NULL, NULL);
	button->button->coord[2] = button->button->coord[2] - (gui.unit * t_vect(0, 6.5));
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
		while (i < list_file.size() && i < 10)
		{
			double line = calc_line((i / 2) * 2 + 5, 0.15);
			s_button *button = new s_button(new s_text_button(//button did you wanna quit
							&(list_file[i]), DARK_GREY, //text info
							gui.unit * t_vect(b_pos[i % 2], line), gui.unit * t_vect(b_size[i % 2], 2), 6, //object info
							color[0], color[3]),
							quit_load, t_data(5, data.data[1], &(list_file[i]), &continu, data.data[2], data.data[0]));
			gui.add(GUI_OBJ_ID, button);
			i++;
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
			if (event.type == SDL_KEYUP && event.key.keysym.sym == SDLK_ESCAPE)
				continu = true;
			else if (event.type == SDL_MOUSEBUTTONUP)
				gui.click();
		}
	}
}
