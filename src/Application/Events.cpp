#include "App.h"

void App::Close() {
	GFX->Free();
}

void App::Create(HWND hwnd){
	::GetClientRect(hwnd, &ClientRect);

}

void App::Command(WPARAM wParam, LPARAM lParam) {
	const App::CTRL_ID nId = static_cast<const App::CTRL_ID>(LOWORD(wParam));

	switch (nId){
	case App::CTRL_ID::CTRL_ID_CLOSE_BUTTON:
		SendMessage(m_Wnd, WM_DESTROY, 0, 0);
		break;
	case App::CTRL_ID::CTRL_ID_MINIMIZE_BUTTON:
		SendMessage(m_Wnd, WM_SYSCOMMAND, SC_MINIMIZE, 0);
		break;
	case App::CTRL_ID::CTRL_ID_CONVERT_BUTTON:
		Convert();
		break;
	}
}

void App::Paint(HWND hwnd){

	PAINTSTRUCT PaintInfo;
	BeginPaint(hwnd, &PaintInfo);

	GFX->Draw(PaintInfo.hdc);

	EndPaint(hwnd, &PaintInfo);
}
