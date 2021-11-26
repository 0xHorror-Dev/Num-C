#ifndef _NUM_C_HEADER_H
#define _NUM_C_HEADER_H

#include <Windows.h>

#define _NUM_C_WND_CLASS_NAME "WND_NUM_C_CLASS"
#define _NUM_C_WND_TITLE "Num-C"

class App {

	// Window handle
	HWND m_Wnd;

	// Window class struct
	WNDCLASSEXA m_WC;

	const int m_Width{ 350 };
	const int m_Height{ 280 };

	//Register application window class
	bool RegisterWindowClass(const char* ClassName);

	// Initialize window
	bool InitWindow();

	// Informs about errors for user
	void ErrorCallback(const char* msg);

public:
	App();

	bool Init();

	int Start();

	~App();

};

#endif	