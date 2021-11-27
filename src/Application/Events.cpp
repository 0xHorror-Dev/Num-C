#include "App.h"

void App::Close() {
	GFX->Free();
}

void App::Create(HWND hwnd){
	::GetClientRect(hwnd, &ClientRect);
}

void App::Paint(HWND hwnd){

	PAINTSTRUCT PaintInfo;
	BeginPaint(hwnd, &PaintInfo);

	GFX->Draw(PaintInfo.hdc);

	EndPaint(hwnd, &PaintInfo);
}
