#include "taag.h"

t_vect			card_size = t_vect(5, 7);
t_vect			card_pos[8];

static void		increment_index(int *index, int delta, vector<string> *file_list, vector<string> *final_list, vector<t_gui_obj *> card_list)
{
	s_spell_card	*card;
	int				i = 0;

	if (*index + delta >= 0 && (size_t)(*index + delta) < (*file_list).size() && (*file_list).size() > 10)
		*index += delta;
	final_list->clear();
	while (i < 8)
	{
		card = (s_spell_card *)(card_list[i]);
		if ((size_t)(*index + i) >= (*file_list).size())
		{
			card->spell = &(spell_list.at("NULL"));
			final_list->push_back("NULL");
		}
		else
		{
			card->spell = &(spell_list.at((*file_list)[i + *index]));
			final_list->push_back((*file_list)[i + *index]);
		}
		(card->button[2])->reset_text(&(card->spell->name));
		card->set_desc_size();
		i++;
	}
}

static void		quit_choose_spell(t_data data)
{
	bool			*continu = (bool *)(data.data[0]);
	string			*new_name = (string *)(data.data[1]);
	t_gui			*gui = (t_gui *)(data.data[2]);
	t_actor			*player = (t_actor *)(data.data[3]);
	int				i = (int &)(data.data[4]);

	player->spell[i] = spell_list.at(*new_name);
	gui->verify_ID_object(SPELL_CARD_ID);
	*continu = true;
}

void		menu_choose_spell(t_data data)//0 - t_gui * | 1 = t_player * | 2 = int
{
	t_gui			gui = t_gui(30, 20);
	int				index = 0;
	vector<string>	list_file;
	vector<string>	final_list;
	SDL_Event		event;
	bool			continu = false;

	s_button *button = new s_button(new s_text_button(//button did you wanna quit
				NULL, DARK_GREY, //text info
				gui.unit * t_vect(2, 2), gui.unit * t_vect(26, 16), 8, //object info
				color[0], color[1]),
				NULL, NULL);
	gui.add(GUI_OBJ_ID, button);

	list_file = list_files(SPELL_PATH, SPELL_EXT);
	list_file.insert(list_file.begin(), "NULL");
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
			card_pos[i] = t_vect(3 + ((card_size.x + 1.2) * (i % 4)), 3 + ((card_size.y + 0.5) * (i / 4)));
			i++;
		}
		i = 0;
		while (i < 8)
		{
			s_spell_card *card = new s_spell_card(&(spell_list.at(final_list[i + index])),
						gui.unit * card_pos[i], gui.unit * card_size,
						quit_choose_spell, t_data(5, &continu, &(final_list[i + index]), data.data[0], data.data[1], data.data[2]));
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
			else if (event.type == SDL_MOUSEBUTTONUP && event.button.button == SDL_BUTTON_LEFT)
				gui.click();
			if ((event.type == SDL_MOUSEWHEEL && event.wheel.y > 0) ||
				(event.type == SDL_KEYUP && event.key.keysym.sym == SDLK_UP))
				increment_index(&index, -8, &list_file, &final_list, gui.object_list[SPELL_CARD_ID]);
			else if ((event.type == SDL_MOUSEWHEEL && event.wheel.y < 0) ||
				(event.type == SDL_KEYUP && event.key.keysym.sym == SDLK_DOWN))
				increment_index(&index, 8, &list_file, &final_list, gui.object_list[SPELL_CARD_ID]);
		}
	}

}
