#ifndef TEMPLATE_GUI_H
# define TEMPLATE_GUI_H

using namespace std;

typedef struct	s_data
{

	void 		**data;
				s_data();
				s_data(void **p_data);
	void		operator = (void **p_data);
}				t_data;

typedef 		void(*gui_funct)(t_data p_data);

typedef struct	s_gui_object
{

					s_gui_object();
	virtual void	set_funct_param(gui_funct p_funct, t_data p_data) = 0;
	virtual void	draw_self();
	virtual void	click(t_vect mouse);
}				t_gui_object;

typedef struct	s_text_button : t_gui_object
{
	string		text;
	int			text_size;
	int			text_color;
	t_vect		coord[2];
	t_vect		size[2];
	t_color		color[2];
	gui_funct	funct;
	t_data		data;
				s_text_button(	string p_text, int p_text_color,
								t_vect p_coord, t_vect p_size, int border,
								t_color p_color1, t_color p_color2);
	void		set_funct_param(gui_funct p_funct, t_data p_data);
	void		draw_self();
	void		click(t_vect mouse);
}				t_text_button;

typedef struct	s_text_box : t_gui_object
{
	t_vect		coord;
	t_vect		size;
}				t_text_box;

typedef struct	s_image_button : t_gui_object
{
	t_image		image;
	t_vect		coord;
	t_vect		size;
	gui_funct	funct;
	t_data		data;
				s_image_button(t_image p_image, t_vect p_coord, t_vect p_size);
	void		set_funct_param(gui_funct p_funct, t_data p_data);
	void		draw_self();
	void		click(t_vect mouse);
}				t_image_button;

typedef struct	s_image_box : t_gui_object
{
	t_vect		coord;
	t_vect		size;
}				t_image_box;

typedef struct	s_text_entry : t_gui_object
{
	t_vect		coord;
	t_vect		size;
}				t_text_entry;

/*
typedef struct	s_text_button : t_gui_object
{
	string		text;
	int			text_size;
	int			text_color;
	t_vect		coord[2];
	t_vect		size[2];
	t_color		color[2];

				s_text_button(string p_text, int p_text_color, t_vect p_coord, t_vect p_size, int border, t_color p_color1, t_color p_color2);
	void		draw_self();
	void		click();
}				t_text_button;
*/

typedef struct	s_gui
{
	vector<t_gui_object *>	object_list;
	s_gui();
	void		draw_self();
	void		click();
}				t_gui;

#endif
