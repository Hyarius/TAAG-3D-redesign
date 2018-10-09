#include "template.h"

s_text_entry::s_text_entry(	string p_text, int p_text_color,
				t_gui_obj **p_selected_entry,
				t_vect p_coord, t_vect p_size, int border,
				t_color p_color1, t_color p_color2)
{
	this->text = p_text;
	this->text_color = p_text_color;
	this->coord[0] = p_coord;
	this->size[0] = p_size;
	this->coord[1] = p_coord + border;
	this->size[1] = p_size - (border * 2);
	this->text_size = calc_text_size(this->text, this->size[1]);
	this->color[0] = p_color1;
	this->color[1] = p_color2;
}
void		s_text_entry::draw_self()
{

}

void		s_text_entry::click(t_vect mouse)
{

}
