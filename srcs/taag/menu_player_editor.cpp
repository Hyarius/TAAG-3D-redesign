#include "taag.h"
#include "player_editor_helper.h"

void		menu_player_editor(t_data data)
{
	SDL_Event		event;
	bool			quit = false;
	t_gui			gui = t_gui(30, 20);

	string			path;
	t_actor			player;

	string			file_name;

	gui.add(new s_button(new s_image_button( t_image(t_color(0.7, 0.7, 0.7)), t_vect(0, 0), get_win_size()), NULL, NULL));

	int i = 0;
	set_b_value();

	create_file_entry(&gui, &file_name, i++);
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
	create_save_button(&gui, &player, i, &file_name);
	create_load_button(&gui, &player, i++, &file_name);

	//create_spell_cards(&gui, &player);

	while (quit == false)
	{
		prepare_screen();

		gui.draw_self();

		render_screen(true);

		if (SDL_PollEvent(&(event)) == 1)
		{
			if (event.type == SDL_QUIT)
				menu_quit(t_data(2, &gui, &quit));
			else if ((event.type == SDL_KEYUP && event.key.keysym.sym == SDLK_RETURN) || (event.type == SDL_KEYUP && event.key.keysym.sym == SDLK_ESCAPE))
			{
				if (gui.entry != NULL)
				{
					gui.entry = NULL;
					SDL_StopTextInput();
				}
				else
					quit = true;
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
