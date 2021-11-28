#include "GFX.h"
#include "..//Application/App.h"

Gfx::Gfx() : m_pD2D1Factory(NULL), m_pIDWriteFactory(NULL), m_pApp(NULL), m_Wnd(NULL), Title(_WCHAR_NUM_C_WND_TITLE){}

bool Gfx::Init(App* p_App){
	m_pApp = p_App;

	m_Wnd = p_App->GetWindowHandle();

	HRESULT hr{};
	hr = D2D1CreateFactory(D2D1_FACTORY_TYPE::D2D1_FACTORY_TYPE_SINGLE_THREADED, &m_pD2D1Factory);
	if (!SUCCEEDED(hr)) {
		p_App->ErrorCallback("Failed to initialize D2D1Factory!");
		return false;
	}

	hr = DWriteCreateFactory(
		DWRITE_FACTORY_TYPE::DWRITE_FACTORY_TYPE_ISOLATED,
		__uuidof(IDWriteFactory),
		reinterpret_cast<IUnknown**>(&m_pIDWriteFactory));
	if (!SUCCEEDED(hr)) {
		p_App->ErrorCallback("Failed to initialize IDWriteFactory!");
		return false;
	}


	D2D1_RENDER_TARGET_PROPERTIES props = D2D1::RenderTargetProperties(
		D2D1_RENDER_TARGET_TYPE_DEFAULT,
		D2D1::PixelFormat(
			DXGI_FORMAT_B8G8R8A8_UNORM,
			D2D1_ALPHA_MODE_PREMULTIPLIED),
		0,
		0,
		D2D1_RENDER_TARGET_USAGE_NONE,
		D2D1_FEATURE_LEVEL_DEFAULT
	);

	m_pD2D1Factory->CreateDCRenderTarget(&props, &m_pID2D1DCRT);


	hr = m_pID2D1DCRT->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::Black), &m_pSolidBrush);
	if (!SUCCEEDED(hr)) {
		p_App->ErrorCallback("Failed to create SolidColorBrush!");
		return false;
	}

	const D2D1_GRADIENT_STOP GradientStops[] =
	{
		{ 0.8f, D2D1::ColorF(0.137255f, 0.145098f, 0.149020f) },
		{ 0.2f, D2D1::ColorF(0.254902f, 0.262745f, 0.270588f) },
	};

	hr = m_pID2D1DCRT->
		CreateGradientStopCollection(GradientStops, _countof(GradientStops), &m_pGSC);
	if (!SUCCEEDED(hr)) {
		p_App->ErrorCallback("Failed to create GradientStopCollection!");
		return false;
	}

	hr = m_pIDWriteFactory->CreateTextFormat(L"Consolas", nullptr,
	DWRITE_FONT_WEIGHT::DWRITE_FONT_WEIGHT_REGULAR, DWRITE_FONT_STYLE::DWRITE_FONT_STYLE_NORMAL,
	DWRITE_FONT_STRETCH::DWRITE_FONT_STRETCH_NORMAL, 20.f, L"", &m_pIDWriteTitleTextFormat);
	if (!SUCCEEDED(hr)) {
		p_App->ErrorCallback("Failed to create IDWriteTitleTextFormat!");
		return false;
	}

	hr = m_pIDWriteFactory->CreateTextFormat(L"Consolas", nullptr,
		DWRITE_FONT_WEIGHT::DWRITE_FONT_WEIGHT_REGULAR, DWRITE_FONT_STYLE::DWRITE_FONT_STYLE_NORMAL,
		DWRITE_FONT_STRETCH::DWRITE_FONT_STRETCH_NORMAL, 20.f, L"", &m_pIDWriteConvertTextFormat);
	if (!SUCCEEDED(hr)) {
		p_App->ErrorCallback("Failed to create m_pIDWriteConvertTextFormat!");
		return false;
	}

	hr = m_pID2D1DCRT->CreateSolidColorBrush(D2D1::ColorF(1.000000f, 0.843137f, 0.000000f), &m_pTitleSolidBrush);
	if (!SUCCEEDED(hr)) {
		p_App->ErrorCallback("Failed to create TitleSolidColorBrush!");
		return false;
	}

	hr = m_pID2D1DCRT->CreateSolidColorBrush(D2D1::ColorF(1.000000f, 0.843137f, 0.000000f), &m_pButtonsBrush);
	if (!SUCCEEDED(hr)) {
		p_App->ErrorCallback("Failed to create m_pButtonsBrush!");
		return false;
	}

	return true;
}

void Gfx::Draw(HDC hdc){
	m_pID2D1DCRT->BindDC(hdc, m_pApp->GetClientRect());
	m_pID2D1DCRT->BeginDraw();
	DrawBackGround();
	DrawTitle();
	m_pID2D1DCRT->EndDraw();
}

