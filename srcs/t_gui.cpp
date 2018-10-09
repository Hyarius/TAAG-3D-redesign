#include "template.h"

s_gui::s_gui()
{

}

void		s_gui::draw_self()
{
	size_t i = 0;

	while (i < this->object_list.size())
	{
		this->object_list[i]->draw_self();
		i++;
	}
}

void		s_gui::click()
{
	size_t i = 0;
	t_vect mouse = get_mouse_coord();

	this->selected_entry = NULL;
	SDL_StopTextInput();
	while (i < this->object_list.size())
	{
		this->object_list[i]->click(mouse);
		i++;
	}
}
