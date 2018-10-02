#ifndef TEMPLATE_CLASS_H
# define TEMPLATE_CLASS_H

# include "structure.h"
# include "include.h"

using namespace std;

class tileset
{
private:
	string			path;
	SDL_Rect		*sprite_list;
	SDL_Surface		*surface;
	t_vect			nb_tile;
	GLenum			format;
	GLint			internal_format;
	GLuint			texture_id;
	GLuint			texture_info;

public:
					tileset(string path, int value_x, int value_y);
	void			draw_sprite(int sprite, t_vect tl, t_vect tr, t_vect dl, t_vect dr);
    SDL_Rect	    *get_rect(int sprite);
	SDL_Surface		*get_surface();
	int				get_sprite(int x, int y);
	GLenum			get_format();
	GLint			get_internal_format();
	GLuint			get_texture_id();
	GLuint			get_texture_info();
	void			reload_texture();
};

class image
{
private:
	SDL_Surface		*surface;
	t_vect			coord;
	t_vect			size;
	GLenum			format;
	GLint			internal_format;
	GLuint			texture_id;
	GLuint			texture_info;
public:
					image(string path);
					image(string path, t_vect p_coordd, t_vect p_size);
	void			draw_self();
	void			draw_self(t_vect tl, t_vect tr, t_vect dl, t_vect dr);
	SDL_Surface		*get_surface();
	GLenum			get_format();
	GLint			get_internal_format();
	GLuint			get_texture_id();
	GLuint			get_texture_info();
	void			reload_texture();
};

class text_button
{
private:
	string			text;
	int				text_color;
	int				text_size;
	t_vect			coord;
	t_vect			size;
	t_color			color_front;
	t_color			color_back;
	void			(*funct)();
public:
					text_button();
					text_button(string text, int text_color, t_vect coord, t_vect size, t_color color, void(&p_fonct)());
					text_button(string text, int text_color, t_vect coord, t_vect size, t_color color, t_color color2, void(&p_fonct)());
					text_button(string text, int text_color, int text_size, t_vect coord, t_vect size, t_color color, void(&p_fonct)());
					text_button(string text, int text_color, int text_size, t_vect coord, t_vect size, t_color color, t_color color2, void(&p_fonct)());
	void			draw_self();
	void			click(t_vect mouse);
};

class text_box
{
private:
	string			text;
	string			description;
	int				text_color;
	int				text_size;
	t_vect			coord;
	t_vect			size;
	t_color			color_front;
	t_color			color_back;
public:
					text_box();
					text_box(string description, int text_color, t_vect coord, t_vect size, t_color color);
					text_box(string description, int text_color, t_vect coord, t_vect size, t_color color, t_color color2);
					text_box(string description, int text_color, int text_size, t_vect coord, t_vect size, t_color color);
					text_box(string description, int text_color, int text_size, t_vect coord, t_vect size, t_color color, t_color color2);
					text_box(string description, string text, int text_color, t_vect coord, t_vect size, t_color color);
					text_box(string description, string text, int text_color, t_vect coord, t_vect size, t_color color, t_color color2);
					text_box(string description, string text, int text_color, int text_size, t_vect coord, t_vect size, t_color color);
					text_box(string description, string text, int text_color, int text_size, t_vect coord, t_vect size, t_color color, t_color color2);
	void			draw_self();
	void			draw_self(int value);
	string			get_text();
	string			get_description();
	void			set_text(string new_text);
	void			add_text(string new_text);
	void			delete_text();
	bool			click(t_vect mouse);
};

class iterator_box
{
private:
	vector<image>	image_list;
	int				*value;
	string			text;
	t_vect			coord[4];
	t_vect			size[4];
	t_color			color_front;
	t_color			color_back;
public:
	iterator_box();
	iterator_box(string text, int *value, vector<image> image_list, t_vect coord_text, t_vect coord, t_vect size, t_vect space, t_color color);
	iterator_box(string text, int *value, vector<image> image_list, t_vect coord_text, t_vect coord, t_vect size, t_vect space, t_color color, t_color color2);
};

class gui
{
private:
	t_vect					win_unit;
	vector<text_button>		list_text_button;
	vector<text_box>		list_text_box;
	vector<image>			list_image;
	text_box				*selected_text_box;
public:
	gui();
	void					draw_self();
	void					draw_image();
	void					draw_text_button();
	void					draw_text_box();
	void					test_button_click();
	void					test_box_click();
	void					test_click();
	void					add_text_button(text_button new_button);
	void					add_text_box(text_box new_text);
	void					add_image(image new_image);
	t_vect					get_win_unit();
	text_box				*get_selected_text_box();
};

#endif
