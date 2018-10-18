#include "taag.h"

void		menu_player_editor(t_data data)
{
	SDL_Event	event;
	bool		quit = false;

	t_gui	gui;

	gui.add(new s_button(new s_image_button(//image de fond
			t_image(t_color(0.7, 0.7, 0.7)),
			t_vect(0, 0), get_win_size()),
			NULL, NULL));

	while (quit == false)
	{
		prepare_screen();

		gui.draw_self();

		render_screen(true);

		if (SDL_PollEvent(&(event)) == 1)
		{
			if (event.type == SDL_QUIT || (event.type == SDL_KEYUP && event.key.keysym.sym == SDLK_ESCAPE))
				menu_quit(t_data(2, &gui, &quit));
			else if (event.type == SDL_MOUSEBUTTONUP)
				gui.click();
		}
	}
}
