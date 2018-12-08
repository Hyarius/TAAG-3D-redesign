#include "taag.h"

static void		quit_choose_sprite(t_data data)
{
	int				*index = (int *)(data.data[0]);
	t_vect			*selected = (t_vect *)(data.data[1]);
	int				*tmp_index = (int *)(data.data[2]);
	t_vect			*tmp_selected = (t_vect *)(data.data[3]);
	bool			*continu = (bool *)(data.data[4]);

	*index = *tmp_index;
	*selected = *tmp_selected;
	*continu = true;
}

void			menu_choose_sprite(t_data data)
{
	int				*index = (int *)(data.data[0]);
	t_vect			*selected = (t_vect *)(data.data[1]);
	t_vect			*increment = (t_vect *)(data.data[2]);
	SDL_Event		event;
	bool			continu = false;

	t_gui	gui = t_gui(30, 20);

	s_button *button = new s_button(new s_text_button(//button did you wanna quit
				NULL, DARK_GREY, //text info
				gui.unit * t_vect(2, 2), gui.unit * t_vect(26, 16), 8, //object info
				color[0], color[1]),
				NULL, NULL);
	gui.add(GUI_OBJ_ID, button);

	int			tmp_index = *index;
	t_vect		tmp_selected = t_vect(0, 0);
	size_t		i = 0;
	t_vect		coord = t_vect(0, 0);
	t_vect		size = t_vect(4 * gui.unit.y / gui.unit.x, 4);
	double		x = (24 - (size.x * 6)) / 5;
	double		y = (14 - (size.y * 3)) / 2;
	t_vect		space = t_vect(x, y);

	while (coord.y + size.y < 15)
	{
		t_tileset_button *tile_button = new s_tileset_button(NULL, BLACK,
				&tile_list, &tmp_index, tmp_selected,
				gui.unit * (coord + t_vect(3, 3)), gui.unit * size, 8);
		button = new s_button(tile_button,
				quit_choose_sprite, t_data(5, data.data[0], data.data[1], &tmp_index, &(tile_button->selected), &continu));
		gui.add(SPRITE_IMAGE_ID, button);
		tmp_selected.x += increment->x;
		if (tmp_selected.x >= tile_list[*index]->nb_sprite.x)
			tmp_selected = t_vect(0, tmp_selected.y + increment->y);
		coord.x += size.x + space.x;
		if (coord.x + size.x > 25)
			coord = t_vect(0, coord.y + size.y + space.y);
		i++;
	}

	while (continu == false)
	{
		prepare_screen(t_color(0.7, 0.7, 0.7));

		if (data.data.size() != 0)
			(*((t_gui *)(data.data[3]))).draw_self();
		gui.draw_self();

		render_screen(draw_fps);

		if (SDL_PollEvent(&(event)) == 1)
		{
			if (event.type == SDL_QUIT)
				menu_quit(&gui);
			else if (event.type == SDL_KEYUP && event.key.keysym.sym == SDLK_ESCAPE)
				continu = true;
			else if (event.type == SDL_MOUSEBUTTONUP && event.button.button == SDL_BUTTON_LEFT)
				gui.click();
			if ((event.type == SDL_MOUSEWHEEL && event.wheel.y > 0) ||
				(event.type == SDL_KEYUP && event.key.keysym.sym == SDLK_UP))
				tmp_index = (tmp_index - 1 < 0 ? tile_list.size() - 1 : tmp_index - 1);
			else if ((event.type == SDL_MOUSEWHEEL && event.wheel.y < 0) ||
				(event.type == SDL_KEYUP && event.key.keysym.sym == SDLK_DOWN))
				tmp_index = (tmp_index + 1 >= (int)(tile_list.size()) ? 0 : tmp_index + 1);
		}
	}
}
