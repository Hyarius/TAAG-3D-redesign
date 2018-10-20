#include "template.h"

s_entry::s_entry(t_entry_comp *p_entry)
{
	this->entry = p_entry;
	if (this->entry->text == NULL)
		this->entry->text = &this->text;
}


void			s_entry::draw_self()
{
	this->entry->draw_self();
}

void			s_entry::click(t_vect mouse)
{
	this->entry->click(mouse);
}
