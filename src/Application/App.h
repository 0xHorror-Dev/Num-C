#ifndef _NUM_C_HEADER_H
#define _NUM_C_HEADER_H

#include <Windows.h>

#include "..//GFX/GFX.h"

#include "..//Converter/Converter.h"

#define _NUM_C_WND_CLASS_NAME "WND_NUM_C_CLASS"
#define _NUM_C_WND_TITLE "Num-C"
#define _WCHAR_NUM_C_WND_TITLE L"Num-C"

class App {

	HWND m_CloseButton;
	HWND m_MinimizeButton;
	HWND m_ConvertButton;
	HWND m_Edit;
	HWND m_EditFromNumSys;
	HWND m_EditInNumSys;


	Gfx* GFX;
	Converter* m_pConverter;

	// Window handle
	HWND m_Wnd;

	// Window class struct
	WNDCLASSEXA m_WC;

	HINSTANCE hInstance;

	const int m_Width{ 350 };
	const int m_Height{ 280 };

	RECT ClientRect;

	//Register application window class
	bool RegisterWindowClass(const char* ClassName);

	// Initialize window
	bool InitWindow();
	bool CreateNativeControls(HWND hwnd);

	//WndProc redirect to InternalWndProc
	static LRESULT CALLBACK WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

	LRESULT InternalWndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

	void Convert();

	void GetTextFromTextBox(HWND hwnd, std::string& str);

	// Events:
	void Close();

	void Create(HWND hwnd);

	void Paint(HWND hwnd);

	void Command(WPARAM wParam, LPARAM lParam);

public:
	enum CTRL_ID {
		CTRL_ID_CLOSE_BUTTON,
		CTRL_ID_MINIMIZE_BUTTON,
		CTRL_ID_CONVERT_BUTTON,
		CTRL_ID_EDIT,
		CTRL_ID_EDIT_FROM_NUM_SYS,
		CTRL_ID_EDIT_IN_NUM_SYS
	};

	App();

	void UpdateHandle(HWND hwnd);

	// Informs about errors for user
	void ErrorCallback(const char* msg);
	HWND GetWindowHandle();

	bool Init(HINSTANCE hInstance);

	RECT* GetClientRect();

	int Start();

	~App();

};

#endif	