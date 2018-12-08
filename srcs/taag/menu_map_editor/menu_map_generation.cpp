#include "taag.h"

void			quit_generate(t_data data)
{
	bool *continu = ((bool *)(data.data[0]));
	t_game_engine *board = ((t_game_engine *)(data.data[1]));
	int *size_x = ((int *)(data.data[2]));
	int *size_y = ((int *)(data.data[3]));
	t_node *node = node_list[*((int *)(data.data[4]))];

	if (board->board == NULL)
	{
		board->board = new t_game_board(map_generator(*size_x, *size_y, node));
		board->camera = new s_camera(60, 0, 45);
		board->camera->target = t_vect(board->board->map_size.x / 2.0, board->board->map_size.y / 2.0);
	}
	else
		*(board->board) = map_generator(*size_x, *size_y, node);
	board->calc_camera();
	*continu = true;
}

void			menu_map_generation(t_data data)
{
	SDL_Event	event;
	bool		continu = false;
	int			size_x = 10;
	int			size_y = 10;
	int			node_type = 0;

	t_gui		gui = t_gui(30, 20);

	gui.add(GUI_OBJ_ID, new s_button(new s_text_button(//button did you wanna quit
						get_text("generate ?"), DARK_GREY, //text info
						gui.unit * t_vect(6, 3), gui.unit * t_vect(18, 14), 15, //object info
						color[0], color[1]),
						NULL, NULL));

	t_vect *tmp = &(((s_button *)(gui.object_list[GUI_OBJ_ID][0]))->button->image_coord);
	*tmp = *tmp - (gui.unit * t_vect(0, 4));

	gui.add(ITERATOR_ID, new s_iterator(
				new t_text_button(get_text("map size x"), DARK_GREY, //health
					gui.unit * t_vect(7.5, 8), gui.unit * t_vect(7, 1), 3,
					color[0], color[3]),
				new t_text_button(get_text("<"), DARK_GREY, //minus button
					gui.unit * t_vect(15, 8), gui.unit * t_vect(1, 1), 3,
					color[0], color[3]),
				new t_text_button(NULL, DARK_GREY, //value button
					gui.unit * t_vect(16.5, 8), gui.unit * t_vect(1, 1), 3,
					color[0], color[3]),
				new t_text_button(get_text(">"), DARK_GREY, //plus button
					gui.unit * t_vect(18, 8), gui.unit * t_vect(1, 1), 3,
					color[0], color[3]),
				&size_x, 1, 1, 50,
				NULL, 0, NULL));

	gui.add(ITERATOR_ID, new s_iterator(
				new t_text_button(get_text("map size y"), DARK_GREY, //health
					gui.unit * t_vect(7.5, 10), gui.unit * t_vect(7, 1), 3,
					color[0], color[3]),
				new t_text_button(get_text("<"), DARK_GREY, //minus button
					gui.unit * t_vect(15, 10), gui.unit * t_vect(1, 1), 3,
					color[0], color[3]),
				new t_text_button(NULL, DARK_GREY, //value button
					gui.unit * t_vect(16.5, 10), gui.unit * t_vect(1, 1), 3,
					color[0], color[3]),
				new t_text_button(get_text(">"), DARK_GREY, //plus button
					gui.unit * t_vect(18, 10), gui.unit * t_vect(1, 1), 3,
					color[0], color[3]),
				&size_y, 1, 5, 50,
				NULL, 0, NULL));

	t_text_button *button0 = new t_text_button(get_text("node type"), DARK_GREY, //health
					gui.unit * t_vect(7.5, 12), gui.unit * t_vect(7, 1), 3,
					color[0], color[3]);
	t_text_button *button1 = new t_text_button(get_text("<"), DARK_GREY, //minus button
					gui.unit * t_vect(15, 12), gui.unit * t_vect(1, 1), 3,
					color[0], color[3]);
	t_text_button *button2 = new t_text_button(NULL, DARK_GREY, //value button
					gui.unit * t_vect(16.5, 12), gui.unit * t_vect(1, 1), 3,
					color[0], color[3]);
	t_text_button *button3 = new t_text_button(get_text(">"), DARK_GREY, //plus button
					gui.unit * t_vect(18, 12), gui.unit * t_vect(1, 1), 3,
					color[0], color[3]);


	t_node_selector *node_selector = new t_node_selector(button0, button1, button2, button3, &node_type, &gui);
	gui.add(SPRITE_SELECTOR_ID, node_selector);

	gui.add(GUI_OBJ_ID, new s_button(new s_text_button(//button yes
						get_text("okay"), DARK_GREY, //text info
						gui.unit * t_vect(7.5, 14), gui.unit * t_vect(3, 1.5), 8, //object info
						color[0], color[1]),
						quit_generate, t_data(5, &continu, data.data[2], &size_x, &size_y, &node_type)));

	gui.add(GUI_OBJ_ID, new s_button(new s_text_button(//button no
						get_text("cancel"), DARK_GREY, //text info
						gui.unit * t_vect(16, 14), gui.unit * t_vect(3, 1.5), 8, //object info
						color[0], color[1]),
						stand, &continu));

	while (continu == false)
	{
		prepare_screen();

		if (data.data.size() != 0)
		{
			(*((t_gui *)(data.data[0]))).draw_self();
			if (data.data.size() == 3)
				(*((t_game_engine *)(data.data[2]))).draw_board();
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
