#if !defined(CONSTS_H)
#define CONSTS_H

const int perRow = 100;
const int padding = 50;

HFONT hfont = CreateFontA(100, 0, 0, 0, FW_NORMAL, 0, 0, 0, DEFAULT_CHARSET, OUT_CHARACTER_PRECIS, CLIP_DEFAULT_PRECIS, PROOF_QUALITY, FF_DONTCARE, NULL);
HWND hwndSquare[3][3];
HWND hwnd;

#endif