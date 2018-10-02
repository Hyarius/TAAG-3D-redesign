#include "template.h"

SDL_Color			g_color_tab[NB_COLOR];
t_color				g_open_color_tab[NB_COLOR];

static SDL_Color	create_color(int r, int g, int b, int a)
{
	SDL_Color color;

	color.r = r;
	color.g = g;
	color.b = b;
	color.a = a;
	return (color);
}

static void			set_open_color(int i)
{

	g_open_color_tab[i].r = (double)(g_color_tab[i].r / 255.0);
	g_open_color_tab[i].g = (double)(g_color_tab[i].g / 255.0);
	g_open_color_tab[i].b = (double)(g_color_tab[i].b / 255.0);
}

static void			set_open_color_tab(void)
{
	set_open_color(BLACK);
	set_open_color(WHITE);
	set_open_color(LIGHT_BLUE);
	set_open_color(BLUE);
	set_open_color(DARK_BLUE);
	set_open_color(LIGHT_RED);
	set_open_color(RED);
	set_open_color(DARK_RED);
	set_open_color(LIGHT_GREEN);
	set_open_color(GREEN);
	set_open_color(DARK_GREEN);
	set_open_color(LIGHT_CYAN);
	set_open_color(CYAN);
	set_open_color(DARK_CYAN);
	set_open_color(LIGHT_GREY);
	set_open_color(GREY);
	set_open_color(DARK_GREY);
	set_open_color(LIGHT_ORANGE);
	set_open_color(ORANGE);
	set_open_color(DARK_ORANGE);
	set_open_color(LIGHT_YELLOW);
	set_open_color(YELLOW);
	set_open_color(DARK_YELLOW);
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
	set_open_color_tab();
}

SDL_Color			get_color(int i)
{
	if (i < 0 || i > NB_COLOR)
		return (g_color_tab[0]);
	return (g_color_tab[i]);
}

t_color				get_open_color(int i)
{
	if (i < 0 || i > NB_COLOR)
		return (g_open_color_tab[0]);
	return (g_open_color_tab[i]);
}