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
		board[x][y] = s_cell(t_vertex(x, y, z), node_list[t], NULL);
	}
}

void				save_map(t_data data)
{
	t_game_engine *board = ((t_game_engine *)(data.data[0]));
	string	p_path = MAP_PATH + *((string *)(data.data[1])) + MAP_EXT;

	ofstream myfile;
	myfile.open(p_path);
	int i = 0, j, h;
	while (i < board->board->map_size.y)
	{
		j = 0;
		while (j < board->board->map_size.x)
		{
			h = 0;
			while (h < node_list.size() && node_list[h] != board->board->board[i][j].node)
				h++;
			myfile << i << ":" << j << ":" << board->board->board[i][j].coord.z << ":" << h << "\n";
			j++;
		}
		i++;
	}
}
