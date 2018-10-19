#include "template.h"

s_gui::s_gui()
{
	entry = NULL;
	unit = t_vect(get_win_size().x / 15, get_win_size().y / 10);
}

void		s_gui::draw_self()
{
	size_t i = 0;

	while (i < object_list.size())
	{
		object_list.at(i)->draw_self();
		i++;
	}
}

void		s_gui::click()
{
	size_t i = 0;
	t_vect mouse = get_mouse_coord();

	if (entry != NULL)
	{
		entry = NULL;
		SDL_StopTextInput();
	}
	while (i < object_list.size())
	{
		object_list.at(i)->click(mouse);
		i++;
	}
}

void		s_gui::add(t_gui_obj *object)
{
	object_list.push_back(object);
}
