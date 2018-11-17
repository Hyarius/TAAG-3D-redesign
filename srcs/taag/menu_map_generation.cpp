#include "taag.h"

void			menu_map_generation(t_data data)
{
	t_gui gui;

	gui.add(ITERATOR_ID, new s_iterator(
				new t_text_button(get_text("map_size_x"), DARK_GREY, //pa
								gui->unit * t_vect(b_pos[0], line), gui->unit * t_vect(b_size[0], line_height), 3,
								color[0], color[1]),
							new t_text_button(get_text("-"), DARK_GREY, //minus button
								gui->unit * t_vect(b_pos[1], line), gui->unit * t_vect(b_size[1], line_height), 3,
								color[0], color[1]),
							new t_text_button(NULL, DARK_GREY, //value button
								gui->unit * t_vect(b_pos[2], line), gui->unit * t_vect(b_size[2], line_height), 3,
								color[0], color[1]),
							new t_text_button(get_text("+"), DARK_GREY, //plus button
								gui->unit * t_vect(b_pos[3], line), gui->unit * t_vect(b_size[3], line_height), 3,
								color[0], color[1]),
							&(player->stat.pa.max), g_pa[0], g_pa[1], g_pa[2],
							&(player->attrib_point), 5, &(player->level)));
}
