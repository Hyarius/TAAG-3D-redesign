#include "template.h"

				text_box::text_box()
{

}

bool			text_box::click(t_vect mouse)
{
	if (mouse.x > this->coord.x && mouse.x < this->coord.x + this->size.x && mouse.y > this->coord.y && mouse.y < this->coord.y + this->size.y)
		return (true);
	return (false);
}

				text_box::text_box(string description, int text_color, t_vect p_coord, t_vect p_size, t_color color)
{
	this->text = "";
	this->description = description;
	this->text_color = text_color;
	this->text_size = -1;
	this->coord = p_coord;
	this->size = p_size;
	this->color_front = color;
	this->color_back = t_color(this->color_front.r + 0.2, this->color_front.g + 0.2, this->color_front.b + 0.2);
}

				text_box::text_box(string description, int text_color, t_vect p_coord, t_vect p_size, t_color color, t_color color2)
{
	this->text = "";
	this->description = description;
	this->text_color = text_color;
	this->text_size = -1;
	this->coord = p_coord;
	this->size = p_size;
	this->color_front = color;
	this->color_back = color2;
}

				text_box::text_box(string description, int text_color, int text_size, t_vect p_coord, t_vect p_size, t_color color)
{
	this->text = "";
	this->description = description;
	this->text_color = text_color;
	this->text_size = text_size;
	this->coord = p_coord;
	this->size = p_size;
	this->color_front = color;
	this->color_back = t_color(this->color_front.r + 0.2, this->color_front.g + 0.2, this->color_front.b + 0.2);
}

				text_box::text_box(string description, int text_color, int text_size, t_vect p_coord, t_vect p_size, t_color color, t_color color2)
{
	this->text = "";
	this->description = description;
	this->text_color = text_color;
	this->text_size = text_size;
	this->coord = p_coord;
	this->size = p_size;
	this->color_front = color;
	this->color_back = color2;
}


				text_box::text_box(string description, string text, int text_color, t_vect p_coord, t_vect p_size, t_color color)
{
	this->text = text;
	this->description = description;
	this->text_color = text_color;
	this->text_size = -1;
	this->coord = p_coord;
	this->size = p_size;
	this->color_front = color;
	this->color_back = t_color(this->color_front.r + 0.2, this->color_front.g + 0.2, this->color_front.b + 0.2);
}

				text_box::text_box(string description, string text, int text_color, t_vect p_coord, t_vect p_size, t_color color, t_color color2)
{
	this->text = text;
	this->description = description;
	this->text_color = text_color;
	this->text_size = -1;
	this->coord = p_coord;
	this->size = p_size;
	this->color_front = color;
	this->color_back = color2;
}

				text_box::text_box(string description, string text, int text_color, int text_size, t_vect p_coord, t_vect p_size, t_color color)
{
	this->text = text;
	this->description = description;
	this->text_color = text_color;
	this->text_size = text_size;
	this->coord = p_coord;
	this->size = p_size;
	this->color_front = color;
	this->color_back = t_color(this->color_front.r + 0.2, this->color_front.g + 0.2, this->color_front.b + 0.2);
}

				text_box::text_box(string description, string text, int text_color, int text_size, t_vect p_coord, t_vect p_size, t_color color, t_color color2)
{
	this->text = text;
	this->description = description;
	this->text_color = text_color;
	this->text_size = text_size;
	this->coord = p_coord;
	this->size = p_size;
	this->color_front = color;
	this->color_back = color2;
}

void			text_box::draw_self()
{
	int i = 8;
	int border_size = size.x / i < size.y / i ? size.x / i : size.y / i;

	draw_border_rectangle(this->coord, this->size, this->color_front, this->color_back, i);
	if (this->text.size() != 0)
	{
		if (this->text_size != -1)
			draw_lined_buffer_sized_text(this->text, this->coord + t_vect(border_size * 2, this->size.y / 2), this->text_size, NORMAL, DARK_GREY);
		else
			draw_lined_buffer_sized_text(this->text, this->coord + t_vect(border_size * 2, this->size.y / 2), this->text_size, NORMAL, DARK_GREY);
	}
	else
	{
		if (this->text_size != -1)
			draw_lined_buffer_sized_text(this->description, this->coord + t_vect(border_size * 2, this->size.y / 2), this->text_size, NORMAL, DARK_GREY);
		else
			draw_lined_buffer_sized_text(this->description, this->coord + t_vect(border_size * 2, this->size.y / 2), this->text_size, NORMAL, DARK_GREY);
	}
}

void			text_box::draw_self(int value)
{
	int i = 8;
	int border_size = size.x / i < size.y / i ? size.x / i : size.y / i;

	if (value == 0)
		draw_border_rectangle(this->coord, this->size, this->color_front, t_color(1.0, 0.9, 0.7), i);
	else
		draw_border_rectangle(this->coord, this->size, this->color_front, this->color_back, i);
	if (this->text.size() != 0)
	{
		if (this->text_size != -1)
			draw_lined_buffer_sized_text(this->text, this->coord + t_vect(border_size * 2, this->size.y / 2), this->text_size, NORMAL, this->text_color);
		else
			draw_lined_buffer_text(this->text, this->coord + t_vect(border_size * 2, this->size.y / 2), NORMAL, this->text_color);
	}
	else
	{
		if (this->text_size != -1)
			draw_lined_buffer_sized_text(this->description, this->coord + t_vect(border_size * 2, this->size.y / 2), this->text_size, NORMAL, GREY);
		else
			draw_lined_buffer_text(this->description, this->coord + t_vect(border_size * 2, this->size.y / 2), NORMAL, GREY);
	}
}

string			text_box::get_text()
{
	return (this->text);
}

string			text_box::get_description()
{
	return (this->description);
}

void			text_box::set_text(string new_text)
{
	this->text = new_text;
}

void			text_box::add_text(string new_text)
{
	int i = 8;
	int border_size = size.x / i < size.y / i ? size.x / i : size.y / i;

	if (this->text_size != -1)
		if (calc_buffer_sized_text_len(this->text + new_text, this->text_size, NORMAL, this->text_color) <= this->size.x - border_size * 2)
			this->text += new_text;
}

void			text_box::delete_text()
{
	if (this->text.size() != 0)
		this->text.pop_back();
}
