#include "taag.h"
#include "player_editor_helper.h"

t_color			color[3] = {t_color(0.5, 0.5, 0.5),
							t_color(0.6, 0.6, 0.6),
							t_color(1.0, 1.0, 0.7)};

t_vect			offset = t_vect(SCREEN_RATIO_X * 8.0 - 4.0, SCREEN_RATIO_Y * 8.0 - 4.0);
double			space = 0.25;
double			line_height = (20 - (offset.x * 2) - space * 14) / 13;
vector<double>	b_pos;
vector<double>	b_size;
vector<t_vect>	c_pos;
t_vect			c_size = t_vect(((30 - offset.x * 2) / 2.0) / 4.0, (16 - offset.y * 2) / 2.0 - space * 3 / 2.0);


static double	calc_line(double line, double space)
{
	double result;

	result = space + ((line_height + space) * line) + offset.y;
	return (result);
}

void			set_b_value()
{
	b_pos.resize(8);
	b_size.resize(8);

	b_pos[0] = space + offset.x;
	b_size[0] = 6.75;

	b_pos[1] = b_pos[0] + b_size[0] + space;
	b_size[1] = line_height;

	b_pos[2] = b_pos[1] + b_size[1] + space;
	b_size[2] = line_height * 1.5;

	b_pos[3] = b_pos[2] + b_size[2] + space;
	b_size[3] = line_height;

	b_pos[4] = b_pos[0];
	b_size[4] = (b_pos[3] + b_size[3] - b_pos[0]) / 4 - space + space / 4;

	b_pos[5] = b_pos[4] + b_size[4] + space;
	b_size[5] = b_size[4];

	b_pos[6] = b_pos[5] + b_size[5] + space;
	b_size[6] = b_size[5];

	b_pos[7] = b_pos[6] + b_size[6] + space;
	b_size[7] = b_size[6];
}

void			set_c_value()
{
	c_pos.resize(8);

	double base = b_pos[7] + b_size[7] + space;
	c_pos[0] = t_vect(base + (c_size.x + space) * 0, offset.y + space + 4);
	c_pos[1] = t_vect(c_pos[0].x + (c_size.x + space) * 1, c_pos[0].y);
	c_pos[2] = t_vect(c_pos[0].x + (c_size.x + space) * 2, c_pos[0].y);
	c_pos[3] = t_vect(c_pos[0].x + (c_size.x + space) * 3, c_pos[0].y);
	c_pos[4] = t_vect(c_pos[0].x + (c_size.x + space) * 0, c_pos[0].y + space + c_size.y);
	c_pos[5] = t_vect(c_pos[0].x + (c_size.x + space) * 1, c_pos[0].y + space + c_size.y);
	c_pos[6] = t_vect(c_pos[0].x + (c_size.x + space) * 2, c_pos[0].y + space + c_size.y);
	c_pos[7] = t_vect(c_pos[0].x + (c_size.x + space) * 3, c_pos[0].y + space + c_size.y);
}

static void		create_card(t_gui *gui, t_actor *player, int i)
{
	gui->add(new s_spell_card(&(player->spell[i]), gui->unit * c_pos[i], gui->unit * c_size, NULL, NULL));
}

void			create_spell_cards(t_gui *gui, t_actor *player)
{
	size_t	i = 0;

	while (i < 8)
	{
		create_card(gui, player, i);
		i++;
	}
}

void			create_entry_name(t_gui *gui, t_actor *player, double p_line)
{
	double line = calc_line(p_line, space);

	s_entry *entry = new s_entry(new t_text_entry(get_text("entry name"),
				&(player->name), DARK_GREY,//name
				&(gui->entry),
				gui->unit * t_vect(b_pos[0], line),
				gui->unit * t_vect(b_pos[3] + b_size[3] - b_pos[0], line_height),
				3, color[0], color[1], color[2]));
	entry->entry->draw_funct = draw_centred_text;
	entry->entry->coord[2] = gui->unit * t_vect(b_pos[0] + (b_pos[3] + b_size[3] - b_pos[0]) / 2, line + line_height / 2);
	gui->add(entry);
}

void			create_file_entry(t_gui *gui, string *p_name, double p_line)
{
	double line = calc_line(p_line, space);

	s_entry *entry = new s_entry(new t_text_entry(get_text("entry file_name"),
				p_name, DARK_GREY,//name
				&(gui->entry),
				gui->unit * t_vect(b_pos[0], line),
				gui->unit * t_vect(b_pos[3] + b_size[3] - b_pos[0], line_height),
				3, color[0], color[1], color[2]));
	entry->entry->set_front(ACT_PATH);
	entry->entry->set_back(ACT_EXT);
	entry->entry->draw_funct = draw_centred_text;
	entry->entry->coord[2] = gui->unit * t_vect(b_pos[0] + (b_pos[3] + b_size[3] - b_pos[0]) / 2, line + line_height / 2);
	gui->add(entry);
}

void			create_level_iterator(t_gui *gui, t_actor *player, double p_line)
{
	double line = calc_line(p_line, space);
	gui->add(new s_iterator(new t_text_button(get_text("level"), DARK_GREY, //pool point
		gui->unit * t_vect(b_pos[0], line), gui->unit * t_vect(b_size[0], line_height), 3,
		color[0], color[1]),
		NULL,
		new t_text_button(NULL, DARK_GREY,
			gui->unit * t_vect(b_pos[1], line), gui->unit * t_vect(b_pos[3] - b_pos[1] + b_size[3], line_height), 3,
			color[0], color[1]),
		NULL,
		&(player->level), 0, 0, 0,
		NULL, 0, NULL));
}

