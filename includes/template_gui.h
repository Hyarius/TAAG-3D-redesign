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

typedef struct	s_gui_obj
{

					s_gui_obj();
	virtual void	set_funct_param(gui_funct p_funct, t_data p_data) = 0;
	virtual void	draw_self();
	virtual void	click(t_vect mouse);
}				t_gui_obj;

typedef struct	s_text_button : t_gui_obj
{
	string		text; //text to draw on screen
	int			text_size; // text size
	int			text_color; // text color
	t_vect		coord[2]; //0 - coord first rect || 1 - coord second rect
 	t_vect		size[2]; //0 - size first rect || 1 - size second rect
	t_color		color[2]; //0 - color back || 1 - color front
	gui_funct	funct; //function to use when clicked : initialized empty
	t_data		data; // data to send to the function : initialized empty
				s_text_button(	string p_text, int p_text_color, // text info
								t_vect p_coord, t_vect p_size, int border, // coord / size info
								t_color p_color1, t_color p_color2); // color info
	void		set_funct_param(gui_funct p_funct, t_data p_data); //set the funct and its param
	void		draw_self(); // draw the button
	void		click(t_vect mouse); // test if the mouse is in the button and start the funct if yes
}				t_text_button;

typedef struct	s_image_button : t_gui_obj
{
	t_image		image; //image to draw on the screen
	t_vect		coord; // coord of the image
	t_vect		size; // size of the image
	gui_funct	funct; //function to use when clicked : initialized empty
	t_data		data; // data to send to the function : initialized empty
				s_image_button(t_image p_image, t_vect p_coord, t_vect p_size); //info about the image and it's place
	void		set_funct_param(gui_funct p_funct, t_data p_data); //set the funct and its param
	void		draw_self(); // draw the button
	void		click(t_vect mouse); // test if the mouse is in the button and start the funct if yes
}				t_image_button;

typedef struct	s_text_entry : t_gui_obj
{
	string		text; //text to draw on screen
	int			text_size; // text size
	int			text_color; // text color
	t_vect		coord[2]; //0 - coord first rect || 1 - coord second rect || 2 - text coord
 	t_vect		size[2]; //0 - size first rect || 1 - size second rect
	t_color		color[2]; //0 - color back || 1 - color front
	t_gui_obj	**selected_entry; //a pointer to the object pointer in the gui object
				s_text_entry(	string p_text, int p_text_color, //text info
								t_gui_obj **p_selected_entry, //info about the pointer in the gui object
								t_vect p_coord, t_vect p_size, int border, // coord / size info
								t_color p_color1, t_color p_color2); // color info
	void		draw_self(); // draw the button
	void		click(t_vect mouse); // test if the mouse is in the button and start the funct if yes
}				t_text_entry;

typedef struct	s_image_entry : t_gui_obj
{
	string		text; //text to draw on screen
	int			text_size; // text size
	int			text_color; // text color
	t_vect		coord[2]; // 0 - coord of the image || 1 - coord text
	t_vect		size; // size of the image
	t_gui_obj	**selected_entry; //a pointer to the object pointer in the gui object
				s_image_entry(	string p_text, int p_text_color, t_vect p_text_coord, //text info
							t_gui_obj **p_selected_entry, //info about the pointer in the gui object
							t_image p_image, t_vect p_coord, t_vect p_size); //info about the image and it's place
	void		draw_self(); // draw the button
	void		click(t_vect mouse); // test if the mouse is in the button and start the funct if yes
}				t_image_entry;


typedef struct	s_gui
{
	vector<t_gui_obj *>	object_list;
	t_gui_obj			*selected_entry;
	s_gui();
	void		draw_self();
	void		click();
}				t_gui;

#endif
