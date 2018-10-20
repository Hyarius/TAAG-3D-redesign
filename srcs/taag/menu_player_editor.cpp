#include "taag.h"

static double	calc_line(int line, double space)
{
	double result;

	result = (double)line + (double)line * (double)space;
	return (result);
}

void		menu_player_editor(t_data data)
{
	SDL_Event		event;
	bool			quit = false;
	t_gui			gui = t_gui(30, 20);
	vector<double>	button_pos = {1, 9, 10.25, 12};
	vector<double>	button_size = {7.75, 1, 1.5, 1};
	int				pool = 15;
	vector<int>		value = {45, 6, 3, 3, 3, 3, 3};
	t_color			color[3] = {t_color(0.5, 0.5, 0.5),
								t_color(0.6, 0.6, 0.6),
								t_color(1.0, 1.0, 0.7)};

	gui.add(new s_button(new s_image_button(//image de fond
			t_image(t_color(0.7, 0.7, 0.7)),
			t_vect(0, 0), get_win_size()),
			NULL, NULL));
	double line = calc_line(1, 0.25);
	gui.add(new s_entry(new t_text_entry(get_text("entry name"), NULL, DARK_GREY,//name
									&(gui.entry),
									gui.unit * t_vect(button_pos[0], line), gui.unit * t_vect(button_pos[3] + button_size[3] - button_pos[0], 1), 3,
									color[0], color[1], color[2])));
	line = calc_line(2, 0.25);
	gui.add(new s_iterator(	new t_text_button(get_text("health"), DARK_GREY, //health
								gui.unit * t_vect(button_pos[0], line), gui.unit * t_vect(button_size[0], 1), 3,
								color[0], color[1]),
							new t_text_button(get_text("-"), DARK_GREY, //minus button
								gui.unit * t_vect(button_pos[1], line), gui.unit * t_vect(button_size[1], 1), 3,
								color[0], color[1]),
							new t_text_button(NULL, DARK_GREY, //value button
								gui.unit * t_vect(button_pos[2], line), gui.unit * t_vect(button_size[2], 1), 3,
								color[0], color[1]),
							new t_text_button(get_text("+"), DARK_GREY, //plus button
								gui.unit * t_vect(button_pos[3], line), gui.unit * t_vect(button_size[3], 1), 3,
								color[0], color[1]),
							&value[0], 5, 15, 150,
							&pool, 1));
	line = calc_line(3, 0.25);
	gui.add(new s_iterator(	new t_text_button(get_text("pa"), DARK_GREY, //health
								gui.unit * t_vect(button_pos[0], line), gui.unit * t_vect(button_size[0], 1), 3,
								color[0], color[1]),
							new t_text_button(get_text("-"), DARK_GREY, //minus button
								gui.unit * t_vect(button_pos[1], line), gui.unit * t_vect(button_size[1], 1), 3,
								color[0], color[1]),
							new t_text_button(NULL, DARK_GREY, //value button
								gui.unit * t_vect(button_pos[2], line), gui.unit * t_vect(button_size[2], 1), 3,
								color[0], color[1]),
							new t_text_button(get_text("+"), DARK_GREY, //plus button
								gui.unit * t_vect(button_pos[3], line), gui.unit * t_vect(button_size[3], 1), 3,
								color[0], color[1]),
							&value[1], 1, 4, 12,
							&pool, 5));
	line = calc_line(4, 0.25);
	gui.add(new s_iterator(	new t_text_button(get_text("pm"), DARK_GREY, //health
								gui.unit * t_vect(button_pos[0], line), gui.unit * t_vect(button_size[0], 1), 3,
								color[0], color[1]),
							new t_text_button(get_text("-"), DARK_GREY, //minus button
								gui.unit * t_vect(button_pos[1], line), gui.unit * t_vect(button_size[1], 1), 3,
								color[0], color[1]),
							new t_text_button(NULL, DARK_GREY, //value button
								gui.unit * t_vect(button_pos[2], line), gui.unit * t_vect(button_size[2], 1), 3,
								color[0], color[1]),
							new t_text_button(get_text("+"), DARK_GREY, //plus button
								gui.unit * t_vect(button_pos[3], line), gui.unit * t_vect(button_size[3], 1), 3,
								color[0], color[1]),
							&value[2], 1, 3, 8,
							&pool, 3));
	line = calc_line(5, 0.25);
	gui.add(new s_iterator(	new t_text_button(get_text("atk_phy"), DARK_GREY, //health
								gui.unit * t_vect(button_pos[0], line), gui.unit * t_vect(button_size[0], 1), 3,
								color[0], color[1]),
							new t_text_button(get_text("-"), DARK_GREY, //minus button
								gui.unit * t_vect(button_pos[1], line), gui.unit * t_vect(button_size[1], 1), 3,
								color[0], color[1]),
							new t_text_button(NULL, DARK_GREY, //value button
								gui.unit * t_vect(button_pos[2], line), gui.unit * t_vect(button_size[2], 1), 3,
								color[0], color[1]),
							new t_text_button(get_text("+"), DARK_GREY, //plus button
								gui.unit * t_vect(button_pos[3], line), gui.unit * t_vect(button_size[3], 1), 3,
								color[0], color[1]),
							&value[3], 1, 0, 12,
							&pool, 2));
	line = calc_line(6, 0.25);
	gui.add(new s_iterator(	new t_text_button(get_text("atk_mag"), DARK_GREY, //health
								gui.unit * t_vect(button_pos[0], line), gui.unit * t_vect(button_size[0], 1), 3,
								color[0], color[1]),
							new t_text_button(get_text("-"), DARK_GREY, //minus button
								gui.unit * t_vect(button_pos[1], line), gui.unit * t_vect(button_size[1], 1), 3,
								color[0], color[1]),
							new t_text_button(NULL, DARK_GREY, //value button
								gui.unit * t_vect(button_pos[2], line), gui.unit * t_vect(button_size[2], 1), 3,
								color[0], color[1]),
							new t_text_button(get_text("+"), DARK_GREY, //plus button
								gui.unit * t_vect(button_pos[3], line), gui.unit * t_vect(button_size[3], 1), 3,
								color[0], color[1]),
							&value[4], 1, 0, 12,
							&pool, 2));
	line = calc_line(7, 0.25);
	gui.add(new s_iterator(	new t_text_button(get_text("def_phy"), DARK_GREY, //health
								gui.unit * t_vect(button_pos[0], line), gui.unit * t_vect(button_size[0], 1), 3,
								color[0], color[1]),
							new t_text_button(get_text("-"), DARK_GREY, //minus button
								gui.unit * t_vect(button_pos[1], line), gui.unit * t_vect(button_size[1], 1), 3,
								color[0], color[1]),
							new t_text_button(NULL, DARK_GREY, //value button
								gui.unit * t_vect(button_pos[2], line), gui.unit * t_vect(button_size[2], 1), 3,
								color[0], color[1]),
							new t_text_button(get_text("+"), DARK_GREY, //plus button
								gui.unit * t_vect(button_pos[3], line), gui.unit * t_vect(button_size[3], 1), 3,
								color[0], color[1]),
							&value[5], 1, 0, 12,
							&pool, 2));
	line = calc_line(8, 0.25);
	gui.add(new s_iterator(	new t_text_button(get_text("def_mag"), DARK_GREY, //health
								gui.unit * t_vect(button_pos[0], line), gui.unit * t_vect(button_size[0], 1), 3,
								color[0], color[1]),
							new t_text_button(get_text("-"), DARK_GREY, //minus button
								gui.unit * t_vect(button_pos[1], line), gui.unit * t_vect(button_size[1], 1), 3,
								color[0], color[1]),
							new t_text_button(NULL, DARK_GREY, //value button
								gui.unit * t_vect(button_pos[2], line), gui.unit * t_vect(button_size[2], 1), 3,
								color[0], color[1]),
							new t_text_button(get_text("+"), DARK_GREY, //plus button
								gui.unit * t_vect(button_pos[3], line), gui.unit * t_vect(button_size[3], 1), 3,
								color[0], color[1]),
							&value[6], 1, 0, 12,
							&pool, 2));
	line = calc_line(14, 0.25);
	gui.add(new s_iterator(	new t_text_button(get_text("pool point"), DARK_GREY, //pool point
								gui.unit * t_vect(button_pos[0], line), gui.unit * t_vect(button_size[0], 1), 3,
								color[0], color[1]),
						NULL,
						new t_text_button(NULL, DARK_GREY,
								gui.unit * t_vect(button_pos[2], line), gui.unit * t_vect(button_size[2], 1), 3,
								color[0], color[1]),
						NULL,
						&pool, 0, 0, 0,
						NULL, 0));
	while (quit == false)
	{
		prepare_screen();

		gui.draw_self();

		render_screen(true);

		if (SDL_PollEvent(&(event)) == 1)
		{
			if (event.type == SDL_QUIT)
				menu_quit(t_data(2, &gui, &quit));
				if ((event.type == SDL_KEYUP && event.key.keysym.sym == SDLK_RETURN) || (event.type == SDL_KEYUP && event.key.keysym.sym == SDLK_ESCAPE))
				{
					if (gui.entry != NULL)
					{
						gui.entry = NULL;
						SDL_StopTextInput();
					}
				}
			else if (event.type == SDL_TEXTINPUT)
				gui.entry->add_text(event.text.text);
			else if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_BACKSPACE && gui.entry != NULL)
				gui.entry->delete_text();
			else if (event.type == SDL_MOUSEBUTTONUP)
				gui.click();
		}
	}
}
