#include "template.h"

map< int, TTF_Font *> 						font_list;
vector<vector<vector<vector<t_image *>>>>	char_list;
SDL_Color									g_color_tab[NB_COLOR];

static SDL_Color	create_color(int r, int g, int b, int a)
{
	SDL_Color color;

	color.r = r;
	color.g = g;
	color.b = b;
	color.a = a;
	return (color);
}

int					calc_text_size(string p_text, t_vect p_size)
{
	int text_size = 1;
	string text = p_text;

	if (p_text == "")
		text = "mmmmmmmmmmmmmmmmmmmmmmmmm";
	while (calc_text_len(p_text, text_size + 1, NORMAL) < p_size.x)
		text_size++;
	while (get_char(text_size, NORMAL, BLACK, 'M')->surface->h > p_size.y)
		text_size--;
	return (text_size);
}

void				set_color_tab(void)
{
	g_color_tab[BLACK] = create_color(39, 39, 39, 42);
	g_color_tab[WHITE] = create_color(240, 240, 240, 42);
	g_color_tab[LIGHT_BLUE] = create_color(135, 206, 250, 42);
	g_color_tab[BLUE] = create_color(30, 144, 255, 42);
	g_color_tab[DARK_BLUE] = create_color(0, 0, 139, 42);
	g_color_tab[LIGHT_RED] = create_color(221, 110, 110, 42);
	g_color_tab[RED] = create_color(165, 89, 89, 42);
	g_color_tab[DARK_RED] = create_color(110, 70, 70, 42);
	g_color_tab[LIGHT_GREEN] = create_color(170, 220, 115, 42);
	g_color_tab[GREEN] = create_color(89, 165, 89, 42);
	g_color_tab[DARK_GREEN] = create_color(30, 100, 60, 42);
	g_color_tab[LIGHT_CYAN] = create_color(127, 255, 212, 42);
	g_color_tab[CYAN] = create_color(64, 224, 208, 42);
	g_color_tab[DARK_CYAN] = create_color(0, 139, 139, 42);
	g_color_tab[LIGHT_GREY] = create_color(175, 175, 175, 42);
	g_color_tab[GREY] = create_color(86, 86, 86, 42);
	g_color_tab[DARK_GREY] = create_color(56, 56, 56, 42);
	g_color_tab[LIGHT_ORANGE] = create_color(255, 195, 0, 42);
	g_color_tab[ORANGE] = create_color(255, 165, 0, 42);
	g_color_tab[DARK_ORANGE] = create_color(255, 130, 0, 42);
	g_color_tab[LIGHT_YELLOW] = create_color(255, 250, 205, 42);
	g_color_tab[YELLOW] = create_color(255, 228, 181, 42);
	g_color_tab[DARK_YELLOW] = create_color(255, 255, 0, 42);
}

static SDL_Color	get_color(int i)
{
	if (i < 0 || i > NB_COLOR)
		return (g_color_tab[0]);
	return (g_color_tab[i]);
}

t_image				*get_char(int size, int style, int p_color, char c)
{
	string text;

	if (char_list.size() <= (size_t)size)
		char_list.resize(size + 1);
	if (char_list[size].size() <= (size_t)style)
		char_list[size].resize(style + 1);
	if (char_list[size][style].size() <= (size_t)p_color)
		char_list[size][style].resize(p_color + 1);
	if (char_list[size][style][p_color].size() <= (size_t)c)
		char_list[size][style][p_color].resize(c + 1);
	if (char_list[size][style][p_color][c] == NULL)
	{
		if (font_list.find(size) == font_list.end())
			font_list[size] = TTF_OpenFont(FONT_PATH, size);
		text = c + '\0';
		char_list[size][style][p_color][c] = new t_image(TTF_RenderText_Blended(font_list[size], text.c_str(), get_color(p_color)));
	}
	return (char_list[size][style][p_color][c]);
}
