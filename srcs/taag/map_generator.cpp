#include "taag.h"

t_game_board		map_generator(int p_x, int p_y)
{
	t_game_board	board = t_game_board();
	int x;
	int y;
	int z = 0;

	y = 0;
	while (y < p_y)
	{
		x = 0;
		while (x < p_x)
		{
			if (board.board.size() <= x)
			{
				board.board.resize(x + 1);
				if ((board.map_size).x < x + 1)
					(board.map_size).x = x + 1;
			}
			if (board.board[x].size() <= y)
			{
				board.board[x].resize(y + 1);
				if ((board.map_size).y < y + 1)
					(board.map_size).y = y + 1;
			}
			if ((board.map_size).z < z + 1)
				(board.map_size).z = z + 1;
			board.board[x][y] = s_cell(t_vertex(x, y, z), 0, NULL);
			x++;
		}
		y++;
	}
	return (board);
}
