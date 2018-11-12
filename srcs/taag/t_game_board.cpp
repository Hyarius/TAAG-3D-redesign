#include "taag.h"
#include "base_value.h"

					s_game_board::s_game_board(string p_path)
{
	int				x, y, z, t;
	ifstream		file;
	vector<string>	line;

	size = t_vect(0, 0);
	file.open(p_path);
	if (file.good() == false)
		error_exit("Can't open a map at : " + p_path, 12342);
	int i = 0;
	while (!(file.eof()))
	{
		line = get_strsplit(&file, ":", 4);
		if (line.size() == 0)
			break;
		x = atoi(line[0].c_str());
		y = atoi(line[1].c_str());
		z = atoi(line[2].c_str());
		t = atoi(line[3].c_str());
		if (board.size() <= x)
		{
			board.resize(x + 1);
			if (size.x < x + 1)
				size.x = x + 1;
		}
		if (board[x].size() <= y)
		{
			board[x].resize(y + 1);
			if (size.y < y + 1)
				size.y = y + 1;
		}
		board[x][y] = s_cell(t_vertex(x, y, z), node_list[t], NULL);
	}
}
