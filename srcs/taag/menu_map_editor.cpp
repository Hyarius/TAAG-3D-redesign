#include "taag.h"

void		menu_map_editor(t_data data)
{
	SDL_Event		event;
	bool			quit = false;
	t_gui			gui = t_gui(30, 20);

	while (quit == false)
	{
		prepare_screen();

		gui.draw_self();

		render_screen(draw_fps);

		if (SDL_PollEvent(&(event)) == 1)
		{
			if (event.type == SDL_QUIT)
				menu_quit(&gui);
			else if ((event.type == SDL_KEYUP && event.key.keysym.sym == SDLK_RETURN) || (event.type == SDL_KEYUP && event.key.keysym.sym == SDLK_ESCAPE))
			{
				if (gui.entry != NULL)
				{
					gui.entry = NULL;
					SDL_StopTextInput();
				}
				else if (event.type == SDL_KEYUP && event.key.keysym.sym == SDLK_ESCAPE)
					menu_quit(t_data(2, &gui, &quit));
			}
			else if (event.type == SDL_TEXTINPUT)
				gui.entry->add_text(event.text.text);
			else if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_BACKSPACE && gui.entry != NULL)
				gui.entry->delete_text();
			else if (event.type == SDL_MOUSEBUTTONUP)
				gui.click();
		}
	}
}
