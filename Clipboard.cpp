#include "Clipboard.h"

UINT Clipboard::AutoPriorityList[2] = { CF_UNICODETEXT, CF_BITMAP };

Clipboard::Clipboard() {
	format = NULL;
	isListened = false;
}

Clipboard::~Clipboard() {}

bool Clipboard::ClearClipboard() {
	if (!OpenClipboard(NULL))
		throw std::exception("Clipboard is not opening");

	bool isCleared = EmptyClipboard();
	CloseClipboard();

	return isCleared;
}

HBITMAP Clipboard::ReadBitmap() {
	if (!OpenClipboard(NULL))
		throw std::exception("Clipboard is not opening");

	HBITMAP bitmap = (HBITMAP)GetClipboardData(CF_BITMAP);
	CloseClipboard();

	if (bitmap == NULL)
		throw std::exception("Imgae does not readed from clipboard");

	return bitmap;
}

void Clipboard::WriteBitmap(HBITMAP hbmp) {
	if (!OpenClipboard(NULL))
		throw std::exception("Clipboard is not opening");

	EmptyClipboard();
	SetClipboardData(CF_BITMAP, hbmp);

	CloseClipboard();
}

void Clipboard::AutoSetFormat(HWND hWnd) {
	format = GetPriorityClipboardFormat(Clipboard::AutoPriorityList, 2);
}

const wchar_t* Clipboard::GetFormatLabel() {
	switch (format)
	{
		case CF_UNICODETEXT:
			return L"CF_UNICODETEXT";
		case CF_BITMAP:
			return L"CF_BITMAP";
		case 0:
			return L"CLIPBOARD IS EMPTY";
		default:
			return L"UNKNOWN FORMAT";
	}
}

void Clipboard::WriteText(const wchar_t* text, int length) {
	size_t memsize = sizeof(wchar_t) * (length + 1);
	HGLOBAL hMem = GlobalAlloc(GMEM_MOVEABLE, memsize);

	if (hMem == NULL)
		throw std::exception("Error occured GlobalAlloc function");
		
	void* mem = GlobalLock(hMem);

	if (mem == NULL) 
		throw std::exception("Error occured GlobalLock function");

	memcpy(mem, text, memsize);
	GlobalUnlock(hMem);

	if (!OpenClipboard(NULL))
		throw std::exception("Clipboard is not opening");

	EmptyClipboard();
	
	if (!SetClipboardData(CF_UNICODETEXT, hMem))
		GlobalFree(hMem);

	CloseClipboard();
}

wchar_t* Clipboard::ReadText() {
	if (!OpenClipboard(NULL))
		throw std::exception("Clipboard is not opening");

	HANDLE hData = GetClipboardData(CF_UNICODETEXT);
	wchar_t* text = static_cast<wchar_t*>(GlobalLock(hData));
	CloseClipboard();

	return text;
}

bool Clipboard::AddListener(HWND hWnd)
{
	isListened = AddClipboardFormatListener(hWnd);
	return isListened;
}

bool Clipboard::RemoveListener(HWND hWnd)
{
	isListened = !RemoveClipboardFormatListener(hWnd);
	return isListened;
}

