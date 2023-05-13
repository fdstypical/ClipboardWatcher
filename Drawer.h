#pragma once
#include "framework.h"

class Drawer
{
public:
	Drawer();
	~Drawer();

	void DrawImage(HDC hdc, HBITMAP bitmap);
	HBITMAP GetScreenImg(HWND hWnd);
protected:
	BITMAP GetImgSizes(HBITMAP bitmap);
};

