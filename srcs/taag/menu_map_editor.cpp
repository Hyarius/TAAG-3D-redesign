#include "taag.h"
#include "map_editor_helper.h"

extern int			test;

void				menu_map_editor(t_data data)
{
	SDL_Event		event;
	bool			quit = false;
	vector<t_cell *>target;
	t_gui			gui = t_gui(30, 20);
	string			path;

	t_game_engine board = s_game_engine("ressources/map/test.map");

	create_file_entry(&gui, &path);
	create_save_button(&gui, &board, &path);
	create_load_button(&gui, &board, &path);
	create_generate_button(&gui, &board);

	while (quit == false)
	{
		prepare_screen(t_color(0.2, 0.2, 0.2));

		board.draw_board();

		gui.draw_self();

		render_screen(draw_fps);

		if (SDL_PollEvent(&(event)) == 1)
		{
			if (target.size() == 0)
				control_empty(&event, &gui, &quit, &board, &target);
			else
				control_selected(&event, &gui, &quit, &board, &target);
			if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_f)
				test = (test == 0 ? 1 : 0);
		}
		SDL_FlushEvents(SDL_MOUSEMOTION, SDL_MOUSEWHEEL);
	}
}
