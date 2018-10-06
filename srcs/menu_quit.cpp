#include "taag.h"

bool		quit;

static void	funct_quit(void *value)
{
	exit(0);
}

static void	funct_stand(void *value)
{
	quit = true;
}

void		menu_quit(void *value)
{
	SDL_Event	event;
	gui			menu;

	quit = false;

	menu.add_text_button(text_button("Yes", BLACK, menu.get_win_unit().x / 5, menu.get_win_unit() * t_f_vect(4, 6), menu.get_win_unit() * t_f_vect(3, 1), t_color(0.6, 0.6, 0.6), funct_quit));
	menu.add_text_button(text_button("No", BLACK, menu.get_win_unit().x / 5, menu.get_win_unit() * t_f_vect(8, 6), menu.get_win_unit() * t_f_vect(3, 1), t_color(0.6, 0.6, 0.6), funct_stand));

	t_vect coord = menu.get_win_unit() * t_f_vect(3.5, 2.5);
	t_vect size = menu.get_win_unit() * t_f_vect(8, 5);
	draw_border_rectangle(coord, size, t_color(0.6, 0.6, 0.6), t_color(0.5, 0.5, 0.5));

	draw_centred_buffer_sized_text("Did you really wanna quit ?", menu.get_win_unit() * t_f_vect(7.5, 4.5), menu.get_win_unit().x / 4, NORMAL, BLACK);

	menu.draw_self();

	render_screen();

	while (quit == false)
	{
		if (SDL_PollEvent(&(event)) == 1)
		{
			if (event.type == SDL_QUIT)
				funct_quit(NULL);
			else if (event.type == SDL_KEYUP && event.key.keysym.sym == SDLK_ESCAPE)
				quit = true;
			else if (event.type == SDL_MOUSEBUTTONUP)
				menu.test_button_click();
		}
	}
}

void		menu_quit()
{
	SDL_Event	event;
	gui			menu;

	quit = false;

	menu.add_text_button(text_button("Yes", BLACK, menu.get_win_unit().x / 5, menu.get_win_unit() * t_f_vect(4, 6), menu.get_win_unit() * t_f_vect(3, 1), t_color(0.6, 0.6, 0.6), funct_quit));
	menu.add_text_button(text_button("No", BLACK, menu.get_win_unit().x / 5, menu.get_win_unit() * t_f_vect(8, 6), menu.get_win_unit() * t_f_vect(3, 1), t_color(0.6, 0.6, 0.6), funct_stand));

	t_vect coord = menu.get_win_unit() * t_f_vect(3.5, 2.5);
	t_vect size = menu.get_win_unit() * t_f_vect(8, 5);
	draw_border_rectangle(coord, size, t_color(0.6, 0.6, 0.6), t_color(0.5, 0.5, 0.5));

	draw_centred_buffer_sized_text("Did you really wanna quit ?", menu.get_win_unit() * t_f_vect(7.5, 4.5), menu.get_win_unit().x / 4, NORMAL, BLACK);

	menu.draw_self();

	render_screen();

	while (quit == false)
	{
		if (SDL_PollEvent(&(event)) == 1)
		{
			if (event.type == SDL_QUIT)
				funct_quit(NULL);
			else if (event.type == SDL_KEYUP && event.key.keysym.sym == SDLK_ESCAPE)
				quit = true;
			else if (event.type == SDL_MOUSEBUTTONUP)
				menu.test_button_click();
		}
	}
}
