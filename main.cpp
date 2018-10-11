 #include "template.h"

static void		test(t_data p_data)
{
	if (p_data.data != NULL)
		printf("Data content : [%s] = %d / %d\n", ((string *)p_data.data[0])->c_str(), *((int *)p_data.data[1]), *((int *)p_data.data[2]));
	else if (p_data.data == NULL)
	{
		printf("Data is empty\n");
	}
}

int main(int argc, char **argv)
{
	if (argc != 1)
		return (1);

	window_initialisation(argv[0]);

	SDL_Event	event;
	bool		quit = false;

	t_gui		gui;

	while (quit == false)
	{
		prepare_screen(t_color(0.3, 0.3, 0.3));

		gui.draw_self();

		render_screen();

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
