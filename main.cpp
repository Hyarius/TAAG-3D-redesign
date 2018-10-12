 #include "template.h"

static void		test(t_data p_data)
{
	size_t i = 0;

	if (p_data.data.size() != 0)
	{
		printf("Data content : ");
		while (i < p_data.data.size())
		{
			if (i != 0)
				printf(" - ");
			printf("[%s]", ((string *)p_data.data[i])->c_str());
			i++;
		}
		printf("\n");
	}
	else
		printf("Data is empty\n");
}

int main(int argc, char **argv)
{
	if (argc != 1)
		return (1);

	window_initialisation(argv[0]);

	SDL_Event	event;
	bool		quit = false;
	int i = 0;

	t_gui		gui;

	string		text_button = "yolo";
	string		text = "AMAZING";
	string		str_content = "Content";
	string		test1 = "ceci est un test";

	t_data		data = t_data(3, &str_content, &text, &test1);

	gui.object_list.push_back(new s_button(new s_text_button(	&text_button, BLACK, t_vect(150, 150), t_vect(150, 150), 8, t_color(0.0, 0.0, 0.0), t_color(0.6, 0.6, 0.6)), test, NULL));


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
