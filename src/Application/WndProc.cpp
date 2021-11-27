#include "App.h"

LRESULT App::WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam){

	App* p_App = nullptr;
	if (uMsg == WM_NCCREATE) {
		p_App = static_cast<App*>(reinterpret_cast<CREATESTRUCT*>(lParam)->lpCreateParams);

		SetLastError(0);

		if (!SetWindowLongPtr(hwnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(p_App))) {
			if (GetLastError() != 0) {
				return false;
			}
		}
	}
	else {
		p_App = reinterpret_cast<App*>(GetWindowLongPtr(hwnd, GWLP_USERDATA));
	}

	if (p_App) {
		p_App->UpdateHandle(hwnd);
		return p_App->InternalWndProc(hwnd, uMsg, wParam, lParam);
	}
	
	return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

LRESULT App::InternalWndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam){

	switch (uMsg){
	case WM_CREATE:
		this->Create(hwnd);
		break;
	case WM_DESTROY:
		this->Close();
		PostQuitMessage(0);
		break;
	case WM_PAINT:
		
		this->Paint(hwnd);

		break;
	case WM_NCHITTEST: 
		/* 
		* This can happen, for example, when the cursor moves, when a mouse button is pressed or released!
		msdn: https://docs.microsoft.com/en-us/windows/win32/inputdev/wm-nchittest
		*/
		SetWindowLong(hwnd, 0, HTCAPTION); // allows to move window
		return HTCAPTION;
	case WM_NCCALCSIZE:
		if (wParam == TRUE)
			SetWindowLong(hwnd, 0, 0);
		return TRUE;
		return FALSE;
		break;
	}

	return DefWindowProc(hwnd, uMsg, wParam, lParam);
}
