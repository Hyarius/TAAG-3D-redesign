#include "taag.h"
#include "base_value.h"

void				menu_map_editor(t_data data)
{
	SDL_Event		event;
	bool			quit = false;

	t_game_engine board = s_game_engine("ressources/map/test.map");

	while (quit == false)
	{
		prepare_screen(t_color(0.5, 0.5, 0.5));
		
		board.draw_board();

		render_screen(draw_fps);

		if (SDL_PollEvent(&(event)) == 1)
		{
			if (event.type == SDL_QUIT || (event.type == SDL_KEYUP &&
				event.key.keysym.sym == SDLK_ESCAPE))
				quit = true;
		}
	}
}