void Gfx::DrawElipseButton(ID2D1SolidColorBrush* pBrus, PDRAWITEMSTRUCT pDis, D2D1::ColorF& NormalColor, D2D1::ColorF& SelectedColor){
	if (pDis->itemState & ODS_SELECTED) {
		pBrus->SetColor(SelectedColor);
	}
	else
		pBrus->SetColor(NormalColor);

	D2D1_SIZE_F size = m_pID2D1DCRT->GetSize();
	const float x = size.width / 2;
	const float y = size.height / 2;
	const float radius = min(x, y);
	m_Elipse = D2D1::Ellipse(D2D1::Point2F(x, y), radius, radius);

	m_pID2D1DCRT->Clear(D2D1::ColorF(0.203922f, 0.211765f, 0.219608f));

	m_pID2D1DCRT->FillEllipse(&m_Elipse, pBrus);
}

void Gfx::DrawTitle(){
	m_pID2D1DCRT->DrawTextA(Title.c_str(), Title.length(), m_pIDWriteTitleTextFormat, 
		D2D1::RectF(10.f, 10.f, 10.f + 120.f, 10.f + 100.f), m_pTitleSolidBrush);
}

void Gfx::DrawBackGround(){
	const D2D1_SIZE_F size = this->m_pID2D1DCRT->GetSize();
	const D2D1_POINT_2F start = D2D1::Point2F(0.0f, 0.0f);
	const D2D1_POINT_2F end = D2D1::Point2F(size.width, size.height);

	const D2D1_LINEAR_GRADIENT_BRUSH_PROPERTIES properties =
		D2D1::LinearGradientBrushProperties(start, end);

	m_pID2D1DCRT->CreateLinearGradientBrush(properties, m_pGSC, &m_pLGB);

	const D2D1_RECT_F Rect = D2D1::RectF(0, 0, size.width, size.height);

	m_pID2D1DCRT->FillRectangle(Rect, m_pLGB);
}

template<typename T>
void SafeRelease(T** obj) {
	if ((*obj) != nullptr) {
		(*obj)->Release();
		(*obj) = nullptr;
	}
}

void Gfx::Free(){
	SafeRelease(&m_pIDWriteConvertTextFormat);
	SafeRelease(&m_pButtonsBrush);
	SafeRelease(&m_pIDWriteTitleTextFormat);
	SafeRelease(&m_pTitleSolidBrush);
	SafeRelease(&m_pGSC);
	SafeRelease(&m_pLGB);
	SafeRelease(&m_pSolidBrush);
	SafeRelease(&m_pID2D1DCRT);
	SafeRelease(&m_pIDWriteFactory);
	SafeRelease(&m_pD2D1Factory);
}

Gfx::~Gfx(){

}

void Gfx::DrawButton(const int nId, PDRAWITEMSTRUCT pDis){

	HRESULT hr = m_pID2D1DCRT->BindDC(pDis->hDC, &pDis->rcItem);
	if (!SUCCEEDED(hr)) {
		exit(6);
	}

	m_pID2D1DCRT->BeginDraw();
	m_pID2D1DCRT->Clear(D2D1::ColorF(D2D1::ColorF::White, 0.42f));

	switch (nId){
	case static_cast<int>(App::CTRL_ID::CTRL_ID_CLOSE_BUTTON): 
		DrawElipseButton(m_pButtonsBrush, pDis,
			D2D1::ColorF(D2D1::ColorF::Red),
			D2D1::ColorF(0.741176f, 0.000000f, 0.000000f));
		
		break;
	case static_cast<int>(App::CTRL_ID::CTRL_ID_MINIMIZE_BUTTON):
		DrawElipseButton(m_pButtonsBrush, pDis,
			D2D1::ColorF(D2D1::ColorF::Lime),
			D2D1::ColorF(0.043137f, 0.400000f, 0.137255f));

		break;
	case static_cast<int>(App::CTRL_ID::CTRL_ID_CONVERT_BUTTON):
	{
		m_pID2D1DCRT->Clear(D2D1::ColorF(D2D1::ColorF::Lime));
		if (pDis->itemState & ODS_SELECTED) {
			this->m_pButtonsBrush->SetColor(D2D1::ColorF(0.043137f, 0.400000f, 0.137255f));
		}
		else {
			this->m_pButtonsBrush->SetColor(D2D1::ColorF(D2D1::ColorF::Lime));
		}

		this->m_pID2D1DCRT->FillRectangle(D2D1::RectF(0.f, 0.f, 1800.f, 110.f), this->m_pButtonsBrush);
		if (pDis->itemState & ODS_SELECTED) {
			m_pButtonsBrush->SetColor(D2D1::ColorF(D2D1::ColorF::DarkGray));
			m_pID2D1DCRT->DrawRectangle(D2D1::RectF(5.f, 5.f,195.f, 34.f), m_pButtonsBrush);
		}

		m_pIDWriteConvertTextFormat->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_CENTER);
		m_pIDWriteConvertTextFormat->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_CENTER);

		const std::wstring text{ L"Convert" };
		m_pButtonsBrush->SetColor(D2D1::ColorF(0.501961f, 0.501961f, 0.501961f));
		m_pID2D1DCRT->DrawText(text.c_str(), 9, m_pIDWriteConvertTextFormat, D2D1::RectF(0.0f, 0.0f, static_cast<FLOAT>(pDis->rcItem.right), static_cast<FLOAT>(pDis->rcItem.bottom)), m_pButtonsBrush);
		m_pID2D1DCRT->EndDraw();
	}
		break;
	}

	m_pID2D1DCRT->EndDraw();
}
