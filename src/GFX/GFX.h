#ifndef _NUM_C_GFX_H
#define _NUM_C_GFX_H

#include<dwrite.h>
#include<d2d1.h>

class App;

class Gfx {

	ID2D1Factory* m_pD2D1Factory;
	IDWriteFactory* m_pIDWriteFactory;

	ID2D1DCRenderTarget* m_pID2D1DCRT;

	ID2D1SolidColorBrush* m_pSolidBrush;

	ID2D1GradientStopCollection* m_pGSC;
	ID2D1LinearGradientBrush* m_pLGB;

	App* m_pApp;

	HWND m_Wnd;

public:

	Gfx();

	bool Init(App* p_App);

	void Draw(HDC hdc);

	void DrawTitle();
	void DrawBackGround();

	void Free();

	~Gfx();

};

#endif