#include "taag.h"

					s_node::s_node(string p_path)
{
	ifstream		file;
	vector<string>	line;

	file.open(p_path);
	if (file.good() == false)
		error_exit("Can't open a node at : " + p_path, 12342);
	name = get_strsplit(&file, ":", 2)[1];
	cost = atoi(get_strsplit(&file, ":", 2)[1].c_str());
	index = atoi(get_strsplit(&file, ":", 2)[1].c_str());
	line = get_strsplit(&file, ":", 3);
	pos = t_vect(atoi(line[1].c_str()), atoi(line[2].c_str()));
	file.close();
}
