#include "template.h"

void			menu_quit();

list_box::list_box()
{

}

list_box::list_box(string p_text, string p_empty_line, t_vect p_coord, t_vect p_size, t_color color, t_color color2, vector<string>(&p_fonct)(string path, string extension))
{
	this->funct = p_fonct;
	this->text = p_text;
	this->empty_line = p_empty_line;
	this->line_index = -1;
	this->color_front = color;
	this->color_back = color2;

	this->coord[0] = p_coord;
	this->size[0] = t_vect(p_size.x / 2 - BORDER, p_size.y);
	this->coord[1] = this->coord[0] + t_vect(this->size[0].x + BORDER * 2, 0);
	this->size[1] = t_vect(p_size.x / 2 - BORDER, p_size.y);

	this->text_size = 1;
	while (calc_buffer_sized_text_len(text, this->text_size + 1, NORMAL, BLACK) + BORDER * 4 < this->size[0].x &&
			get_char(this->text_size, NORMAL, BLACK, 'M')->h < this->size[0].y)
		this->text_size++;
	this->empty_line_size = 1;
	while (calc_buffer_sized_text_len(empty_line, this->empty_line_size + 1, NORMAL, BLACK) + BORDER * 4 < this->size[1].x &&
			get_char(this->empty_line_size, NORMAL, BLACK, 'M')->h < this->size[0].y)
		this->empty_line_size++;
}

void			list_box::draw_self()
{
	draw_border_rectangle(this->coord[0], this->size[0], this->color_front, this->color_back);
	draw_lined_buffer_sized_text(this->text, this->coord[0] + t_vect(BORDER * 2, this->size[0].y / 2), this->text_size, NORMAL, DARK_GREY);

	draw_border_rectangle(this->coord[1], this->size[1], this->color_front, this->color_back);
	if (line_index != -1)
	{
		this->line_size = 1;
		while (calc_buffer_sized_text_len(this->list_string[this->line_index], this->line_size + 1, NORMAL, BLACK) + BORDER * 4 < size[1].x &&
			get_char(this->line_size, NORMAL, BLACK, 'M')->h < this->size[0].y - BORDER * 2)
			this->line_size++;
		draw_centred_buffer_sized_text(this->list_string[line_index], this->coord[1] + this->size[1] / 2, this->line_size, NORMAL, DARK_GREY);
	}
}

string			list_box::check_list(t_vect mouse)
{
	SDL_Event	event;
	bool		quit = false;
	int			i;
	t_vect		text_coord[5];
	t_vect		text_size;

	this->list_string = this->funct("ressources/actor", ".");
	if (this->line_index == -1)
		this->line_index = 0;
	this->list_string.insert(this->list_string.begin(), this->empty_line);

	int delta = 5;
	int j = 0;

	t_vect tmp_size = this->size[1] * t_vect(1, delta);
	text_size = t_vect(tmp_size.x, tmp_size.y / delta);
	t_vect tmp_coord = t_vect(this->coord[1].x, this->coord[1].y - (text_size.y * 2));
	for (i = 0; i < 5; i++)
	{
		while (tmp_coord.y + text_size.y * (i + j) < 0)
			j++;
		text_coord[i] = t_vect(tmp_coord.x, tmp_coord.y + (int)(text_size.y * (i + j)));
	}
	while (quit == false)
	{
		i = - 2;
		while (i + this->line_index < (int)this->list_string.size() + 2 && i < delta)
		{
			if (i + j + this->line_index == this->line_index)
				draw_border_rectangle(text_coord[i + 2], text_size, this->color_front, t_color(1.0, 0.9, 0.7));
			else
				draw_border_rectangle(text_coord[i + 2], text_size, this->color_front, this->color_back);
			if (i + j + this->line_index >= 0 && i + j + this->line_index < this->list_string.size())
			{
				this->line_size = 1;
				while (calc_buffer_sized_text_len(this->list_string[i + j + this->line_index], this->line_size + 1, NORMAL, BLACK) + BORDER * 4 < tmp_size.x &&
						get_char(this->line_size, NORMAL, BLACK, 'M')->h < this->size[0].y - BORDER * 2)
					this->line_size++;
				draw_centred_buffer_sized_text(this->list_string[i + j + this->line_index], text_coord[i + 2] + text_size / 2 , this->line_size, NORMAL, DARK_GREY);
			}
			i++;
		}

		render_screen();

		if (SDL_PollEvent(&(event)) == 1)
		{
			if (event.type == SDL_QUIT || (event.type == SDL_KEYUP && event.key.keysym.sym == SDLK_ESCAPE))
				menu_quit();
			else if (event.type == SDL_KEYUP && event.key.keysym.sym == SDLK_RETURN)
				quit = true;
			else if (((event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_DOWN) || (event.type == SDL_MOUSEWHEEL && event.wheel.y < 0)) && this->line_index + 1  < this->list_string.size())
				this->line_index++;
			else if (((event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_UP) || (event.type == SDL_MOUSEWHEEL && event.wheel.y > 0)) && this->line_index > 0)
				this->line_index--;
			else if (event.type == SDL_MOUSEBUTTONUP)
			{
				t_vect mouse = get_mouse_coord();
				if (mouse.x < text_coord[0].x || mouse.x > text_coord[0].x + text_size.x || mouse.y < text_coord[0].y || mouse.y > text_coord[4].y + text_size.y)
					quit = true;
			}
		}
	}
	return (this->list_string[this->line_index]);
}

string			list_box::click(t_vect mouse)
{
	if (mouse.x > this->coord[1].x && mouse.x < this->coord[1].x + this->size[1].x && mouse.y > this->coord[1].y && mouse.y < this->coord[1].y + this->size[1].y)
	{
		return (this->check_list(mouse));
	}
	return ("");
}
