#include "taag.h"

void		menu_player_editor()
{
	SDL_Event	event;
	bool		quit = false;

	gui			menu;

	t_color		color = t_color(0.6, 0.6, 0.6);
	t_color		color2 = t_color(0.4, 0.4, 0.4);

	menu.add_text_box(text_box("Enter your name", DARK_GREY, menu.get_win_unit().x / 5, menu.get_win_unit() * t_vect(1, 1), menu.get_win_unit() * t_vect(4, 1), color, color2));

	while (quit == false)
	{
		prepare_screen(t_color(0.8, 0.8, 0.8));

		menu.draw_self();

		render_screen();

		if (menu.get_selected_text_box() != NULL)
			SDL_StartTextInput();

		if (SDL_PollEvent(&(event)) == 1)
		{
			if (event.type == SDL_QUIT)
				menu_quit();
			else if (event.type == SDL_KEYUP && event.key.keysym.sym == SDLK_ESCAPE)
				quit = true;
			else if (event.type == SDL_MOUSEBUTTONUP)
				menu.test_click();
			else if (event.type == SDL_KEYUP && event.key.keysym.sym == SDLK_BACKSPACE)
				menu.get_selected_text_box()->delete_text();
			else if (event.type == SDL_TEXTINPUT)
				menu.get_selected_text_box()->add_text(event.text.text);
		}
	}
}