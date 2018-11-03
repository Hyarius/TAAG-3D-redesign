#include "taag.h"

t_vect			card_size = t_vect(5, 7);
t_vect			c_pos[8];

static void		increment_index(int *index, int delta, vector<string> *file_list, vector<t_gui_obj *> card_list)
{
	s_spell_card	*card;
	int				i = 0;

	if (*index + delta >= 0 && (size_t)(*index + delta) < (*file_list).size() && (*file_list).size() > 10)
		*index += delta;
	while (i < 8)
	{
		printf("seg fault at = %d\n", i);
		card = (s_spell_card *)(card_list[i]);
		if ((size_t)(*index + i) >= (*file_list).size())
			card->spell = &(spell_list.at("NULL"));
		else
			card->spell = &(spell_list.at((*file_list)[i + *index]));
		(card->button[2])->reset_text(&(card->spell->name));
		i++;
	}
}

static double	calc_line(double line, double space)
{
	double result;

	result = (double)line + (double)line * (double)space;
	return (result);
}

static void		quit_choose_spell(t_data data)//0 = spell ptr | 1 = spell_name | 2 = continue | 3 = spell_card
{
	s_spell			**ptr = (s_spell **)(data.data[0]);
	string			*spell_name = (string *)(data.data[1]);
	bool			*continu = (bool *)(data.data[2]);
	t_spell_card	*spell_card = (t_spell_card *)(data.data[3]);

	*ptr = &(spell_list.at(*spell_name));
	spell_card->set_desc_size();

	*continu = true;
}

void		menu_choose_spell(t_data data)
{
	t_gui			gui = t_gui(30, 20);
	s_spell			*selected_spell = ((s_spell *)(data.data[1]));
	int				index = 0;
	vector<string>	list_file = list_files(SPELL_PATH, SPELL_EXT);
	vector<string>	final_list;
	SDL_Event		event;
	bool			continu = false;

	s_button *button = new s_button(new s_text_button(//button did you wanna quit
		NULL, DARK_GREY, //text info
		gui.unit * t_vect(2, 2), gui.unit * t_vect(26, 16), 8, //object info
		color[0], color[1]),
		NULL, NULL);
	gui.add(GUI_OBJ_ID, button);
	
	size_t i = 0;
	if (list_file.size() == 0)
	{
		s_button *button = new s_button(new s_text_button(//button did you wanna quit
			get_text("no file"), DARK_GREY, //text info
			gui.unit * t_vect(3, 3), gui.unit * t_vect(24, 16), 6, //object info
			color[0], color[1]),
			stand, t_data(1, &continu));
		gui.add(GUI_OBJ_ID, button);
		i++;
	}
	else
	{
		while (i < 8)
		{
			if (i + index < list_file.size())
				final_list.push_back(list_file[i + index]);
			else
				final_list.push_back("");
			i++;
		}
		i = 0;
		while (i < 8)
		{
			c_pos[i] = t_vect(3 + ((card_size.x + 1.2) * (i % 4)), 3 + ((card_size.y + 0.5) * (i / 4)));
			i++;
		}
		i = 0;
		while (i < 8)
		{
			s_spell_card *card = new s_spell_card(&(spell_list.at(final_list[i + index])),
						gui.unit * c_pos[i], gui.unit * card_size,
						NULL, NULL);
			gui.add(SPELL_CARD_ID, card);
			i++;
		}
	}

	while (continu == false)
	{
		prepare_screen();

		if (data.data.size() != 0)
			(*((t_gui *)(data.data[0]))).draw_self();
		gui.draw_self();

		render_screen(draw_fps);

		if (SDL_PollEvent(&(event)) == 1)
		{
			if (event.type == SDL_QUIT)
				menu_quit(&gui);
			else if (event.type == SDL_KEYUP && event.key.keysym.sym == SDLK_ESCAPE)
				continu = true;
			else if (event.type == SDL_MOUSEBUTTONUP)
				gui.click();
			if (event.type == SDL_MOUSEWHEEL && event.wheel.y > 0)
				increment_index(&index, -8, &list_file, gui.object_list[SPELL_CARD_ID]);
			else if (event.type == SDL_MOUSEWHEEL && event.wheel.y < 0)
				increment_index(&index, 8, &list_file, gui.object_list[SPELL_CARD_ID]);
		}
	}

}