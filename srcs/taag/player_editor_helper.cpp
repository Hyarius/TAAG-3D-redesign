#include "taag.h"

vector<double>	b_pos = {1, 9, 10.25, 12};
vector<double>	b_size = {7.75, 1, 1.5, 1};
t_color			color[3] = {t_color(0.5, 0.5, 0.5),
							t_color(0.6, 0.6, 0.6),
							t_color(1.0, 1.0, 0.7)};

static double	calc_line(int line, double space)
{
	double result;

	result = (double)line + (double)line * (double)space;
	return (result);
}

void			create_entry_name(t_gui *gui, t_actor *player, int p_line)
{
	double line = calc_line(p_line, 0.25);
	gui->add(new s_entry(new t_text_entry(get_text("entry name"), &(player->name), DARK_GREY,//name
				&(gui->entry),
				gui->unit * t_vect(b_pos[0], line),
				gui->unit * t_vect(b_pos[3] + b_size[3] - b_pos[0], 1),
				3, color[0], color[1], color[2])));
}

void			create_level_iterator(t_gui *gui, t_actor *player, int p_line)
{
	double line = calc_line(p_line, 0.25);
	gui->add(new s_iterator(
				new t_text_button(get_text("level"), DARK_GREY, //level
					gui->unit * t_vect(b_pos[0], line), gui->unit * t_vect(b_size[0], 1), 3,
					color[0], color[1]),
				NULL,
				new t_text_button(NULL, DARK_GREY, //value button
								gui->unit * t_vect(b_pos[2], line), gui->unit * t_vect(b_size[2], 1), 3,
								color[0], color[1]),
				NULL,
				&(player->level), 0, 0, 0,
				&(player->attrib_point), 0));
}

void			create_health_iterator(t_gui *gui, t_actor *player, int p_line)
{
	double line = calc_line(p_line, 0.25);
	gui->add(new s_iterator(
				new t_text_button(get_text("health"), DARK_GREY, //health
					gui->unit * t_vect(b_pos[0], line), gui->unit * t_vect(b_size[0], 1), 3,
					color[0], color[1]),
				new t_text_button(get_text("-"), DARK_GREY, //minus button
					gui->unit * t_vect(b_pos[1], line), gui->unit * t_vect(b_size[1], 1), 3,
					color[0], color[1]),
				new t_text_button(NULL, DARK_GREY, //value button
					gui->unit * t_vect(b_pos[2], line), gui->unit * t_vect(b_size[2], 1), 3,
					color[0], color[1]),
				new t_text_button(get_text("+"), DARK_GREY, //plus button
					gui->unit * t_vect(b_pos[3], line), gui->unit * t_vect(b_size[3], 1), 3,
					color[0], color[1]),
				&(player->stat.hp.max), 5, 15, 150,
				&(player->attrib_point), 1));
}

void			create_pa_iterator(t_gui *gui, t_actor *player, int p_line)
{
	double line = calc_line(p_line, 0.25);
	gui->add(new s_iterator(
				new t_text_button(get_text("pa"), DARK_GREY, //pa
								gui->unit * t_vect(b_pos[0], line), gui->unit * t_vect(b_size[0], 1), 3,
								color[0], color[1]),
							new t_text_button(get_text("-"), DARK_GREY, //minus button
								gui->unit * t_vect(b_pos[1], line), gui->unit * t_vect(b_size[1], 1), 3,
								color[0], color[1]),
							new t_text_button(NULL, DARK_GREY, //value button
								gui->unit * t_vect(b_pos[2], line), gui->unit * t_vect(b_size[2], 1), 3,
								color[0], color[1]),
							new t_text_button(get_text("+"), DARK_GREY, //plus button
								gui->unit * t_vect(b_pos[3], line), gui->unit * t_vect(b_size[3], 1), 3,
								color[0], color[1]),
							&(player->stat.pa.max), 1, 4, 12,
							&(player->attrib_point), 5));
}

void			create_pm_iterator(t_gui *gui, t_actor *player, int p_line)
{
	double line = calc_line(p_line, 0.25);
	gui->add(new s_iterator(	new t_text_button(get_text("pm"), DARK_GREY, //pm
								gui->unit * t_vect(b_pos[0], line), gui->unit * t_vect(b_size[0], 1), 3,
								color[0], color[1]),
							new t_text_button(get_text("-"), DARK_GREY, //minus button
								gui->unit * t_vect(b_pos[1], line), gui->unit * t_vect(b_size[1], 1), 3,
								color[0], color[1]),
							new t_text_button(NULL, DARK_GREY, //value button
								gui->unit * t_vect(b_pos[2], line), gui->unit * t_vect(b_size[2], 1), 3,
								color[0], color[1]),
							new t_text_button(get_text("+"), DARK_GREY, //plus button
								gui->unit * t_vect(b_pos[3], line), gui->unit * t_vect(b_size[3], 1), 3,
								color[0], color[1]),
							&(player->stat.pm.max), 1, 3, 8,
							&(player->attrib_point), 3));
}

void			create_init_iterator(t_gui *gui, t_actor *player, int p_line)
{
	double line = calc_line(p_line, 0.25);
	gui->add(new s_iterator(	new t_text_button(get_text("init"), DARK_GREY, //initiative
							gui->unit * t_vect(b_pos[0], line), gui->unit * t_vect(b_size[0], 1), 3,
							color[0], color[1]),
						new t_text_button(get_text("-"), DARK_GREY, //minus button
							gui->unit * t_vect(b_pos[1], line), gui->unit * t_vect(b_size[1], 1), 3,
							color[0], color[1]),
						new t_text_button(NULL, DARK_GREY, //value button
							gui->unit * t_vect(b_pos[2], line), gui->unit * t_vect(b_size[2], 1), 3,
							color[0], color[1]),
						new t_text_button(get_text("+"), DARK_GREY, //plus button
							gui->unit * t_vect(b_pos[3], line), gui->unit * t_vect(b_size[3], 1), 3,
							color[0], color[1]),
						&(player->stat.ini.max), 2, 50, 150,
						&(player->attrib_point), 1));
}

