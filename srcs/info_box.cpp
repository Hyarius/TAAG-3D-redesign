#include "template.h"

				info_box::info_box()
{

}

				info_box::info_box(string text, int text_color, t_vect p_coord, t_vect p_size, t_color color, t_color color2)
{
	this->text = text;
	this->text_color = text_color;
	this->text_size = 1;
	while (calc_buffer_sized_text_len(text, this->text_size + 1, NORMAL, BLACK) + (BORDER * 4) < p_size.x &&
			get_char(this->text_size + 1, NORMAL, BLACK, 'M')->h < p_size.y / 2)
		this->text_size++;
	this->coord = p_coord;
	this->size = p_size;
	this->color_front = color;
	this->color_back = color2;
}


void			info_box::draw_self()
{
	draw_border_rectangle(this->coord, this->size, this->color_front, this->color_back);
	draw_centred_buffer_sized_text(this->text, this->coord + this->size / 2, this->text_size, NORMAL, DARK_GREY);
}
