#include "WindowProcedure.h"

void SetControlOffsets(HWND control, RECT &offsets) {
    RECT currentOffsets;
    SendMessage(control, EM_GETRECT, 0, (LPARAM)&currentOffsets);

    currentOffsets.left += offsets.left;
    currentOffsets.top += offsets.top;
    currentOffsets.right -= offsets.right;
    currentOffsets.bottom -= offsets.bottom;

    SendMessage(control, EM_SETRECT, 0, (LPARAM)&currentOffsets);
}

void UpdateWindowM(HWND hWnd) {
    InvalidateRect(hWnd, NULL, TRUE);
    UpdateWindow(hWnd);
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_CREATE:
    {
        clipboard.AddListener(hWnd);

        fLabel = CreateWindowW(
            L"static", NULL,
            WS_VISIBLE | WS_CHILD | SS_CENTER | SS_CENTERIMAGE,
            10, 10, 565, 40, hWnd, NULL, NULL, NULL
        );

        viewEdit = CreateWindowW(
            L"edit", NULL,
            WS_CHILD | WS_VISIBLE | WS_VSCROLL |
            ES_MULTILINE | ES_WANTRETURN | ES_OEMCONVERT | ES_READONLY,
            10, 60, 565, 200, hWnd, (HMENU)ID_VIEW_EDIT, NULL, NULL
        );

        copyTextBtn = CreateWindowW(
            L"button", L"Copy Text",
            WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON,
            10, 270, 185, 40, hWnd, (HMENU)ID_BUTTON_COPY_TEXT, NULL, NULL
        );

        copyImgBtn = CreateWindowW(
            L"button", L"Copy Image",
            WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON,
            200, 270, 185, 40, hWnd, (HMENU)ID_BUTTON_COPY_IMG, NULL, NULL
        );

        clearBtn = CreateWindowW(
            L"button", L"Clear Clipboard",
            WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON,
            390, 270, 185, 40, hWnd, (HMENU)ID_BUTTON_CLEAR, NULL, NULL
        );

        typeEdit = CreateWindowW(
            L"edit", NULL,
            WS_CHILD | WS_VISIBLE | WS_BORDER |
            ES_MULTILINE | ES_WANTRETURN | ES_OEMCONVERT,
            10, 320, 565, 150, hWnd, (HMENU)ID_TYPE_EDIT, NULL, NULL
        );

        RECT offsets = { 10, 5, 10, 5 };
        SetControlOffsets(viewEdit, offsets);
        SetControlOffsets(typeEdit, offsets);
    }   
    break;
    case WM_COMMAND:
    {
        int wmId = LOWORD(wParam);

        switch (wmId)
        {
        case ID_BUTTON_COPY_TEXT:
        {
            wchar_t buf[1024];
            int len = GetWindowTextLengthW(typeEdit);
            size_t memsize = sizeof(wchar_t) * (len + 1);
            GetWindowTextW(typeEdit, (LPWSTR)buf, len + 1);

            clipboard.WriteText(buf, memsize);
            SendMessage(typeEdit, WM_SETTEXT, WPARAM(0), LPARAM(L""));
        }
        break;
        case ID_BUTTON_COPY_IMG:
        {
            HBITMAP hbmp = drawer.GetScreenImg(hWnd);
            clipboard.WriteBitmap(hbmp);
        }
        break;
        case ID_BUTTON_CLEAR:
        {
            clipboard.ClearClipboard();
            SendMessage(viewEdit, WM_SETTEXT, WPARAM(0), LPARAM(L""));
            SendMessage(typeEdit, WM_SETTEXT, WPARAM(0), LPARAM(L""));
        }
        break; 
        case IDM_EXIT:
            DestroyWindow(hWnd);
            break;
        default:
            return DefWindowProc(hWnd, message, wParam, lParam);
        }
    }
    break;
    case WM_CLIPBOARDUPDATE:
    {
        clipboard.AutoSetFormat(hWnd);
        const wchar_t* label = clipboard.GetFormatLabel();
        SetWindowText(fLabel, label);

        if (clipboard.GetFomat() == CF_UNICODETEXT) {
            wchar_t* text = clipboard.ReadText();
            SetDlgItemText(hWnd, ID_VIEW_EDIT, text);
        }

        UpdateWindowM(hWnd);
    }
    break;
    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hWnd, &ps);

        if (clipboard.GetFomat() == CF_BITMAP) {
            HBITMAP bitmap = clipboard.ReadBitmap();
            drawer.DrawImage(hdc, bitmap);
        }

        EndPaint(hWnd, &ps);
    }
    break;
    case WM_DESTROY:
    {
        clipboard.RemoveListener(hWnd);
        PostQuitMessage(0);
    }
    break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}