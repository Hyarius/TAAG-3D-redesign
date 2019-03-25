#include "taag.h"

int main(int argc, char **argv)
{
	if (argc != 1)
		return (1);
	window_initialisation(argv[0]);
	menu_start();

	return 0;
}
