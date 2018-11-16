#include "taag.h"
#include "map_editor_helper.h"

void				menu_map_editor(t_data data)
{
	SDL_Event		event;
	bool			quit = false;
	t_cell			*target = NULL;
	t_gui			gui = t_gui(30, 20);
	string			path;

	t_game_engine board = s_game_engine("ressources/map/test.map");

	create_file_entry(&gui, &path);
	create_save_button(&gui, &board, &path);
	create_load_button(&gui, &board, &path);

	while (quit == false)
	{
		prepare_screen(t_color(0.2, 0.2, 0.2));

		board.draw_board();

		gui.draw_self();

		render_screen(draw_fps);

		if (SDL_PollEvent(&(event)) == 1)
		{
			if (target == NULL)
				control_empty(&event, &gui, &quit, &board, &target);
			else
				control_selected(&event, &gui, &quit, &board, &target);
		}
		SDL_FlushEvents(SDL_MOUSEMOTION, SDL_MOUSEWHEEL);
	}
}
