#include "taag.h"

void			map_generator(string p_path, int p_x, int p_y)
{
	ofstream myfile;
	myfile.open(p_path);
	int i;
	int j;

	i = 0;
	while (i < p_y)
	{
		j = 0;
		while (j < p_x)
		{
			myfile << j << ":" << i << ":0:0\n";
			j++;
		}
		i++;
	}
}
