#include "App.h"

bool App::RegisterWindowClass(const char* ClassName){
	m_WC.cbSize = sizeof(WNDCLASSEXA);
	m_WC.lpszClassName = ClassName;
	m_WC.lpfnWndProc = DefWindowProc;
	m_WC.hCursor = LoadCursor(nullptr, IDC_ARROW);
	m_WC.hIcon = LoadCursor(nullptr, IDI_APPLICATION);
	m_WC.hIconSm = LoadCursor(nullptr, IDI_APPLICATION);
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

void App::ErrorCallback(const char* msg){
	MessageBoxA(m_Wnd, msg, "NUM_C", MB_ICONERROR);
}

App::App() : m_Wnd(NULL){

	memset(&m_WC, 0, sizeof(WNDCLASSEXA));
}

bool App::Init(){

	if (!RegisterWindowClass(_NUM_C_WND_CLASS_NAME))return false;

	return true;
}

App::~App(){
	
}