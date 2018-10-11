#include "template.h"

s_gui::s_gui()
{
	this->selected_entry = NULL;
}

void		s_gui::draw_self()
{
	size_t i = 0;

	while (i < this->object_list.size())
	{
		this->object_list.at(i)->draw_self();
		i++;
	}
}

void		s_gui::click()
{
	size_t i = 0;
	t_vect mouse = get_mouse_coord();

	if (this->selected_entry != NULL)
	{
		this->selected_entry = NULL;
		SDL_StopTextInput();
	}
	while (i < this->object_list.size())
	{
		this->object_list.at(i)->click(mouse);
		i++;
	}
}
