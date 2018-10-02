#include "template.h"

iterator_box::iterator_box()
{

}

iterator_box::iterator_box(string text, int *value, t_vect p_coord, t_vect p_size, t_color color, t_color color2 )
{
	double i = 8;
	int border_size = p_size.x / i < p_size.y / i ? p_size.x / i : p_size.y / i;

	this->value = value;
	this->text = text;

	i = 1;
	while (calc_buffer_sized_text_len(text, i + 1, NORMAL, BLACK) + border_size * 4 < p_size.x / 2 &&
			get_char(i, NORMAL, BLACK, 'M')->h < p_size.y / 2)
		i++;
	this->text_size = i;
	this->color_front = color;
	this->color_back = color2;

	this->coord[4] = p_coord + t_vect(border_size * 2, p_size.y / 2);
	this->size[3] = t_vect(p_size.y, p_size.y);
	this->size[2] = t_vect(p_size.y * 2 , p_size.y);
	this->size[1] = t_vect(p_size.y, p_size.y);
	this->coord[3] = p_coord + t_vect(p_size.x - this->size[3].x, 0);
	this->coord[2] = this->coord[3] - t_vect(p_size.y * 2.5, 0);
	this->coord[1] = this->coord[2] - t_vect(p_size.y * 1.5, 0);
	this->size[0] = t_vect(this->coord[1].x - p_coord.x - p_size.y * 0.5, p_size.y);
	this->coord[0] = p_coord;
}

string		iterator_box::get_text()
{
	return (this->text);
}

void		iterator_box::draw_self()
{
	int i = 8;
	int border_size = this->size[0].x / i < this->size[0].y / i ? this->size[0].x / i : this->size[0].y / i;

	i = 0;
	while (i < 4)
	{
		draw_border_rectangle(this->coord[i], this->size[i], this->color_front, this->color_back, 8);
		i++;
	}
	draw_centred_buffer_sized_text("<", this->coord[1] + this->size[1] / 2, this->text_size, NORMAL, DARK_GREY);
	if (this->value != NULL)
		draw_centred_buffer_sized_text(to_string(*this->value), this->coord[2] + this->size[2] / 2, this->text_size, NORMAL, DARK_GREY);
	draw_centred_buffer_sized_text(">", this->coord[3] + this->size[3] / 2, this->text_size, NORMAL, DARK_GREY);
	draw_lined_buffer_sized_text(this->text, this->coord[4], this->text_size, NORMAL, DARK_GREY);
}

void			iterator_box::add_value(double modif)
{
	*(this->value) += modif;
}

bool			iterator_box::click_minus(t_vect mouse)
{
	if (mouse.x > this->coord[1].x && mouse.x < this->coord[1].x + this->size[1].x && mouse.y > this->coord[1].y && mouse.y < this->coord[1].y + this->size[1].y)
		return (true);
	return (false);
}

bool			iterator_box::click_plus(t_vect mouse)
{
	if (mouse.x > this->coord[3].x && mouse.x < this->coord[3].x + this->size[3].x && mouse.y > this->coord[3].y && mouse.y < this->coord[3].y + this->size[3].y)
		return (true);
	return (false);
}
