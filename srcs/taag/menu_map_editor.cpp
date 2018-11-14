#include "taag.h"
#include "base_value.h"

void				menu_map_editor(t_data data)
{
	SDL_Event		event;
	bool			quit = false;

	t_game_engine board = s_game_engine("ressources/map/test.map");

	while (quit == false)
	{
		prepare_screen(t_color(0.2, 0.2, 0.2));

		board.draw_board();

		render_screen(draw_fps);

		if (SDL_PollEvent(&(event)) == 1)
		{
			if (event.type == SDL_QUIT || (event.type == SDL_KEYUP &&
				event.key.keysym.sym == SDLK_ESCAPE))
				quit = true;
			else if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_UP)
				board.handle_rot(90);
			else if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_DOWN)
				board.handle_rot(-90);
			else if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_LEFT)
				board.handle_rot(2);
			else if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_RIGHT)
				board.handle_rot(-2);
			else if (event.type == SDL_MOUSEMOTION && event.button.button == SDL_BUTTON_MIDDLE)
				board.handle_rot(0 - event.motion.xrel);
			else if (event.type == SDL_MOUSEMOTION && event.button.button == SDL_BUTTON_LEFT)
				board.camera->handle_move(event.motion.xrel, event.motion.yrel);
			else if (event.type == SDL_MOUSEWHEEL)
			{
				if (event.wheel.y > 0)
					board.camera->handle_zoom(1.1);
        		else if (event.wheel.y < 0)
					board.camera->handle_zoom(0.9);
			}
		}
		SDL_FlushEvent(SDL_KEYDOWN);
		SDL_FlushEvent(SDL_MOUSEBUTTONDOWN);
		SDL_FlushEvents(SDL_MOUSEMOTION, SDL_MOUSEWHEEL);
	}
}
