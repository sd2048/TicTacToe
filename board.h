#if !defined(BOARD_H)
#define BOARD_H

#include "consts.h"

enum b_square {empty, xed = 2, oed = 5};

class Board
{
	b_square matrix[3][3];
	int count;

	inline bool IsCorner(void)
	{
		return(matrix[0][0] + matrix[0][2] + matrix[2][0] + matrix[2][2] == oed);
	}

	inline bool IsCenter(void)
	{
		return(matrix[1][1] == oed);
	}

	inline int abs(int x)
	{
		return(x<0 ? -x : x);
	}

	inline int GetGoodMove(b_square barr[3])
	{
		return GetGoodMove(barr[0], barr[1], barr[2]);
	}

	inline int GetBestMove(b_square barr[3])
	{
		return GetBestMove(barr[0], barr[1], barr[2]);
	}

	int GetBestMove(b_square b1, b_square b2, b_square b3)
	{
		if (b1+b2+b3 == 4) return(!b1 ? 1 : !b2 ? 2 : 3);
		return 0;
	}

	int GetGoodMove(b_square b1, b_square b2, b_square b3)
	{
		if (b1+b2+b3 == 10) return(!b1 ? 1 : !b2 ? 2 : 3);
		return 0;
	}

public:

    bool isSmart;
	Board(){ count = 0; isSmart = true; } ~Board(){}
	int SetSquare(int x, int y, int val)
	{
		if (x<0||x>2||y<0||y>2) return 0;
		matrix[x][y] = val ? oed : xed;
		SetWindowText(hwndSquare[x][y], val ? "o" : "x");
	}
	void CreateBoard(HWND hwnd)
	{
		int x, y;
		for (x=0; x<3; x++)
			for (y=0; y<3; y++) {
				hwndSquare[x][y] = CreateWindow("STATIC", "", WS_CHILD | WS_VISIBLE | WS_BORDER | SS_CENTER | SS_NOTIFY, padding+x*perRow, padding+y*perRow, perRow, perRow, hwnd, (HMENU)(x*3+y), NULL, NULL);
				SetWindowFont(hwndSquare[x][y], hfont, 1);
			}
	}
	bool Play(int x, int y)
	{
		if (matrix[x][y]!=empty) return true;
		SetSquare(x, y, 1);
		count++;
		return false;
	}
	bool CheckWin(void)
	{
		int x,y; bool win=false; bool lose=false; int result=0;
		for (x=0; x<3; x++)
		{
			if (matrix[x][0]==xed&&matrix[x][1]==xed&&matrix[x][2]==xed||matrix[0][x]==xed&&matrix[1][x]==xed&&matrix[2][x]==xed) lose=true;
			if (matrix[x][0]==oed&&matrix[x][1]==oed&&matrix[x][2]==oed||matrix[0][x]==oed&&matrix[1][x]==oed&&matrix[2][x]==oed) win=true;
		}
		if (matrix[0][0]==xed&&matrix[1][1]==xed&&matrix[2][2]==xed||matrix[0][2]==xed&&matrix[1][1]==xed&&matrix[2][0]==xed) lose=true;
		if (matrix[0][0]==oed&&matrix[1][1]==oed&&matrix[2][2]==oed||matrix[0][2]==oed&&matrix[1][1]==oed&&matrix[2][0]==oed) win=true;
		if (lose)
		{
			result = MessageBox(hwnd, "Sorry, You Lose.\nPlay again?\n(This time you might win!)", "You Lose", MB_YESNO | MB_ICONEXCLAMATION);
			if (result == IDNO) exit(0);
			else return(true);
		}
		else if (win)
		{
			result = MessageBox(hwnd, "YOU WIN!!\nPlay again?\n(This you might win again!)", "You Win", MB_YESNO | MB_ICONASTERISK);
			if (result == IDNO) exit(0);
			else return(true);
		}
		else
		{
			for (x=0;x<3;x++)
				for(y=0;y<3;y++)
					if (matrix[x][y]==empty) win=true;
			if (!win)
			{
				result = MessageBox(hwnd, "Tie!\nPlay again?\n(This time you might win!)", "Tie", MB_YESNO | MB_ICONASTERISK);
				if (result == IDNO) exit(0);
			    else return(true);
			}
		}
		return(false);
	}
	void ClearAll(void)
	{
		count = 0;
		for (int x=0; x<3; x++)
			for (int y=0; y<3; y++)
			{
				matrix[x][y] = empty;
				SetWindowText(hwndSquare[x][y], "");
			}
	}
	void Move(void)
	{
		int x, y;
		bool find = true;
		int move[2];

		if (isSmart)
		{
			if (count == 1 && IsCorner())
			{
				move[0] = move[1] = 1;
				goto end;
			}
			if (count == 1 && IsCenter())
			{
				move[0] = move[1] = 0;
				goto end;
			}

			for (x=0; x<3; x++)
			{
				if (y=GetBestMove(matrix[x]))
				{
					move[0] = x;
					move[1] = y-1;
					goto end;
				}
				if (y=GetBestMove(matrix[0][x], matrix[1][x], matrix[2][x]))
				{
					move[0] = y-1;
					move[1] = x;
					goto end;
				}
			}

			for (x=0; x<3; x++)
			{
				if (y=GetGoodMove(matrix[x]))
				{
					move[0] = x;
					move[1] = y-1;
					goto end;
				}
				if (y=GetGoodMove(matrix[0][x], matrix[1][x], matrix[2][x]))
				{
					move[0] = y-1;
					move[1] = x;
					goto end;
				}
			}


			if (y=GetGoodMove(matrix[0][0], matrix[1][1], matrix[2][2]))
			{
				move[0] = move[1] = y-1;
				goto end;
			}

			if (y=GetGoodMove(matrix[0][2], matrix[1][1], matrix[2][0]))
			{
				move[0] = y-1;
				move[1] = 3-y;
				goto end;
			}
		}

		do
		{
			do
			{
				x = rand();
			} while (x >= RAND_MAX-RAND_MAX%9);
			x %= 9;
		} while (matrix[x/3][x%3]!=empty);
		move[0] = x/3; move[1] = x%3;
		
end:
		SetSquare(move[0], move[1], 0);
		if (CheckWin())
			ClearAll();
	}
};

#endif