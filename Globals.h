#pragma once
#pragma comment(linker,"\"/manifestdependency:type='win32' \
name='Microsoft.Windows.Common-Controls' version='6.0.0.0' \
processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")

#include "framework.h"
#include "ClipboardWatcher.h"
#include "Clipboard.h"
#include "Drawer.h"

#define MAX_LOADSTRING 100

#define ID_VIEW_EDIT 3002
#define ID_TYPE_EDIT 3003
#define ID_BUTTON_COPY_TEXT 3004
#define ID_BUTTON_COPY_IMG 3005
#define ID_BUTTON_CLEAR 3006

extern HINSTANCE hInst;
extern WCHAR szTitle[MAX_LOADSTRING];
extern WCHAR szWindowClass[MAX_LOADSTRING];

extern HWND viewEdit;
extern HWND typeEdit;
extern HWND copyTextBtn;
extern HWND	copyImgBtn;
extern HWND clearBtn;
extern HWND fLabel;

extern Clipboard clipboard;
extern Drawer drawer;

extern ATOM                MyRegisterClass(HINSTANCE hInstance);
extern BOOL                InitInstance(HINSTANCE, int);
extern LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
extern INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);