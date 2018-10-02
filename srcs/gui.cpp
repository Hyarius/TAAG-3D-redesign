#include "template.h"

gui::gui()
{
	this->win_unit = t_vect(get_win_size().x / 15, get_win_size().y / 10);
}

void					gui::draw_self()
{
	this->draw_image();
	this->draw_text_button();
	this->draw_text_box();
}

void					gui::draw_image()
{
	size_t i;

	i = 0;
	while (i < this->list_image.size())
	{
		this->list_image[i].draw_self();
		i++;
	}
}

void					gui::draw_text_button()
{
	size_t i;

	i = 0;
	while (i < this->list_text_button.size())
	{
		this->list_text_button[i].draw_self();
		i++;
	}
}

void					gui::draw_text_box()
{
	size_t i;

	i = 0;
	while (i < this->list_text_box.size())
	{
		this->list_text_box[i].draw_self((this->selected_text_box != &(this->list_text_box[i]) ? 1 : 0));
		i++;
	}
}

void					gui::test_button_click()
{
	size_t i;
	t_vect mouse;

	i = 0;
	mouse = get_mouse_coord();
	while (i < this->list_text_button.size())
	{
		this->list_text_button[i].click(mouse);
		i++;
	}
}

void					gui::test_box_click()
{
	size_t i;
	t_vect mouse;

	i = 0;
	this->selected_text_box = NULL;
	mouse = get_mouse_coord();
	while (i < this->list_text_box.size())
	{
		if (this->list_text_box[i].click(mouse) == true)
			this->selected_text_box = &(this->list_text_box[i]);
		i++;
	}
}

void					gui::test_click()
{
	this->test_button_click();
	this->test_box_click();
}

void					gui::add_text_button(text_button new_button)
{
	this->list_text_button.push_back(new_button);
}

void					gui::add_text_box(text_box new_button)
{
	this->list_text_box.push_back(new_button);
}

void					gui::add_image(image new_image)
{
	this->list_image.push_back(new_image);
}

t_vect		gui::get_win_unit()
{
	return (this->win_unit);
}

text_box	*gui::get_selected_text_box()
{
	return (this->selected_text_box);
}