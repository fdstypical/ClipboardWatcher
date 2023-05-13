#include "Drawer.h"

Drawer::Drawer() {}

Drawer::~Drawer() {}

void Drawer::DrawImage(HDC hdc, HBITMAP bitmap) {
    PAINTSTRUCT ps;
    HDC mdc = CreateCompatibleDC(hdc);

    SelectObject(mdc, bitmap);

    BITMAP rect = GetImgSizes(bitmap);

    StretchBlt(
        hdc, 10, 480, 565, 350,
        mdc, 0, 0, rect.bmWidth, rect.bmHeight,
        SRCCOPY
    );

    DeleteDC(mdc);
}

BITMAP Drawer::GetImgSizes(HBITMAP bitmap) {
    BITMAP rect;
    GetObject(bitmap, sizeof(BITMAP), &rect);
    return rect;
}

HBITMAP Drawer::GetScreenImg(HWND hWnd) {
    RECT rc;
    GetClientRect(hWnd, &rc);

    HDC hdcScreen = GetDC(NULL);
    HDC hdc = CreateCompatibleDC(hdcScreen);

    HBITMAP hbmp = CreateCompatibleBitmap(
        hdcScreen,
        rc.right - rc.left,
        (rc.bottom - rc.top) / 2
    );

    SelectObject(hdc, hbmp);
    PrintWindow(hWnd, hdc, PW_CLIENTONLY);

    DeleteDC(hdc);
    ReleaseDC(NULL, hdcScreen);

    return hbmp;
}