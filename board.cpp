enum b_square {empty, xed, oed};

class Board
{
	b_square matrix[3][3];

public:

	Board(){} ~Board(){}
	int SetSquare(int x, int y, b_square fillval)
	{
		if (x<0||x>2||y<0||y>2) return 0;
		matrix[x][y] = fillval;
	}
};