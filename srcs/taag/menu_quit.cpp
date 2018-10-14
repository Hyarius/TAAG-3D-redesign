#include "taag.h"

static void		set_quit(t_data data)
{
	*((bool *)data.data[0]) = true;
}

void		menu_quit(t_data data)
{
	SDL_Event	event;
	bool		quit = false;
	t_gui		back_gui = t_gui(*((t_gui *)(data.data[0])));
	t_color		color[2] = {t_color(0.6, 0.6, 0.6), t_color(0.8, 0.8, 0.8)};

	t_gui		gui;

	gui.add(new s_button(new s_text_button(//button did you wanna quit
						get_text("quit ?"), DARK_GREY, //text info
						gui.unit * t_vect(4, 2), gui.unit * t_vect(7, 5), 8, //object info
						color[0], color[1]),
						NULL, NULL));

	t_vect *tmp = &(((s_button *)(gui.object_list[0]))->button->coord[2]);
	*tmp = *tmp - (gui.unit * t_vect(0, 0.5));

	gui.add(new s_button(new s_text_button(//button yes
						get_text("yes"), DARK_GREY, //text info
						gui.unit * t_vect(5.25, 4.75), gui.unit * t_vect(2, 1), 8, //object info
						color[0], color[1]),
						NULL, NULL));

	gui.add(new s_button(new s_text_button(//button no
						get_text("no"), DARK_GREY, //text info
						gui.unit * t_vect(7.75, 4.75), gui.unit * t_vect(2, 1), 8, //object info
						color[0], color[1]),
						NULL, NULL));

	while (quit == false)
	{
		prepare_screen();

		back_gui.draw_self();
		gui.draw_self();

		render_screen(true);

		if (SDL_PollEvent(&(event)) == 1)
		{
			if (event.type == SDL_QUIT || (event.type == SDL_KEYUP && event.key.keysym.sym == SDLK_ESCAPE))
				quit = true;
			else if (event.type == SDL_MOUSEBUTTONUP)
				gui.click();
		}
	}
	printf("menu quit\n");
}
