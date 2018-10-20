#ifndef DEFINE_H
# define DEFINE_H

# define FONT_PATH		"ressources/font/MonospaceTypewriter.ttf"
# define FONT_SIZE		get_win_size().y / 60

# define SCREEN_RATIO_X	0.6
# define SCREEN_RATIO_Y	0.6

# define NB_CHANNEl		10

#ifdef _WIN32
#	define strtok_r strtok_s
#endif

# define ACTOR_EXT		".act"

#endif
