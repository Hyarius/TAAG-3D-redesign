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

	t_gui					gui;

	gui.object_list.push_back(new t_text_button("ceci est un test", RED, t_vect(150, 150), t_vect(450, 60), 6, t_color(0.6, 0.4, 0.2), t_color(1.0, 1.0, 1.0)));
	gui.object_list.push_back(new t_text_button("ceci est un autre test", RED, t_vect(150, 450), t_vect(450, 60), 6, t_color(0.0, 0.0, 0.0), t_color(0.8, 0.8, 0.8)));
	gui.object_list.push_back(new t_image_button(t_image("ressources/assets/interface/GUI_shortcut.png"), t_vect(150, 750), t_vect(450, 60)));
	gui.object_list[2]->set_funct_param(test, NULL);

	while (quit == false)
	{
		prepare_screen(t_color(0.3, 0.3, 0.3));

		gui.draw_self();

		render_screen();

		if (SDL_PollEvent(&(event)) == 1)
		{
			if (event.type == SDL_QUIT || (event.type == SDL_KEYUP && event.key.keysym.sym == SDLK_ESCAPE))
				exit(0);
			if (event.type == SDL_MOUSEBUTTONUP)
				gui.click();
		}
	}
	return 0;
}
