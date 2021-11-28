#include "App.h"

bool App::CreateNativeControls(HWND hwnd){

	DWORD ButtonsStyle = BS_PUSHBUTTON | BS_OWNERDRAW | WS_VISIBLE | WS_CHILD;

	m_CloseButton = CreateWindowEx(0,
		"BUTTON", "Close",
		ButtonsStyle,
		340, 10, 10, 10, hwnd, reinterpret_cast<HMENU>(App::CTRL_ID::CTRL_ID_CLOSE_BUTTON),
		nullptr, nullptr);

	if (m_CloseButton == NULL) {
		ErrorCallback("Failed to create close button");
		return false;
	}

	m_MinimizeButton = CreateWindowEx(0,
		"BUTTON", "Minimize",
		ButtonsStyle,
		320, 10, 10, 10, hwnd, reinterpret_cast<HMENU>(App::CTRL_ID::CTRL_ID_MINIMIZE_BUTTON),
		nullptr, nullptr);
	if (m_MinimizeButton == NULL) {
		ErrorCallback("Failed to create minimize button");
		return false;
	}

	m_ConvertButton = CreateWindowEx(0,
		"BUTTON", "Convert",
		ButtonsStyle,
		80, 140, 200, 40,
		hwnd, reinterpret_cast<HMENU>(App::CTRL_ID::CTRL_ID_CONVERT_BUTTON),
		nullptr, nullptr);
	if (m_ConvertButton == NULL) {
		ErrorCallback("Failed to create convert button");
		return false;
	}

	m_Edit = CreateWindowEx(0,
		"EDIT", NULL,
		WS_VISIBLE | WS_CHILD,
		50, 100, 250, 20,
		hwnd, reinterpret_cast<HMENU>(App::CTRL_ID::CTRL_ID_EDIT),
		nullptr, nullptr);
	if (m_Edit == NULL) {
		ErrorCallback("Failed to create edit");
		return false;
	}

	HFONT FontConsolas = CreateFont(
		18, 0, 0, 0, FW_REGULAR,
		0, 0, 0,
		DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, 
		CLIP_DEFAULT_PRECIS, CLEARTYPE_QUALITY,
		DEFAULT_PITCH,
		"Consolas");

	SendMessage(m_Edit, WM_SETFONT, reinterpret_cast<WPARAM>(FontConsolas), TRUE);

	return true;
}

bool App::RegisterWindowClass(const char* ClassName){
	m_WC.cbSize = sizeof(WNDCLASSEXA);
	m_WC.lpszClassName = ClassName;
	m_WC.lpfnWndProc = &App::WndProc;
	m_WC.hCursor = LoadCursor(nullptr, IDC_ARROW);
	m_WC.hIcon = LoadIcon(nullptr, IDI_APPLICATION);
	m_WC.hIconSm = LoadIcon(nullptr, IDI_APPLICATION);
	m_WC.hbrBackground = nullptr;
	//m_WC.hbrBackground = CreateSolidBrush(RGB(0, 0, 0));
	m_WC.cbClsExtra = 0;
	m_WC.cbWndExtra = 0;
	m_WC.hInstance = hInstance;
	m_WC.style = CS_VREDRAW | CS_HREDRAW;

	if (!RegisterClassExA(&m_WC)) {
		ErrorCallback("Error:Failed to register class name");
		return false;
	}

	return true;
}

bool App::InitWindow(){
	
	RECT _WndUserArea{ 0, 0, m_Width, m_Height};
	AdjustWindowRect(&_WndUserArea, WS_POPUP | WS_CAPTION, false);

	int ScreenCenterX = (GetSystemMetrics(SM_CXSCREEN) - _WndUserArea.right) / 2;
	int ScreenCenterY = (GetSystemMetrics(SM_CYSCREEN) - _WndUserArea.bottom) / 2;

	//WS_CAPTION | WS_POPUP

	m_Wnd = CreateWindowExA(0,
		_NUM_C_WND_CLASS_NAME, 
		_NUM_C_WND_TITLE,
		WS_POPUP | WS_CAPTION,
		ScreenCenterX, 
		ScreenCenterY,
		_WndUserArea.right,
		_WndUserArea.bottom,
		NULL, NULL, hInstance, this
	);

	if (!m_Wnd) {
		this->ErrorCallback("Error: Failed to create window!");

		return false;
	}

	return true;
}

void App::UpdateHandle(HWND hwnd){
	this->m_Wnd = hwnd;
}

void App::ErrorCallback(const char* msg){
	MessageBoxA(m_Wnd, msg, _NUM_C_WND_TITLE, MB_ICONERROR);
}

HWND App::GetWindowHandle(){
	return m_Wnd;
}

App::App() : m_Wnd(NULL){
	memset(&m_WC, 0, sizeof(WNDCLASSEXA));
}

bool App::Init(HINSTANCE hInstance){

	this->hInstance = hInstance;

	if (!RegisterWindowClass(_NUM_C_WND_CLASS_NAME))return false;
	if (!InitWindow()) return false;
	if (!CreateNativeControls(m_Wnd)) return false;

	GFX = new Gfx;

	if (!GFX->Init(this)) return false;

	return true;
}

void App::Convert(LPARAM lParam){

}

RECT* App::GetClientRect(){
	return &ClientRect;
}

int App::Start(){

	ShowWindow(m_Wnd, true);
	UpdateWindow(m_Wnd);

	MSG _msg{};
	while (GetMessageA(&_msg, nullptr, 0, 0)) {
		TranslateMessage(&_msg);
		DispatchMessageA(&_msg);
	}

	return _msg.wParam;
}

App::~App(){
	if (m_Wnd != NULL)
		DestroyWindow(m_Wnd);

	if (GFX != NULL) {
		
		delete GFX;
	}
}

