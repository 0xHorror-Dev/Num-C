#ifndef _NUM_C_GFX_H
#define _NUM_C_GFX_H

#include<string>
#include<dwrite.h>
#include<d2d1.h>

class App;

class Gfx {

	ID2D1Factory* m_pD2D1Factory;
	IDWriteFactory* m_pIDWriteFactory;

	// Title:
	IDWriteTextFormat* m_pIDWriteTitleTextFormat;
	ID2D1SolidColorBrush* m_pTitleSolidBrush;

	//Buttons:
	ID2D1SolidColorBrush* m_pButtonsBrush;
	IDWriteTextFormat* m_pIDWriteConvertTextFormat;
	D2D1_ELLIPSE m_Elipse;


	ID2D1DCRenderTarget* m_pID2D1DCRT;

	ID2D1SolidColorBrush* m_pSolidBrush;

	ID2D1GradientStopCollection* m_pGSC;
	ID2D1LinearGradientBrush* m_pLGB;


	App* m_pApp;

	HWND m_Wnd;

	void DrawTitle();
	void DrawBackGround();

	std::wstring Title;

	void DrawElipseButton(ID2D1SolidColorBrush* pBrush, PDRAWITEMSTRUCT pDis, D2D1::ColorF& NormalColor, D2D1::ColorF& SelectedColor);

public:

	Gfx();

	bool Init(App* p_App);

	void Draw(HDC hdc);

	void Free();

	void DrawButton(const int nId, PDRAWITEMSTRUCT pDis);

	~Gfx();

};

#endif