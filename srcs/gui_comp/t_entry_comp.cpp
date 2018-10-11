#include "template.h"

void			t_entry_comp::add_text(string new_text)
{
	if (calc_text_len(this->text + new_text, this->text_size, NORMAL) <= this->size[1].x)
		this->text += new_text;
}

void			t_entry_comp::delete_text()
{
	if (this->text.size() != 0)
		this->text.pop_back();
}

void			t_entry_comp::click(t_vect mouse)
{
	if (mouse > this->coord[0] && mouse < this->coord[0] + this->size[0])
	{
		*(this->selected_entry) = this;
		SDL_StartTextInput();
	}
}

void			t_entry_comp::set_funct_param(gui_funct p_funct, t_data p_data)
{

}
