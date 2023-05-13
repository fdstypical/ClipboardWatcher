#include "framework.h"
#include "ClipboardWatcher.h"
#include "InitWinMain.h"
#include "RegisterClass.h"
#include "InitInstance.h"
#include "WindowProcedure.h"
#include "Clipboard.h"
#include "Drawer.h"

HINSTANCE hInst;
WCHAR szTitle[MAX_LOADSTRING];
WCHAR szWindowClass[MAX_LOADSTRING];

HWND viewEdit;
HWND typeEdit;
HWND copyTextBtn;
HWND copyImgBtn;
HWND clearBtn;
HWND fLabel;

Clipboard clipboard;
Drawer drawer;

int APIENTRY wWinMain(
    _In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPWSTR    lpCmdLine,
    _In_ int       nCmdShow
) {
    return InitWinMain(hInstance, hPrevInstance, lpCmdLine, nCmdShow);
}