void			create_atk_phy_iterator(t_gui *gui, t_actor *player, int p_line)
{
	double line = calc_line(p_line, 0.25);
		gui->add(new s_iterator(	new t_text_button(get_text("atk_phy"), DARK_GREY, //atk phy
									gui->unit * t_vect(b_pos[0], line), gui->unit * t_vect(b_size[0], 1), 3,
									color[0], color[1]),
								new t_text_button(get_text("-"), DARK_GREY, //minus button
									gui->unit * t_vect(b_pos[1], line), gui->unit * t_vect(b_size[1], 1), 3,
									color[0], color[1]),
								new t_text_button(NULL, DARK_GREY, //value button
									gui->unit * t_vect(b_pos[2], line), gui->unit * t_vect(b_size[2], 1), 3,
									color[0], color[1]),
								new t_text_button(get_text("+"), DARK_GREY, //plus button
									gui->unit * t_vect(b_pos[3], line), gui->unit * t_vect(b_size[3], 1), 3,
									color[0], color[1]),
								&(player->stat.phy.atk), 1, 0, 12,
								&(player->attrib_point), 2));
}

void			create_atk_mag_iterator(t_gui *gui, t_actor *player, int p_line)
{
	double line = calc_line(p_line, 0.25);
	gui->add(new s_iterator(	new t_text_button(get_text("atk_mag"), DARK_GREY, //atk mag
								gui->unit * t_vect(b_pos[0], line), gui->unit * t_vect(b_size[0], 1), 3,
								color[0], color[1]),
							new t_text_button(get_text("-"), DARK_GREY, //minus button
								gui->unit * t_vect(b_pos[1], line), gui->unit * t_vect(b_size[1], 1), 3,
								color[0], color[1]),
							new t_text_button(NULL, DARK_GREY, //value button
								gui->unit * t_vect(b_pos[2], line), gui->unit * t_vect(b_size[2], 1), 3,
								color[0], color[1]),
							new t_text_button(get_text("+"), DARK_GREY, //plus button
								gui->unit * t_vect(b_pos[3], line), gui->unit * t_vect(b_size[3], 1), 3,
								color[0], color[1]),
							&(player->stat.mag.atk), 1, 0, 12,
							&(player->attrib_point), 2));
}

void			create_def_phy_iterator(t_gui *gui, t_actor *player, int p_line)
{
	double line = calc_line(p_line, 0.25);
	gui->add(new s_iterator(	new t_text_button(get_text("def_phy"), DARK_GREY, //def phy
								gui->unit * t_vect(b_pos[0], line), gui->unit * t_vect(b_size[0], 1), 3,
								color[0], color[1]),
							new t_text_button(get_text("-"), DARK_GREY, //minus button
								gui->unit * t_vect(b_pos[1], line), gui->unit * t_vect(b_size[1], 1), 3,
								color[0], color[1]),
							new t_text_button(NULL, DARK_GREY, //value button
								gui->unit * t_vect(b_pos[2], line), gui->unit * t_vect(b_size[2], 1), 3,
								color[0], color[1]),
							new t_text_button(get_text("+"), DARK_GREY, //plus button
								gui->unit * t_vect(b_pos[3], line), gui->unit * t_vect(b_size[3], 1), 3,
								color[0], color[1]),
							&(player->stat.phy.def), 1, 0, 12,
							&(player->attrib_point), 2));
}

void			create_def_mag_iterator(t_gui *gui, t_actor *player, int p_line)
{
	double line = calc_line(p_line, 0.25);
	gui->add(new s_iterator(	new t_text_button(get_text("def_mag"), DARK_GREY, //def mag
								gui->unit * t_vect(b_pos[0], line), gui->unit * t_vect(b_size[0], 1), 3,
								color[0], color[1]),
							new t_text_button(get_text("-"), DARK_GREY, //minus button
								gui->unit * t_vect(b_pos[1], line), gui->unit * t_vect(b_size[1], 1), 3,
								color[0], color[1]),
							new t_text_button(NULL, DARK_GREY, //value button
								gui->unit * t_vect(b_pos[2], line), gui->unit * t_vect(b_size[2], 1), 3,
								color[0], color[1]),
							new t_text_button(get_text("+"), DARK_GREY, //plus button
								gui->unit * t_vect(b_pos[3], line), gui->unit * t_vect(b_size[3], 1), 3,
								color[0], color[1]),
							&(player->stat.mag.def), 1, 0, 12,
							&(player->attrib_point), 2));
}

void			create_pool_iterator(t_gui *gui, t_actor *player, int p_line)
{
	double line = calc_line(p_line, 0.25);
	gui->add(new s_iterator(	new t_text_button(get_text("pool point"), DARK_GREY, //pool point
								gui->unit * t_vect(b_pos[0], line), gui->unit * t_vect(b_size[0], 1), 3,
								color[0], color[1]),
						NULL,
						new t_text_button(NULL, DARK_GREY,
								gui->unit * t_vect(b_pos[2], line), gui->unit * t_vect(b_size[2], 1), 3,
								color[0], color[1]),
						NULL,
						&(player->attrib_point), 0, 0, 0,
						NULL, 0));
}
