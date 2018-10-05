#include "template.h"

text_button::text_button()
{

}

text_button::text_button(string text, int text_color, t_vect p_coord, t_vect p_size, t_color color, void(&p_fonct)())
{
	this->text = text;
	this->text_color = text_color;
	this->text_size = -1;
	this->coord = p_coord;
	this->size = p_size;
	this->color_front = color;
	this->color_back = t_color(this->color_front.r + 0.2, this->color_front.g + 0.2, this->color_front.b + 0.2);
	this->funct = p_fonct;
}

text_button::text_button(string text, int text_color, t_vect p_coord, t_vect p_size, t_color color, t_color color2, void(&p_fonct)())
{
	this->text = text;
	this->text_color = text_color;
	this->text_size = -1;
	this->coord = p_coord;
	this->size = p_size;
	this->color_front = color;
	this->color_back = color2;
	this->funct = p_fonct;
}

text_button::text_button(string text, int text_color, int text_size, t_vect p_coord, t_vect p_size, t_color color, void(&p_fonct)())
{
	this->text = text;
	this->text_color = text_color;
	this->text_size = text_size;
	this->coord = p_coord;
	this->size = p_size;
	this->color_front = color;
	this->color_back = t_color(this->color_front.r + 0.2, this->color_front.g + 0.2, this->color_front.b + 0.2);
	this->funct = p_fonct;
}

text_button::text_button(string text, int text_color, int text_size, t_vect p_coord, t_vect p_size, t_color color, t_color color2, void(&p_fonct)())
{
	this->text = text;
	this->text_color = text_color;
	this->text_size = text_size;
	this->coord = p_coord;
	this->size = p_size;
	this->color_front = color;
	this->color_back = color2;
	this->funct = p_fonct;
}

void			text_button::draw_self()
{
	draw_border_rectangle(this->coord, this->size, this->color_front, this->color_back, BORDER);
	if (this->text_size != -1)
		draw_centred_buffer_sized_text(this->text, t_vect(this->coord.x + this->size.x / 2, this->coord.y + this->size.y / 2), this->text_size, NORMAL, this->text_color);
	else
		draw_centred_buffer_text(this->text, t_vect(this->coord.x + this->size.x / 2, this->coord.y + this->size.y / 2), NORMAL, this->text_color);
}

bool			text_button::click(t_vect mouse)
{
	if (mouse.x > this->coord.x && mouse.x < this->coord.x + this->size.x && mouse.y > this->coord.y && mouse.y < this->coord.y + this->size.y)
	{
		this->funct();
		return (true);
	}
	return (false);
}
