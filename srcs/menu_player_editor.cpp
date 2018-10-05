#include "taag.h"

void		menu_player_editor()
{
	SDL_Event	event;
	bool		quit = false;

	gui			menu;

	t_color		color = t_color(0.4, 0.4, 0.4);
	t_color		color2 = t_color(0.6, 0.6, 0.6);

	player target = player(t_stat(t_value(50), t_value(7), t_value(4), t_element(3, 3), t_element(3, 3)), 0);

	menu.add_list_box(list_box("Heroes selected : ", " - Create a new char - ", menu.get_win_unit() * t_f_vect(0.5, 0.5), menu.get_win_unit() * t_f_vect(5, 0.5), color, color2, list_files));

	menu.add_text_box(text_box("Enter your name", DARK_GREY, menu.get_win_unit().x / 5, menu.get_win_unit() * t_f_vect(0.5, 1.2), menu.get_win_unit() * t_f_vect(5, 0.5), color, color2));


	menu.add_iterator_box(iterator_box("HP : 1 pts", &(target.get_stat()->hp.max), 10, 150, 10, menu.get_win_unit() * t_f_vect(0.5, 2), menu.get_win_unit() * t_f_vect(5, 0.5), color, color2 ));
	menu.add_iterator_box(iterator_box("PA : 3 pts", &target.get_stat()->pa.max, 5, 12, 1, menu.get_win_unit() * t_f_vect(0.5, 2.7), menu.get_win_unit() * t_f_vect(5, 0.5), color, color2 ));
	menu.add_iterator_box(iterator_box("PM : 2 pts", &target.get_stat()->pm.max, 3, 8, 1, menu.get_win_unit() * t_f_vect(0.5, 3.4), menu.get_win_unit() * t_f_vect(5, 0.5), color, color2 ));
	menu.add_iterator_box(iterator_box("Physical attack : 2 pts", &target.get_stat()->phy.atk, 1, 10, 1, menu.get_win_unit() * t_f_vect(0.5, 4.1), menu.get_win_unit() * t_f_vect(5, 0.5), color, color2 ));
	menu.add_iterator_box(iterator_box("Magical attack : 2 pts", &target.get_stat()->mag.atk, 1, 10, 1, menu.get_win_unit() * t_f_vect(0.5, 4.8), menu.get_win_unit() * t_f_vect(5, 0.5), color, color2 ));
	menu.add_iterator_box(iterator_box("Physical defense : 2 pts", &target.get_stat()->phy.def, 1, 10, 1, menu.get_win_unit() * t_f_vect(0.5, 5.5), menu.get_win_unit() * t_f_vect(5, 0.5), color, color2 ));
	menu.add_iterator_box(iterator_box("Magical defense : 2 pts", &target.get_stat()->mag.def, 1, 10, 1, menu.get_win_unit() * t_f_vect(0.5, 6.2), menu.get_win_unit() * t_f_vect(5, 0.5), color, color2 ));
	menu.add_iterator_box(iterator_box("sprite :", target.get_sprite(), 0, 12, 1, menu.get_win_unit() * t_f_vect(0.5, 6.9), menu.get_win_unit() * t_f_vect(5, 0.5), color, color2 ));

	while (quit == false)
	{
		prepare_screen(t_color(0.8, 0.8, 0.8));

		menu.draw_self();

		render_screen();

		if (menu.get_selected_text_box() != NULL)
			SDL_StartTextInput();
		else
			SDL_StopTextInput();

		if (SDL_PollEvent(&(event)) == 1)
		{
			if (event.type == SDL_QUIT)
				menu_quit();
			else if (event.type == SDL_KEYUP && event.key.keysym.sym == SDLK_ESCAPE)
			{
				if (menu.get_selected_text_box() != NULL)
					menu.set_selected_text_box(NULL);
				else
					quit = true;
			}
			else if (event.type == SDL_MOUSEBUTTONUP)
				menu.test_click();
			else if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_BACKSPACE && menu.get_selected_text_box() != NULL)
				menu.get_selected_text_box()->delete_text();
			else if (event.type == SDL_TEXTINPUT && menu.get_selected_text_box() != NULL)
				menu.get_selected_text_box()->add_text(event.text.text);
		}
	}
}
