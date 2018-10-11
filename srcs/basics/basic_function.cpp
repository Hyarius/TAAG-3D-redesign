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
