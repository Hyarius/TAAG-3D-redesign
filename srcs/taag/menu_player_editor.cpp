#include "taag.h"

void		menu_player_editor(t_data data)
{
	SDL_Event		event;
	bool			quit = false;
	t_gui			gui = t_gui(30, 20);

	t_actor			player = s_actor("Hyarius", 1, 15, s_stat(t_value(45), t_value(6), t_value(3), t_value(100), t_element(3, 3), t_element(3, 3)));

	string			saved_path = "ressources/actor/test.act";

	gui.add(new s_button(new s_image_button( t_image(t_color(0.7, 0.7, 0.7)), t_vect(0, 0), get_win_size()), NULL, NULL));

	int i = 1;

	create_entry_name(&gui, &player, i++);
	create_level_iterator(&gui, &player, i++);
	create_pool_iterator(&gui, &player, i++);
	create_health_iterator(&gui, &player, i++);
	create_pa_iterator(&gui, &player, i++);
	create_pm_iterator(&gui, &player, i++);
	create_init_iterator(&gui, &player, i++);
	create_atk_phy_iterator(&gui, &player, i++);
	create_atk_mag_iterator(&gui, &player, i++);
	create_def_phy_iterator(&gui, &player, i++);
	create_def_mag_iterator(&gui, &player, i++);
	create_save_button(&gui, &player, i++, &saved_path);

	//save_actor(t_data(2, &player, "ressources/actor/test.act"));

	while (quit == false)
	{
		prepare_screen();

		gui.draw_self();

		render_screen(true);

		if (SDL_PollEvent(&(event)) == 1)
		{
			if (event.type == SDL_QUIT)
				menu_quit(t_data(2, &gui, &quit));
				if ((event.type == SDL_KEYUP && event.key.keysym.sym == SDLK_RETURN) || (event.type == SDL_KEYUP && event.key.keysym.sym == SDLK_ESCAPE))
				{
					if (gui.entry != NULL)
					{
						gui.entry = NULL;
						SDL_StopTextInput();
					}
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