void			create_pool_iterator(t_gui *gui, t_actor *player, double p_line)
{
	double line = calc_line(p_line, space);
	gui->add(new s_iterator(new t_text_button(get_text("pool point"), DARK_GREY, //pool point
		gui->unit * t_vect(b_pos[0], line), gui->unit * t_vect(b_size[0], line_height), 3,
		color[0], color[1]),
		NULL,
		new t_text_button(NULL, DARK_GREY,
			gui->unit * t_vect(b_pos[1], line), gui->unit * t_vect(b_pos[3] - b_pos[1] + b_size[3], line_height), 3,
			color[0], color[1]),
		NULL,
		&(player->attrib_point), 0, 0, 0,
		NULL, 0, NULL));
}

void			create_health_iterator(t_gui *gui, t_actor *player, double p_line)
{
	double line = calc_line(p_line, space);
	gui->add(new s_iterator(
				new t_text_button(get_text("health"), DARK_GREY, //health
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
				&(player->stat.hp.max), g_hp[0], g_hp[1], g_hp[2],
				&(player->attrib_point), 1, &(player->level)));
}

void			create_pa_iterator(t_gui *gui, t_actor *player, double p_line)
{
	double line = calc_line(p_line, space);
	gui->add(new s_iterator(
				new t_text_button(get_text("pa"), DARK_GREY, //pa
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

void			create_pm_iterator(t_gui *gui, t_actor *player, double p_line)
{
	double line = calc_line(p_line, space);
	gui->add(new s_iterator(	new t_text_button(get_text("pm"), DARK_GREY, //pm
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
							&(player->stat.pm.max), g_pm[0], g_pm[1], g_pm[2],
							&(player->attrib_point), 3, &(player->level)));
}

void			create_init_iterator(t_gui *gui, t_actor *player, double p_line)
{
	double line = calc_line(p_line, space);
	gui->add(new s_iterator(	new t_text_button(get_text("init"), DARK_GREY, //initiative
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
						&(player->stat.ini.max), g_init[0], g_init[1], g_init[2],
						&(player->attrib_point), 1, &(player->level)));
}

void			create_atk_phy_iterator(t_gui *gui, t_actor *player, double p_line)
{
	double line = calc_line(p_line, space);
		gui->add(new s_iterator(	new t_text_button(get_text("atk_phy"), DARK_GREY, //atk phy
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
								&(player->stat.phy.atk), g_atk_phy[0], g_atk_phy[1], g_atk_phy[2],
								&(player->attrib_point), 2, &(player->level)));
}

void			create_atk_mag_iterator(t_gui *gui, t_actor *player, double p_line)
{
	double line = calc_line(p_line, space);
	gui->add(new s_iterator(	new t_text_button(get_text("atk_mag"), DARK_GREY, //atk mag
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
							&(player->stat.mag.atk), g_atk_mag[0], g_atk_mag[1], g_atk_mag[2],
							&(player->attrib_point), 2, &(player->level)));
}

void			create_def_phy_iterator(t_gui *gui, t_actor *player, double p_line)
{
	double line = calc_line(p_line, space);
	gui->add(new s_iterator(	new t_text_button(get_text("def_phy"), DARK_GREY, //def phy
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
							&(player->stat.phy.def), g_def_phy[0], g_def_phy[1], g_def_phy[2],
							&(player->attrib_point), 2, &(player->level)));
}

void			create_def_mag_iterator(t_gui *gui, t_actor *player, double p_line)
{
	double line = calc_line(p_line, space);
	gui->add(new s_iterator(	new t_text_button(get_text("def_mag"), DARK_GREY, //def mag
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
							&(player->stat.mag.def), g_def_mag[0], g_def_mag[1], g_def_mag[2],
							&(player->attrib_point), 2, &(player->level)));
}

void			create_save_button(t_gui *gui, t_actor *player, double p_line, string *p_path)
{
	double line = calc_line(p_line, space);
	gui->add(new s_button(new t_text_button(get_text("save"), DARK_GREY, //pa
		gui->unit * t_vect(b_pos[4], line), gui->unit * t_vect(b_size[4], line_height), 3,
		color[0], color[1]), menu_save_actor, t_data(3, gui, player, p_path)));
}

void			create_load_button(t_gui *gui, t_actor *player, double p_line, string *p_path)
{
	double line = calc_line(p_line, space);
	gui->add(new s_button(new t_text_button(get_text("load"), DARK_GREY, //pa
		gui->unit * t_vect(b_pos[5], line), gui->unit * t_vect(b_size[5], line_height), 3,
		color[0], color[1]), menu_load_actor, t_data(3, gui, player, p_path)));
}

void			create_duplicate_button(t_gui *gui, t_actor *player, double p_line, string *p_path)
{
	double line = calc_line(p_line, space);
	gui->add(new s_button(new t_text_button(get_text("duplicate"), DARK_GREY, //pa
		gui->unit * t_vect(b_pos[6], line), gui->unit * t_vect(b_size[6], line_height), 3,
		color[0], color[1]), NULL, NULL));
}

void			create_erase_button(t_gui *gui, t_actor *player, double p_line, string *p_path)
{
	double line = calc_line(p_line, space);
	gui->add(new s_button(new t_text_button(get_text("erase"), DARK_GREY, //pa
		gui->unit * t_vect(b_pos[7], line), gui->unit * t_vect(b_size[7], line_height), 3,
		color[0], color[1]), NULL, NULL));
}
