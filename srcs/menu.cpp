#include "taag.h"

void		play()
{
	printf("Enter play mode\n");
}

void		menu_spell_editor()
{
	printf("Enter spell editor\n");
}

void		menu_map_editor()
{
	printf("Enter map editor\n");
}

void		menu_shop()
{
	printf("Enter shop\n");
}

void		menu_option()
{
	printf("Enter option menu\n");
}

void		menu_start()
{
	SDL_Event	event;
	bool		quit = false;

	gui			menu;

	menu.add_image(image("ressources/assets/interface/menu_start.png", t_vect(0, 0), get_win_size()));
	menu.add_text_button(text_button("Play", BLACK, menu.get_win_unit().x / 2.5, menu.get_win_unit() * t_vect(10, 1), menu.get_win_unit() * t_vect(4, 1), t_color(0.6, 0.6, 0.6), t_color(0.4, 0.4, 0.4), play));
	menu.add_text_button(text_button("Player editor", BLACK, menu.get_win_unit().x / 5, menu.get_win_unit() * t_f_vect(10, 2.5), menu.get_win_unit() * t_vect(4, 1), t_color(0.6, 0.6, 0.6), menu_player_editor));
	menu.add_text_button(text_button("Spell editor", BLACK, menu.get_win_unit().x / 5, menu.get_win_unit() * t_f_vect(10, 4), menu.get_win_unit() * t_vect(4, 1), t_color(0.6, 0.6, 0.6), menu_spell_editor));
	menu.add_text_button(text_button("Map editor", BLACK, menu.get_win_unit().x / 5, menu.get_win_unit() * t_f_vect(10, 5.5), menu.get_win_unit() * t_vect(4, 1), t_color(0.6, 0.6, 0.6), menu_map_editor));
	menu.add_text_button(text_button("Shop", BLACK, menu.get_win_unit().x / 5, menu.get_win_unit() * t_f_vect(10, 7), menu.get_win_unit() * t_vect(4, 1), t_color(0.6, 0.6, 0.6), menu_shop));
	menu.add_text_button(text_button("Option", BLACK, menu.get_win_unit().x / 5, menu.get_win_unit() * t_f_vect(10, 8.5), menu.get_win_unit() * t_f_vect(1.8, 1), t_color(0.6, 0.6, 0.6), menu_option));
	menu.add_text_button(text_button("Quit", BLACK, menu.get_win_unit().x / 5, menu.get_win_unit() * t_f_vect(12.2, 8.5), menu.get_win_unit() * t_f_vect(1.8, 1), t_color(0.6, 0.6, 0.6), menu_quit));

	while (quit == false)
	{
		prepare_screen();

		menu.draw_self();

		render_screen();

		if (SDL_PollEvent(&(event)) == 1)
		{
			if (event.type == SDL_QUIT || event.type == SDL_KEYUP && event.key.keysym.sym == SDLK_ESCAPE)
				menu_quit();
			if (event.type == SDL_MOUSEBUTTONUP)
				menu.test_click();
		}
	}
}