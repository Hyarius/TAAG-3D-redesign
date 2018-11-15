#include "taag.h"

int main(int argc, char **argv)
{
	if (argc != 1 && argc != 4)
		return (1);
	if (argc == 4)
		map_generator(argv[1], atoi(argv[2]), atoi(argv[3]));
	else
	{
		window_initialisation(argv[0]);
		menu_start();
	}
	return 0;
}
