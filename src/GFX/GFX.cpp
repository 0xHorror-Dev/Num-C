#include "GFX.h"
#include "..//Application/App.h"

Gfx::Gfx() : m_pD2D1Factory(NULL), m_pIDWriteFactory(NULL), m_pApp(NULL), m_Wnd(NULL){}

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

	return true;
}

void Gfx::Draw(HDC hdc){
	m_pID2D1DCRT->BindDC(hdc, m_pApp->GetClientRect());
	m_pID2D1DCRT->BeginDraw();
	DrawBackGround();
	m_pID2D1DCRT->EndDraw();
}

void Gfx::DrawTitle(){

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
	SafeRelease(&m_pGSC);
	SafeRelease(&m_pSolidBrush);
	SafeRelease(&m_pID2D1DCRT);
	SafeRelease(&m_pIDWriteFactory);
	SafeRelease(&m_pD2D1Factory);
}

Gfx::~Gfx(){

}
