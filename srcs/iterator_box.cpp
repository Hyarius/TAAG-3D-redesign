#include "template.h"

iterator_box::iterator_box()
{

}

iterator_box::iterator_box(string text, int *value, int value_min, int value_max, int value_incre, t_vect p_coord, t_vect p_size, t_color color, t_color color2 )
{
	this->value = value;

	this->value_min = value_min;
	this->value_max = value_max;
	this->value_incre = value_incre;
	this->text = text;

	int i = 1;
	while (calc_buffer_sized_text_len(text, i + 1, NORMAL, BLACK) + BORDER * 4 < p_size.x / 2 &&
			get_char(i, NORMAL, BLACK, 'M')->h < p_size.y / 2)
		i++;
	this->text_size = i;
	this->color_front = color;
	this->color_back = color2;

	this->coord[4] = p_coord + t_vect(BORDER * 2, p_size.y / 2);
	this->size[3] = t_vect(p_size.y, p_size.y);
	this->size[2] = t_vect(p_size.y * 2 , p_size.y);
	this->size[1] = t_vect(p_size.y, p_size.y);
	this->coord[3] = p_coord + t_vect(p_size.x - this->size[3].x, 0);
	this->coord[2] = this->coord[3] - t_f_vect(p_size.y * 2.5, 0);
	this->coord[1] = this->coord[2] - t_f_vect(p_size.y * 1.5, 0);
	this->size[0] = t_vect(this->coord[1].x - p_coord.x - (int)(p_size.y * 0.5), p_size.y);
	this->coord[0] = p_coord;
}

string		iterator_box::get_text()
{
	return (this->text);
}

void		iterator_box::draw_self()
{
	int i = 0;
	while (i < 4)
	{
		draw_border_rectangle(this->coord[i], this->size[i], this->color_front, this->color_back);
		i++;
	}
	draw_centred_buffer_sized_text("<", this->coord[1] + this->size[1] / 2, this->text_size, NORMAL, DARK_GREY);
	if (this->value != NULL)
		draw_centred_buffer_sized_text(to_string(*this->value), this->coord[2] + this->size[2] / 2, this->text_size, NORMAL, DARK_GREY);
	draw_centred_buffer_sized_text(">", this->coord[3] + this->size[3] / 2, this->text_size, NORMAL, DARK_GREY);
	draw_lined_buffer_sized_text(this->text, this->coord[4], this->text_size, NORMAL, DARK_GREY);
}

void			iterator_box::add_value(int modif)
{
	*(this->value) += modif;
}

void			iterator_box::click_minus(t_vect mouse)
{
	if (mouse.x > this->coord[1].x && mouse.x < this->coord[1].x + this->size[1].x && mouse.y > this->coord[1].y && mouse.y < this->coord[1].y + this->size[1].y)
	{
		if (*(this->value) > this->value_min)
			this->add_value(- this->value_incre);
		else
			*(this->value) = this->value_max;
	}
}

void			iterator_box::click_plus(t_vect mouse)
{
	if (mouse.x > this->coord[3].x && mouse.x < this->coord[3].x + this->size[3].x && mouse.y > this->coord[3].y && mouse.y < this->coord[3].y + this->size[3].y)
	{
		if (*(this->value) < this->value_max)
			this->add_value(this->value_incre);
		else
			*(this->value) = this->value_min;
	}
}
