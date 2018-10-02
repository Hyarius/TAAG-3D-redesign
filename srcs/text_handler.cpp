#include "template.h"

map< int, TTF_Font *> font_list;
//map< int, map< int, map< int, map< int, SDL_Surface *> > > > char_list;
vector<vector<vector<vector<SDL_Surface *>>>> char_list;

SDL_Surface			*get_char(int size, int style, int p_color, char c)
{
	string text;

	if (char_list.size() <= size)
	{
		char_list.resize(size + 1);
		char_list[size].resize(style + 1);
		char_list[size][style].resize(p_color + 1);
		char_list[size][style][p_color].resize(c + 1);
	}
	else if (char_list[size].size() <= style)
	{
		char_list[size].resize(style + 1);
		char_list[size][style].resize(p_color + 1);
		char_list[size][style][p_color].resize(c + 1);
	}
	else if (char_list[size][style].size() <= p_color)
	{
		char_list[size][style].resize(p_color + 1);
		char_list[size][style][p_color].resize(c + 1);
	}
	else if (char_list[size][style][p_color].size() <= c)
		char_list[size][style][p_color].resize(c + 1);
	if (char_list[size][style][p_color][c] == NULL)
	{
		if (font_list.find(size) == font_list.end())
			font_list[size] = TTF_OpenFont(FONT_PATH, FONT_SIZE + size);
		text = c + '\0';
		char_list[size][style][p_color][c] = TTF_RenderText_Blended(font_list[size], text.c_str(), get_color(p_color));
	}
	return (char_list[size][style][p_color][c]);
}
