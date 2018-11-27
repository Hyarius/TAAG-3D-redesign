#include "taag.h"
#include "map_editor_helper.h"

void				menu_map_editor(t_data data)
{
	SDL_Event		event;
	bool			quit = false;
	vector<t_cell *>target;
	t_gui			gui = t_gui(30, 20);
	string			path;

	t_game_engine board = s_game_engine();

	create_file_entry(&gui, &path);
	create_save_button(&gui, &board, &path);
	create_load_button(&gui, &board, &path);
	create_generate_button(&gui, &board);
	create_erase_button(&gui, &path);

	create_object_editor(&gui, );

	create_spawn_selector_button(&gui, &target);

	create_swap_button(&gui, &target);

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
		}
		SDL_FlushEvents(SDL_MOUSEMOTION, SDL_MOUSEWHEEL);
	}
}
