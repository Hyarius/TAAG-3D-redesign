#include "taag.h"

void		create_player_selector_red(t_gui *gui, vector <t_actor> *actor_red)
{
	gui->add(GUI_OBJ_ID, new s_button(new t_text_button(get_text("red team comp"), DARK_GREY, //text info
									gui->unit * 1, gui->unit * t_vect(6, 18), 8, //object info
									color[0], color[1]), NULL, NULL));
}

void		create_player_selector_blue(t_gui *gui, vector <t_actor> *actor_blue)
{
	gui->add(GUI_OBJ_ID, new s_button(new t_text_button(get_text("blue team comp"), DARK_GREY, //text info
									gui->unit * t_vect(23, 1), gui->unit * t_vect(6, 18), 8, //object info
									color[0], color[1]), NULL, NULL));
}

void		menu_play(t_data data)
{
	SDL_Event		event;
	bool			quit = false;
	t_gui			gui = t_gui(30, 20);
	vector <t_actor>	actor_red;
	vector <t_actor>	actor_blue;

	actor_red.resize(8);
	actor_blue.resize(8);

	gui.add(GUI_OBJ_ID, new s_button(new s_image_button( t_image(t_color(0.2, 0.2, 0.2)), t_vect(0, 0), get_win_size()), NULL, NULL));

	create_player_selector_red(&gui, &actor_red);
	create_player_selector_blue(&gui, &actor_blue);

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
				menu_quit(t_data(2, &gui, &quit));
			else if (event.type == SDL_TEXTINPUT)
				gui.entry->add_text(event.text.text);
			else if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_BACKSPACE && gui.entry != NULL)
				gui.entry->delete_text();
			else if (event.type == SDL_MOUSEBUTTONUP && event.button.button == SDL_BUTTON_LEFT)
				gui.click();
		}
	}
}
