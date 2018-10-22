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
	bool *continu = (bool *)(data.data[2]);
	*continu = true;
}

void			menu_load_actor(t_data data)
{
	vector<string> list_file = list_files(ACT_PATH, ACT_EXT);

	if (list_file.size() == 0)
		return ;
	t_gui		gui = t_gui(30, 20);
	SDL_Event	event;

	bool		continu = false;
	t_color		color[2] = {t_color(0.6, 0.6, 0.6), t_color(0.8, 0.8, 0.8)};

	s_button *button = new s_button(new s_text_button(//button did you wanna quit
						get_text("player to load"), DARK_GREY, //text info
						gui.unit * t_vect(2, 2), gui.unit * t_vect(26, 16), 8, //object info
						t_color(0.5, 0.5, 0.5), t_color(0.65, 0.65, 0.65)),
						NULL, NULL);
	button->button->coord[2] = button->button->coord[2] - (gui.unit * t_vect(0, 6.5));
	gui.add(button);

	double b_pos[2] = {3, 16};
	double b_size[2] = {11, 11};

	size_t i = 0;

	while (i < list_file.size() && i < 10)
	{
		double line = calc_line((i / 2) * 2 + 5, 0.15);
		s_button *button = new s_button(new s_text_button(//button did you wanna quit
						&(list_file[i]), DARK_GREY, //text info
						gui.unit * t_vect(b_pos[i % 2], line), gui.unit * t_vect(b_size[i % 2], 2), 6, //object info
						color[0], color[1]),
						quit_load, t_data(4, data.data[1], &(list_file[i]), &continu, data.data[2]));
		gui.add(button);
		i++;
	}

	while (continu == false)
	{
		prepare_screen();

		if (data.data.size() != 0)
			(*((t_gui *)(data.data[0]))).draw_self();
		gui.draw_self();

		render_screen();

		if (SDL_PollEvent(&(event)) == 1)
		{
			if (event.type == SDL_KEYUP && event.key.keysym.sym == SDLK_ESCAPE)
				continu = true;
			else if (event.type == SDL_MOUSEBUTTONUP)
				gui.click();
		}
	}
}
