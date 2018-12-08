#include "taag.h"
#include "base_value.h"

					s_game_board::s_game_board()
{
	map_size = t_vertex(0, 0, 0);
}
					s_game_board::s_game_board(string p_path)
{
	int				x, y, z, t;
	ifstream		file;
	vector<string>	line;

	map_size = t_vertex(0, 0, 0);
	file.open(p_path);
	if (file.good() == false)
		error_exit("Can't open a map at : " + p_path, 12342);
	while (!(file.eof()))
	{
		line = get_strsplit(&file, ":", -1);
		if (line.size() == 0 || line[0] == "blue" || line[0] == "red")
			break;
		x = atoi(line[0].c_str());
		y = atoi(line[1].c_str());
		z = atoi(line[2].c_str());
		t = atoi(line[3].c_str());
		if (board.size() <= x)
		{
			board.resize(x + 1);
			if (map_size.x < x + 1)
				map_size.x = x + 1;
		}
		if (board[x].size() <= y)
		{
			board[x].resize(y + 1);
			if (map_size.y < y + 1)
				map_size.y = y + 1;
		}
		if (map_size.z < z + 1)
			map_size.z = z + 1;
		if (t >= node_list.size())
			t = 0;
		board[x][y] = s_cell(t_vertex(x, y, z), node_list[t], NULL);
	}
	while (!(file.eof()))
	{
		if (line.size() != 3 || (line[0] != "blue" && line[0] != "red"))
			break;
		board[atoi(line[1].c_str())][atoi(line[2].c_str())].cursor = (line[0] == "blue" ? t_vect(1, 3) : t_vect(2, 3));
		line = get_strsplit(&file, ":", -1);
	}
}