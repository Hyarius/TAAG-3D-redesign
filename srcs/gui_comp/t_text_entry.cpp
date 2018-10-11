#include "template.h"

s_text_entry::s_text_entry(	string p_text, int p_text_color,
				t_entry_comp **p_selected_entry,
				t_vect p_coord, t_vect p_size, int border,
				t_color p_color1, t_color p_color2)
{
	this->text = p_text;
	this->text_color = p_text_color;
	this->coord[0] = p_coord;
	this->size[0] = p_size;
	this->coord[1] = p_coord + border;
	this->size[1] = p_size - (border * 2);
	this->coord[2] = this->coord[1] + t_vect(0, this->size[1].y / 2);
	this->text_size = calc_text_size(this->text, this->size[1]);
	this->color[0] = p_color1;
	this->color[1] = p_color2;
	this->selected_entry = p_selected_entry;
}

void		s_text_entry::draw_self()
{
	for (int i = 0 ; i < 2 ; i++)
		draw_rectangle(this->coord[i], this->size[i], this->color[i]);
	draw_lined_text(this->text, this->text_size, this->coord[2], NORMAL, this->text_color);
}
