 #include "template.h"

int main(int argc, char **argv)
{
	if (argc != 1)
		return (1);

	window_initialisation(argv[0]);

	SDL_Event	event;
	bool		quit = false;
	int i = 0;

	t_gui		gui;

	int			value = 10;

	gui.object_list.push_back(new s_button(new s_image_button(t_image("ressources/assets/interface/Menu_start.png"), t_vect(0, 0), get_win_size()), NULL, NULL));

	gui.object_list.push_back(new s_iterator(	new s_text_button(	get_text("value"), 	BLACK, 	t_vect(150, 150), 	t_vect(450, 150), 8, 	t_color(0.0, 0.0, 0.0), 	t_color(0.6, 0.6, 0.6)),
												new s_text_button(	get_text("minus"), 		BLACK, 	t_vect(650, 150), 	t_vect(150, 150), 8, 	t_color(0.0, 0.0, 0.0), 	t_color(0.6, 0.6, 0.6)),
												new s_text_button(	NULL, 	BLACK, 	t_vect(850, 150), 	t_vect(250, 150), 8, 	t_color(0.0, 0.0, 0.0), 	t_color(0.6, 0.6, 0.6)),
												new s_text_button(	get_text("plus"), 			BLACK, 	t_vect(1150, 150), 	t_vect(150, 150), 8, 	t_color(0.0, 0.0, 0.0), 	t_color(0.6, 0.6, 0.6)),
												&value, 1, 0, 20));

	while (quit == false)
	{

		prepare_screen(t_color(0.3, 0.3, 0.3));

		gui.draw_self();

		render_screen(true);

		if (SDL_PollEvent(&(event)) == 1)
		{
			if (event.type == SDL_QUIT || (event.type == SDL_KEYUP && event.key.keysym.sym == SDLK_ESCAPE))
				exit(0);
			else if (event.type == SDL_MOUSEBUTTONUP)
				gui.click();
		}
	}
	return 0;
}
