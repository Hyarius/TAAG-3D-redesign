#include "taag.h"

static double	calc_line(int line, double space)
{
	double result;

	result = line + space;
	return (result);
}

void		menu_player_editor(t_data data)
{
	SDL_Event	event;
	bool		quit = false;

	t_gui	gui;

	gui.unit = get_win_size() / t_vect(30, 20);

	double	pos[4] = {1, 6.25, 7.5, 9.25};
	double	size[4] = {5, 1, 1.5, 1};
	int		pool = 30;

	t_color	color[3] = {t_color(0.5, 0.5, 0.5), t_color(0.6, 0.6, 0.6), t_color(1.0, 1.0, 0.7)};

	int		health = 45, pa = 6, pm = 3;

	gui.add(new s_button(new s_image_button(//image de fond
			t_image(t_color(0.7, 0.7, 0.7)),
			t_vect(0, 0), get_win_size()),
			NULL, NULL));


	int line = calc_line(1, 0.25);
	gui.add(new s_entry(new t_text_entry(get_text("entry name"), NULL, DARK_GREY,//name
									&(gui.entry),
									gui.unit * t_vect(pos[0], line), gui.unit * t_vect(9, 1), 3,
									color[0], color[1], color[2])));



	line = calc_line(2, 0.25);
	gui.add(new s_iterator(	new t_text_button(get_text("health"), DARK_GREY, //health
								gui.unit * t_vect(pos[0], line), gui.unit * t_vect(size[0], 1), 3,
								color[0], color[1]),
							new t_text_button(get_text("-"), DARK_GREY, //minus button
								gui.unit * t_vect(pos[1], line), gui.unit * t_vect(size[1], 1), 3,
								color[0], color[1]),
							new t_text_button(NULL, DARK_GREY, //value button
								gui.unit * t_vect(pos[2], line), gui.unit * t_vect(size[2], 1), 3,
								color[0], color[1]),
							new t_text_button(get_text("+"), DARK_GREY, //plus button
								gui.unit * t_vect(pos[3], line), gui.unit * t_vect(size[3], 1), 3,
								color[0], color[1]),
							&health, 5, 15, 150,
							&pool, 1));



	line = calc_line(3, 0.25);
	gui.add(new s_iterator(	new t_text_button(get_text("pa"), DARK_GREY, //health
								gui.unit * t_vect(pos[0], line), gui.unit * t_vect(size[0], 1), 3,
								color[0], color[1]),
							new t_text_button(get_text("-"), DARK_GREY, //minus button
								gui.unit * t_vect(pos[1], line), gui.unit * t_vect(size[1], 1), 3,
								color[0], color[1]),
							new t_text_button(NULL, DARK_GREY, //value button
								gui.unit * t_vect(pos[2], line), gui.unit * t_vect(size[2], 1), 3,
								color[0], color[1]),
							new t_text_button(get_text("+"), DARK_GREY, //plus button
								gui.unit * t_vect(pos[3], line), gui.unit * t_vect(size[3], 1), 3,
								color[0], color[1]),
							&pa, 1, 4, 12,
							&pool, 5));




	line = calc_line(4, 0.25);
	gui.add(new s_iterator(	new t_text_button(get_text("pm"), DARK_GREY, //health
								gui.unit * t_vect(pos[0], line), gui.unit * t_vect(size[0], 1), 3,
								color[0], color[1]),
							new t_text_button(get_text("-"), DARK_GREY, //minus button
								gui.unit * t_vect(pos[1], line), gui.unit * t_vect(size[1], 1), 3,
								color[0], color[1]),
							new t_text_button(NULL, DARK_GREY, //value button
								gui.unit * t_vect(pos[2], line), gui.unit * t_vect(size[2], 1), 3,
								color[0], color[1]),
							new t_text_button(get_text("+"), DARK_GREY, //plus button
								gui.unit * t_vect(pos[3], line), gui.unit * t_vect(size[3], 1), 3,
								color[0], color[1]),
							&pm, 1, 3, 8,
							&pool, 3));

	line = calc_line(15, 0.25);
	gui.add(new s_iterator(	new t_text_button(get_text("pool point"), DARK_GREY, //pool point
								gui.unit * t_vect(1, line), gui.unit * t_vect(7.25, 1), 3,
								color[0], color[1]),
						NULL,
						new t_text_button(NULL, DARK_GREY,
								gui.unit * t_vect(8.5, line), gui.unit * t_vect(1.5, 1), 3,
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
			if (event.type == SDL_QUIT || (event.type == SDL_KEYUP && event.key.keysym.sym == SDLK_ESCAPE))
				menu_quit(t_data(2, &gui, &quit));
			else if (event.type == SDL_TEXTINPUT)
				gui.entry->add_text(event.text.text);
			else if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_BACKSPACE && gui.entry != NULL)
				gui.entry->delete_text();
			else if (event.type == SDL_MOUSEBUTTONUP)
				gui.click();
		}
	}
}
