#include "taag.h"

void			stand(t_data data)
{
	*((bool *)data.data[0]) = true;
}

void			quit(t_data data)
{
	if (data.data[0] == NULL)
		exit(0);
	else
		*((bool *)data.data[0]) = true;;
		*((bool *)data.data[1]) = true;;
}

void			menu_quit(t_data data)
{
	SDL_Event	event;
	bool		continu = false;

	t_gui		gui;

	gui.add(GUI_OBJ_ID, new s_button(new s_text_button(//button did you wanna quit
						get_text("quit ?"), DARK_GREY, //text info
						gui.unit * t_vect(4, 2), gui.unit * t_vect(7, 5), 8, //object info
						color[0], color[1]),
						NULL, NULL));

	t_vect *tmp = &(((s_button *)(gui.object_list[GUI_OBJ_ID][0]))->button->image_coord);
	*tmp = *tmp - (gui.unit * t_vect(0, 0.5));

	gui.add(GUI_OBJ_ID, new s_button(new s_text_button(//button yes
						get_text("yes"), DARK_GREY, //text info
						gui.unit * t_vect(4.25, 5.25), gui.unit * t_vect(3, 1.5), 8, //object info
						color[0], color[1]),
						quit, (data.data.size() == 1 ? NULL : t_data(2, data.data[1], &continu))));

	gui.add(GUI_OBJ_ID, new s_button(new s_text_button(//button no
						get_text("no"), DARK_GREY, //text info
						gui.unit * t_vect(7.75, 5.25), gui.unit * t_vect(3, 1.5), 8, //object info
						color[0], color[1]),
						stand, &continu));

	while (continu == false)
	{
		prepare_screen();

		if (data.data.size() != 0)
		{
			if (data.data.size() == 3)
				(*((t_game_engine *)(data.data[2]))).draw_board();
			(*((t_gui *)(data.data[0]))).draw_self();
		}
		gui.draw_self();

		render_screen(draw_fps);

		if (SDL_PollEvent(&(event)) == 1)
		{
			if (event.type == SDL_QUIT || (event.type == SDL_KEYUP && event.key.keysym.sym == SDLK_ESCAPE))
				continu = true;
			else if (event.type == SDL_MOUSEBUTTONUP)
				gui.click();
		}
	}
}
