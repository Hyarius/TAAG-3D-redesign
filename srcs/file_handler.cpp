#include "template.h"

string					get_str(ifstream *myfile)
{
    string line;

	if (myfile->eof())
		return ("");
    getline(*myfile, line);
	if (line.size() == 0)
		return ("");
    if (line[strlen((char *)line.c_str()) - 1] == '\n')
        line[strlen((char *)line.c_str()) - 1] = '\0';
    return (line);
}

vector<string>			get_strsplit(ifstream *myfile, const string c, int size)
{
    vector<string> tab;
    string line;
    string saved_line;
    char	*word;
	char	*context = NULL;

    line = get_str(myfile);
	if (line == "")
	{
		tab.resize(0);
		return (tab);
	}
	saved_line = line;
    word = strtok_r((char *)(line.c_str()), c.c_str(), &context);
    while(word != NULL)
    {
        tab.push_back(word);
        word = strtok_r(NULL, c.c_str(), &context);
    }
	if ((int)(tab.size()) != size)
		error_exit("Bad splited line (" + saved_line + ")!", 134);
    return tab;
}
