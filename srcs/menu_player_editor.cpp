#include "taag.h"

void		menu_player_editor()
{
	SDL_Event	event;
	bool		quit = false;

	gui			menu;

	t_color		color = t_color(0.6, 0.6, 0.6);
	t_color		color2 = t_color(0.4, 0.4, 0.4);

	menu.add_text_box(text_box("Enter your name", DARK_GREY, menu.get_win_unit().x / 5, menu.get_win_unit() * t_f_vect(0.5, 1), menu.get_win_unit() * t_f_vect(5, 0.5), color, color2));

	int value = 15;

	menu.add_iterator_box(iterator_box("Petit poney", &value, menu.get_win_unit() * t_f_vect(0.5, 2), menu.get_win_unit() * t_f_vect(5, 0.5), color, color2 ));

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
			{
				if (value > 0)
					menu.test_iterator_click_minus();
				if (value < 30)
					menu.test_iterator_click_plus();
				menu.test_click();
			}
			else if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_BACKSPACE)
				menu.get_selected_text_box()->delete_text();
			else if (event.type == SDL_TEXTINPUT)
				menu.get_selected_text_box()->add_text(event.text.text);
		}
	}
}
