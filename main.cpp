 #include "template.h"

int main(int argc, char **argv)
{
	if (argc != 1)
		return (1);

	window_initialisation(argv[0]);

	SDL_Event	event;
	bool		quit = false;

	while (quit == false)
	{
		prepare_screen();

		draw_rectangle(t_vect(150, 150), t_vect(15, 150), t_color(0.5, 0.5, 0.5, 1.0));
		draw_rectangle(t_vect(250, 150), t_vect(15, 150), t_color(0.5, 0.5, 0.5, 0.5));
		draw_rectangle(t_vect(350, 150), t_vect(15, 150), t_color(0.5, 0.5, 0.5, 0.0));

		draw_text("ceci est un test", 16, t_vect(130, 170), NORMAL, DARK_RED);

		render_screen();

		if (SDL_PollEvent(&(event)) == 1)
		{
			if (event.type == SDL_QUIT || (event.type == SDL_KEYUP && event.key.keysym.sym == SDLK_ESCAPE))
				exit(0);
		}
	}
	return 0;
}
