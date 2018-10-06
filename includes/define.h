#ifndef DEFINE_H
# define DEFINE_H

# define FONT_PATH		"ressources/font/MonospaceTypewriter.ttf"
# define FONT_SIZE		get_win_size().y / 60

# define NB_SIZE		30

# define NB_COLOR		23
# define BLACK			0
# define WHITE			1
# define LIGHT_BLUE		2
# define BLUE			3
# define DARK_BLUE		4
# define LIGHT_RED		5
# define RED			6
# define DARK_RED		7
# define LIGHT_GREEN	8
# define GREEN			9
# define DARK_GREEN		10
# define LIGHT_CYAN		11
# define CYAN			12
# define DARK_CYAN		13
# define LIGHT_GREY		14
# define GREY			15
# define DARK_GREY		16
# define LIGHT_ORANGE	17
# define ORANGE			18
# define DARK_ORANGE	19
# define LIGHT_YELLOW	20
# define YELLOW			21
# define DARK_YELLOW	22

# define NB_STYLE		4
# define NORMAL			0
# define BOLD			1
# define ITALIC			2
# define UNDERLINE		3

# define BORDER			3

# define SCREEN_RATIO_X	0.6
# define SCREEN_RATIO_Y	0.6

# define NB_CHANNEl		10

# define ACTOR_PATH		"ressources/actor"
# define ACTOR_EXT		".act"

#ifdef _WIN32
#	define strtok_r strtok_s
#endif

#endif
