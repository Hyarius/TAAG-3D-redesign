#include "template.h"

list_box::list_box()
{

}

list_box::list_box(string p_text, string p_empty_line, t_vect p_coord, t_vect p_size, t_color color, t_color color2)
{
	this->text = p_text;
	this->empty_line = p_empty_line;
	this->line_index = -1;
	this->color_front = color;
	this->color_back = color2;

	int i = 8;
	int border_size = p_size.x / i < p_size.y / i ? p_size.x / i : p_size.y / i;

	this->coord[0] = p_coord;
	this->size[0] = t_vect(p_size.x / 2 - border_size, p_size.y);
	this->coord[1] = this->coord[0] + t_vect(this->size[0].x + border_size * 2, 0);
	this->size[1] = t_vect(p_size.x / 2 - border_size, p_size.y);

	this->text_size = 1;
	while (calc_buffer_sized_text_len(text, this->text_size + 1, NORMAL, BLACK) + border_size * 4 < this->size[0].x &&
			get_char(this->text_size, NORMAL, BLACK, 'M')->h < this->size[0].y)
		this->text_size++;
	this->empty_line_size = 1;
	while (calc_buffer_sized_text_len(empty_line, this->empty_line_size + 1, NORMAL, BLACK) + border_size * 4 < this->size[1].x &&
			get_char(this->empty_line_size, NORMAL, BLACK, 'M')->h < this->size[0].y)
	this->empty_line_size++;
}

void			list_box::draw_self()
{
	int i = 8;
	int border_size = this->size[0].x / i < this->size[0].y / i ? this->size[0].x / i : this->size[0].y / i;

	draw_border_rectangle(this->coord[0], this->size[0], this->color_front, this->color_back, 8);
	draw_lined_buffer_sized_text(this->text, this->coord[0] + t_vect(border_size * 2, this->size[0].y / 2), this->text_size, NORMAL, DARK_GREY);

	draw_border_rectangle(this->coord[1], this->size[1], this->color_front, this->color_back, 8);
	if (line_index != -1)
	{

		draw_centred_buffer_sized_text(this->list_string[line_index], this->coord[1] + this->size[1] / 2, this->line_size, NORMAL, DARK_GREY);
	}

}

string			list_box::check_list(t_vect mouse)
{
	printf("Click sur la list done\n");
	return ("");
}

string			list_box::click(t_vect mouse)
{
	if (mouse.x > this->coord[1].x && mouse.x < this->coord[1].x + this->size[1].x && mouse.y > this->coord[1].y && mouse.y < this->coord[1].y + this->size[1].y)
	{
		return (this->check_list(mouse));
	}
	return ("");
}
