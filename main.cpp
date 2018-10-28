 #include "taag.h"

int main(int argc, char **argv)
{
	if (argc != 1)
		return (1);

	window_initialisation(argv[0]);

	prepare_screen();

	t_vect rect1 = t_vect(150, 150);
	t_vect rect2 = t_vect(450, 250);

	draw_rectangle(rect1, rect2, t_color(0.3, 0.3, 0.3));
	draw_paragraphe("ceci est un test yolo", rect1, rect2, NORMAL, DARK_RED);

	render_screen();
	
	getchar();

	//menu_start();

	return 0;
}
