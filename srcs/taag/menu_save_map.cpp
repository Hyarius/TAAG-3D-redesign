#include "taag.h"
#include "player_editor_helper.h"

static void		quit_save(t_data data)
{
	save_map(t_data(2, data.data[0], data.data[1]));
	bool *continu = (bool *)(data.data[2]);
	*continu = true;
}

void			menu_save_map(t_data data)
{
	string name = (*((string *)(data.data[2])) == "" ? "noname" : *((string *)(data.data[2])) );
	string full_path = MAP_PATH + name + MAP_EXT;

	t_gui		gui;
	SDL_Event	event;

	bool		continu = false;


	s_button *button = new s_button(new s_text_button(//button did you wanna quit
						get_text("save ?"), DARK_GREY, //text info
						gui.unit * t_vect(4, 2), gui.unit * t_vect(7, 5), 8, //object info
						color[0], color[1]),
						NULL, NULL);
	button->button->image_coord = button->button->image_coord - (gui.unit * t_vect(0, 1));

	gui.add(GUI_OBJ_ID, button);

	s_button *button2 = new s_button(new s_text_button(//button did you wanna quit
						&full_path, DARK_GREY, //text info
						gui.unit * t_vect(4, 2), gui.unit * t_vect(7, 5), 8, //object info
						t_color(0, 0, 0, 0), t_color(0, 0, 0, 0)),
						NULL, NULL);

	gui.add(GUI_OBJ_ID, button2);

	gui.add(GUI_OBJ_ID, new s_button(new s_text_button(//button yes
						get_text("yes"), DARK_GREY, //text info
						gui.unit * t_vect(4.25, 5.25), gui.unit * t_vect(3, 1.5), 8, //object info
						color[0], color[1]),
						quit_save, t_data(3, data.data[1], &name, &continu)));

	gui.add(GUI_OBJ_ID, new s_button(new s_text_button(//button no
						get_text("no"), DARK_GREY, //text info
						gui.unit * t_vect(7.75, 5.25), gui.unit * t_vect(3, 1.5), 8, //object info
						color[0], color[1]),
						stand, &continu));

	while (continu == false)
	{
		prepare_screen();

		if (data.data.size() != 0)
			(*((t_gui *)(data.data[0]))).draw_self();
		gui.draw_self();

		render_screen(draw_fps);

		if (SDL_PollEvent(&(event)) == 1)
		{
			if (event.type == SDL_KEYUP && event.key.keysym.sym == SDLK_ESCAPE)
				continu = true;
			else if (event.type == SDL_MOUSEBUTTONUP && event.button.button == SDL_BUTTON_LEFT)
				gui.click();
		}
	}

}
