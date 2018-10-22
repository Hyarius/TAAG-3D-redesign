#include "taag.h"

void		menu_start()
{
	SDL_Event	event;
	bool		bool_quit = false;

	t_gui		gui;

	t_color		color[2] = {t_color(0.3, 0.3, 0.3), t_color(0.5, 0.5, 0.5)};

	gui.add(new s_button(new s_image_button(//image de fond
			t_image("ressources/assets/interface/Menu_start.png"),
			t_vect(0, 0), get_win_size()),
			NULL, NULL));
	gui.add(new s_button(new s_text_button(//button play
						get_text("play"), LIGHT_GREY, //text info
						gui.unit * t_vect(10, 1), gui.unit * t_vect(4, 1), 8, //object info
						color[1], color[0]),
						menu_play, NULL));
	gui.add(new s_button(new s_text_button(//button player editor
						get_text("player_editor"), DARK_GREY, //text info
						gui.unit * t_vect(10, 2.75), gui.unit * t_vect(4, 1), 8, //object info
						color[0], color[1]),
						menu_player_editor, NULL));
	gui.add(new s_button(new s_text_button(//button map editor
						get_text("map_editor"), DARK_GREY, //text info
						gui.unit * t_vect(10, 4.5), gui.unit * t_vect(4, 1), 8, //object info
						color[0], color[1]),
						menu_map_editor, NULL));
	gui.add(new s_button(new s_text_button(//button shop
						get_text("shop"), DARK_GREY, //text info
						gui.unit * t_vect(10, 6.25), gui.unit * t_vect(4, 1), 8, //object info
						color[0], color[1]),
						menu_shop, NULL));
	gui.add(new s_button(new s_text_button(//button option
						get_text("option"), DARK_GREY, //text info
						gui.unit * t_vect(10, 8), gui.unit * t_vect(1.75, 1.0), 8, //object info
						color[0], color[1]),
						menu_option, &gui));
	gui.add(new s_button(new s_text_button(//button quit
						get_text("quit"), DARK_GREY, //text info
						gui.unit * t_vect(12.25, 8), gui.unit * t_vect(1.75, 1.0), 8, //object info
						color[0], color[1]),
						menu_quit, &gui));

	while (bool_quit == false)
	{
		prepare_screen();

		gui.draw_self();

		render_screen();

		if (SDL_PollEvent(&(event)) == 1)
		{
			if (event.type == SDL_QUIT || (event.type == SDL_KEYUP && event.key.keysym.sym == SDLK_ESCAPE))
				menu_quit(&gui);
			else if (event.type == SDL_MOUSEBUTTONUP)
				gui.click();
		}
	}
}
