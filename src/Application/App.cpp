#include "App.h"

bool App::RegisterWindowClass(const char* ClassName){
	m_WC.cbSize = sizeof(WNDCLASSEXA);
	m_WC.lpszClassName = ClassName;
	m_WC.lpfnWndProc = DefWindowProc;
	m_WC.hCursor = LoadCursor(nullptr, IDC_ARROW);
	m_WC.hIcon = LoadIcon(nullptr, IDI_APPLICATION);
	m_WC.hIconSm = LoadIcon(nullptr, IDI_APPLICATION);
	m_WC.hbrBackground = nullptr;
	m_WC.cbClsExtra = 0;
	m_WC.cbWndExtra = 0;
	m_WC.style = CS_VREDRAW | CS_HREDRAW;

	if (!RegisterClassExA(&m_WC)) {
		ErrorCallback("Error:Failed to register class name");
		return false;
	}

	return true;
}

bool App::InitWindow(){
	
	RECT _WndUserArea;
	AdjustWindowRect(&_WndUserArea, WS_CAPTION | WS_POPUP, false);

	int ScreenCenterX = (GetSystemMetrics(SM_CXSCREEN) - _WndUserArea.right) / 2;
	int ScreenCenterY = (GetSystemMetrics(SM_CYSCREEN) - _WndUserArea.bottom) / 2;

	m_Wnd = CreateWindowExA(
		0, _NUM_C_WND_CLASS_NAME,_NUM_C_WND_TITLE,
		WS_CAPTION | WS_POPUP,
		ScreenCenterX, ScreenCenterY,
		_WndUserArea.right, _WndUserArea.bottom, NULL, NULL, NULL, this);

	if (!m_Wnd) {
		this->ErrorCallback("Error: Failed to create window!");

		return false;
	}

	return true;
}

void App::ErrorCallback(const char* msg){
	MessageBoxA(m_Wnd, msg, "NUM_C", MB_ICONERROR);
}

App::App() : m_Wnd(NULL){

	memset(&m_WC, 0, sizeof(WNDCLASSEXA));
}

bool App::Init(){

	if (!RegisterWindowClass(_NUM_C_WND_CLASS_NAME))return false;
	if (!InitWindow()) return false;

	return true;
}

int App::Start(){

	return 0;
}

App::~App(){
	if (m_Wnd != NULL)
		DestroyWindow(m_Wnd);
}