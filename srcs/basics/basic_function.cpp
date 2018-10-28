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
	string			val;
	int 			startIndex = 0;
	int 			endIndex = 0;

	while( (endIndex = input.find(c, startIndex)) < input.size() )
	{
		val = input.substr(startIndex, endIndex - startIndex);
		if (val.size())
			tab.push_back(val);
		startIndex = endIndex + c.size();
	}
	if(startIndex < input.size())
	{
		val = input.substr(startIndex);
		tab.push_back(val);
	}
	return (tab);
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
		p_color.r * 255, p_color.g * 255, p_color.b * 255, p_color.a * 255));

	return (surface);
}
