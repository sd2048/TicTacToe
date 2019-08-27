#include "projheader.h"

Board board;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	MSG msg;
	WNDCLASS wc;
	
	wc.style         = CS_HREDRAW | CS_VREDRAW;
	wc.cbClsExtra    = 0;
	wc.cbWndExtra    = 0;
	wc.lpszClassName = "Tic Tac Toe!";
	wc.hInstance     = hInstance;
	wc.hbrBackground = GetSysColorBrush(COLOR_3DFACE);
	wc.lpszMenuName  = NULL;
	wc.lpfnWndProc   = WndProc;
	wc.hCursor       = LoadCursor(NULL, IDC_ARROW);
	wc.hIcon         = (HICON)LoadImage(NULL, "TicTacToe\\icon1.ico", IMAGE_ICON|LR_LOADFROMFILE, 0, 0, LR_DEFAULTSIZE);

	RegisterClass(&wc);
	hwnd = CreateWindow( wc.lpszClassName, wc.lpszClassName,
		WS_OVERLAPPEDWINDOW | WS_VISIBLE,
		GetSystemMetrics(SM_CXSCREEN)/2-padding-perRow*2, GetSystemMetrics(SM_CYSCREEN)/2-padding-perRow*2,
		padding*2+perRow*3+20, padding*2+perRow*3+34, NULL, NULL, hInstance, NULL);  

	ShowWindow(hwnd, nCmdShow);
	UpdateWindow(hwnd);

	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return (int) msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	static HMENU hMenu;
	switch(msg)  
	{
		case WM_CREATE:
			board.CreateBoard(hwnd);
			{
				HMENU hMenubar;

				hMenubar = CreateMenu();
				hMenu = CreateMenu();
				
				AppendMenuW(hMenu, MF_STRING, 9, L"&Smart");
				CheckMenuItem(hMenu, 9, MF_CHECKED);

				AppendMenuW(hMenubar, MF_POPUP, (UINT_PTR)hMenu, L"&Settings");
				SetMenu(hwnd, hMenubar);
			}
			srand(time(NULL));
			break;
		case WM_COMMAND:
			if (LOWORD(wParam) == 9)
			{
				if (board.isSmart)
				{
					CheckMenuItem(hMenu, 9, MF_UNCHECKED);
					board.isSmart = false;
				}
				else
				{
					CheckMenuItem(hMenu, 9, MF_CHECKED);
					board.isSmart = true;
				}
			}
			else if (HIWORD(wParam) == STN_CLICKED)
			{
				if (board.Play(LOWORD(wParam)/3, LOWORD(wParam)%3))
					MessageBox(hwnd, "Can't move there!", "NO!", MB_OK | MB_ICONHAND);
				else
				{
					if (board.CheckWin())
						board.ClearAll();
					else
					    board.Move();
				}
			}
			break;
		case WM_DESTROY:
			PostQuitMessage(0);
			return 0;
	}
	return DefWindowProc(hwnd, msg, wParam, lParam);
}

