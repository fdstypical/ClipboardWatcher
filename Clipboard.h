#pragma once
#include "string"
#include "exception"
#include "framework.h"

class Clipboard
{
public:
	Clipboard();
	~Clipboard();

	bool AddListener(HWND hWnd);
	bool RemoveListener(HWND hWnd);
	
	bool ClearClipboard();

	wchar_t* ReadText();
	void WriteText(const wchar_t* text, int length);

	void AutoSetFormat(HWND hWnd);
	const wchar_t* GetFormatLabel();

	HBITMAP ReadBitmap();
	void WriteBitmap(HBITMAP hbmp);
	
	UINT GetFomat() { return format; }
protected:
	static UINT AutoPriorityList[2];
	bool isListened = false;
	UINT format;
};
