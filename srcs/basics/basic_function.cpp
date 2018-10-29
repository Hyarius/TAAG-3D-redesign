#include "template.h"

void				error_exit(string msg, int error)
{
	printf("Error %d : %s\n", error, msg.c_str());
	exit(error);
}

t_vect				get_mouse_coord()
{
	int		x;
	int		y;

	SDL_GetMouseState(&x, &y);
	return(t_vect(x, y));
}

vector<string>		strsplit(string input, string c)
{
	vector<string>	tab;
	string			line;
	string			saved_line;
	char			*word;
	char			*context = NULL;

	if (input == "")
	{
		tab.resize(0);
		return (tab);
	}
	word = strtok_r((char *)(input.c_str()), c.c_str(), &context);
	while (word != NULL)
	{
		if (word != c)
			tab.push_back(word);
		word = strtok_r(NULL, c.c_str(), &context);
	}
	return tab;
}

SDL_Surface			*create_surface_color(t_color p_color)
{
	SDL_Surface		*surface;
	Uint32			rmask, gmask, bmask, amask;

	#if SDL_BYTEORDER == SDL_BIG_ENDIAN
	    rmask = 0xff000000;
	    gmask = 0x00ff0000;
	    bmask = 0x0000ff00;
	    amask = 0x000000ff;
	#else
	    rmask = 0x000000ff;
	    gmask = 0x0000ff00;
	    bmask = 0x00ff0000;
	    amask = 0xff000000;
	#endif

    surface = SDL_CreateRGBSurface(0, 1, 1, 32, rmask, gmask, bmask, amask);
	SDL_FillRect(surface, NULL, SDL_MapRGBA(surface->format,
		(Uint8)(p_color.r * 255), (Uint8)(p_color.g * 255),
		(Uint8)(p_color.b * 255), (Uint8)(p_color.a * 255)));

	return (surface);
}
