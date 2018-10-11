#ifndef TEMPLATE_GUI_H
# define TEMPLATE_GUI_H

# include "template_gui_structure.h"

using namespace std;

typedef struct		s_gui_obj
{
	virtual void	draw_self() = 0;
	virtual void	click(t_vect mouse) = 0;
	virtual 		~s_gui_obj() {}
}					t_gui_obj;

typedef struct		s_button : t_gui_obj
{
	t_button_comp	*button;

					s_button(t_button_comp *p_button, gui_funct p_funct, t_data p_data);
	void			draw_self();
	void			click(t_vect mouse);
}					t_button;

typedef struct	s_gui
{
	vector<t_gui_obj *>	object_list;
	t_gui_obj			*selected_entry;
	s_gui();
	void		draw_self();
	void		click();
}				t_gui;

#endif
