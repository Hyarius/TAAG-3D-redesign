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

vector<string>		list_files(string path, string extension)
{
	vector<string>	brut_files;
	vector<string>	files;
	string			line;
	DIR				*dir = opendir(path.c_str());
	char	*context = NULL;

	size_t i = 2;
	struct dirent *dirent_ptr;

	while ((dirent_ptr = readdir(dir)) != NULL)
        brut_files.push_back(dirent_ptr->d_name);
	while (i < brut_files.size())
	{
		if (brut_files[i].find(extension.c_str(), 0, extension.size()) != string::npos)
			files.push_back(strsplit(brut_files[i], extension)[0]);
		i++;
	}
	return files;
}

bool				check_file_exist(string path, string name)
{
	vector<string>	brut_files;
	DIR				*dir = opendir(path.c_str());
	char			*context = NULL;

	size_t i = 2;
	struct dirent *dirent_ptr;

	while ((dirent_ptr = readdir(dir)) != NULL)
        brut_files.push_back(dirent_ptr->d_name);
	while (i < brut_files.size())
	{
		if (brut_files[i] == name)
			return (true);
		i++;
	}
	return (false);
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
