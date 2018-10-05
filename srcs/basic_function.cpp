#include "template.h"

int					get_root(int size)
{
	int		i;

	i = 1;
	while ((i + 1) * (i + 1) <= size)
		i++;
	return (i);
}

void				error_exit(string msg, int error)
{
	printf("Error %d : %s\n", error, msg.c_str());
	getchar();
	exit(error);
}

void				set_sdl_rect(SDL_Rect *rect, int x, int y, int w, int h)
{
	rect->x = x;
	rect->y = y;
	rect->w = w;
	rect->h = h;
}

void				get_leaks(string msg)
{
	//system("clear");
	system("leaks TAAG 2>/dev/null | grep 'total leaked bytes'");
	cout << msg << "\n\n\n"<< endl;
	//getchar();
}

t_vect				get_mouse_coord()
{
	t_vect mouse;

	SDL_GetMouseState(&mouse.x, &mouse.y);
	return(mouse);
}

vector<string>        strsplit(string input, const string c)
{
    vector<string> tab;
	char	*line;
	char	*context = NULL;
    char	*word;

    line = (char *)(input.c_str());
    word = strtok_r(line, c.c_str(), &context);
    while(word != NULL)
    {
        tab.push_back(word);
        word = strtok_r(NULL, c.c_str(), &context);
    }
    return tab;
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
		if (brut_files[i].find(extension) != string::npos)
			files.push_back(strsplit(brut_files[i], extension)[0]);
		i++;
	}
	return files;
}
