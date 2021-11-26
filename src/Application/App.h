#ifndef _NUM_C_HEADER_H
#define _NUM_C_HEADER_H

#include <Windows.h>

#define _NUM_C_WND_CLASS_NAME "WND_NUM_C_CLASS"

class App {

	// Window handle
	HWND m_Wnd;

	// Window class struct
	WNDCLASSEXA m_WC;


	//Register application window class
	bool RegisterWindowClass(const char* ClassName);

	//
	void ErrorCallback(const char* msg);

public:
	App();

	bool Init();

	~App();

};

#endif	