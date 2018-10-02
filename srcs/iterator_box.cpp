#include "template.h"

iterator_box::iterator_box()
{

}

iterator_box::iterator_box(string text, int *value, vector<image> image_list, t_vect coord_text, t_vect coord, t_vect size, t_vect space, t_color color)
{
	this->image_list = image_list;
	this->value = value;
	this->text = text;
	this->coord[0] = coord_text;
	this->coord[1] = coord;
	this->coord[2] = coord + 
	this->size[4];
	this->color_front;
	this->color_back;
}

iterator_box::iterator_box(string text, int *value, vector<image> image_list, t_vect coord_text, t_vect coord, t_vect size, t_vect space, t_color color, t_color color2)
{
	this->image_list;
	this->value;
	this->text;
	this->coord[4];
	this->size[4];
	this->color_front;
	this->color_back;
}