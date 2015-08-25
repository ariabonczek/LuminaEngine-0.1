#include "GraphicsDevice.hpp"

#include "Window.hpp"
#include "Texture2D.hpp"

NS_BEGIN

ID3D11Device* GraphicsDevice::dev;
ID3D11DeviceContext* GraphicsDevice::devCon;
IDXGISwapChain*  GraphicsDevice::swapChain;
ID3D11Texture2D*  GraphicsDevice::depthBuffer;
ID3D11RenderTargetView*  GraphicsDevice::renderTargetView;
ID3D11DepthStencilView*  GraphicsDevice::depthStencilView;
D3D11_VIEWPORT  GraphicsDevice::viewport;
D3D_FEATURE_LEVEL  GraphicsDevice::featureLevel;

Color  GraphicsDevice::_clearColor;
UINT  GraphicsDevice::windowWidth;
UINT GraphicsDevice::windowHeight;
bool GraphicsDevice::isInitialized;

GraphicsDevice::GraphicsDevice()
{
	ZeroMemory(&viewport, sizeof(D3D11_VIEWPORT));
}

GraphicsDevice::~GraphicsDevice()
{
	DELETECOM(depthStencilView);
	DELETECOM(depthBuffer);
	DELETECOM(renderTargetView);
	DELETECOM(swapChain);

	if (devCon)
		devCon->ClearState();
	DELETECOM(devCon);
	DELETECOM(dev);
}

bool GraphicsDevice::Initialize(Window window)
{
	DXGI_SWAP_CHAIN_DESC scd;
	ZeroMemory(&scd, sizeof(DXGI_SWAP_CHAIN_DESC));
	scd.BufferCount = 1;
	scd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	scd.BufferDesc.Width = window.GetWindowWidth();
	scd.BufferDesc.Height = window.GetWindowHeight();
	scd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	scd.OutputWindow = window.GetWindowHandle();
	scd.Windowed = TRUE;
	scd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
	scd.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;
	scd.SampleDesc.Count = 4;
	scd.BufferDesc.RefreshRate.Numerator = 60;
	scd.BufferDesc.RefreshRate.Denominator = 1;
	scd.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	scd.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;

	featureLevel = D3D_FEATURE_LEVEL_11_0;
	HRESULT hr = D3D11CreateDeviceAndSwapChain(
		NULL,
		D3D_DRIVER_TYPE_HARDWARE,
		NULL,
#ifdef DEBUG
		D3D11_CREATE_DEVICE_DEBUG,
#else
		NULL,
#endif
		NULL,
		NULL,
		D3D11_SDK_VERSION,
		&scd,
		&swapChain,
		&dev,
		&featureLevel,
		&devCon);

	if (FAILED(hr))
	{
		MessageBox(NULL, "D3D11CreateDeviceAndSwapChain failed.", NULL, NULL);
		return false;
	}

	OnResize(window.GetWindowWidth(), window.GetWindowHeight());

	_clearColor = Color(0.0f, 0.0f, 0.0f, 1.0f);
	isInitialized = true;

	return true;
}

void GraphicsDevice::OnResize(UINT newWidth, UINT newHeight)
{
	DELETECOM(renderTargetView);
	DELETECOM(depthStencilView);
	DELETECOM(depthBuffer);

	windowWidth = newWidth;
	windowHeight = newHeight;

	swapChain->ResizeBuffers(
		1,
		windowWidth,
		windowHeight,
		DXGI_FORMAT_R8G8B8A8_UNORM,
		NULL);
	ID3D11Texture2D* backBuffer;
	swapChain->GetBuffer(NULL, __uuidof(ID3D11Texture2D), reinterpret_cast<void**>(&backBuffer));
	dev->CreateRenderTargetView(backBuffer, 0, &renderTargetView);
	DELETECOM(backBuffer);

	D3D11_TEXTURE2D_DESC dsd;
	ZeroMemory(&dsd, sizeof(D3D11_TEXTURE2D_DESC));
	dsd.Width = windowWidth;
	dsd.Height = windowHeight;
	dsd.MipLevels = 1;
	dsd.ArraySize = 1;
	dsd.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	dsd.Usage = D3D11_USAGE_DEFAULT;
	dsd.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	dsd.CPUAccessFlags = NULL;
	dsd.MiscFlags = NULL;
	dsd.SampleDesc.Count = 4;

	dev->CreateTexture2D(&dsd, NULL, &depthBuffer);
	dev->CreateDepthStencilView(depthBuffer, NULL, &depthStencilView);
	devCon->OMSetRenderTargets(1, &renderTargetView, depthStencilView);

	viewport.TopLeftX = 0;
	viewport.TopLeftY = 0;
	viewport.Width = (float)windowWidth;
	viewport.Height = (float)windowHeight;
	viewport.MinDepth = 0.0f;
	viewport.MaxDepth = 1.0f;
	devCon->RSSetViewports(1, &viewport);
}

void GraphicsDevice::OnResizeExit()
{
	DELETECOM(renderTargetView);
	DELETECOM(depthStencilView);
	DELETECOM(depthBuffer);

	swapChain->ResizeBuffers(
		1,
		windowWidth,
		windowHeight,
		DXGI_FORMAT_R8G8B8A8_UNORM,
		NULL);
	ID3D11Texture2D* backBuffer;
	swapChain->GetBuffer(NULL, __uuidof(ID3D11Texture2D), reinterpret_cast<void**>(&backBuffer));
	dev->CreateRenderTargetView(backBuffer, 0, &renderTargetView);
	DELETECOM(backBuffer);

	D3D11_TEXTURE2D_DESC dsd;
	ZeroMemory(&dsd, sizeof(D3D11_TEXTURE2D_DESC));
	dsd.Width = windowWidth;
	dsd.Height = windowHeight;
	dsd.MipLevels = 1;
	dsd.ArraySize = 1;
	dsd.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	dsd.Usage = D3D11_USAGE_DEFAULT;
	dsd.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	dsd.CPUAccessFlags = NULL;
	dsd.MiscFlags = NULL;
	dsd.SampleDesc.Count = 4;

	dev->CreateTexture2D(&dsd, NULL, &depthBuffer);
	dev->CreateDepthStencilView(depthBuffer, NULL, &depthStencilView);
	devCon->OMSetRenderTargets(1, &renderTargetView, depthStencilView);

	viewport.TopLeftX = 0;
	viewport.TopLeftY = 0;
	viewport.Width = (float)windowWidth;
	viewport.Height = (float)windowHeight;
	viewport.MinDepth = 0.0f;
	viewport.MaxDepth = 1.0f;
	devCon->RSSetViewports(1, &viewport);
}

void GraphicsDevice::Clear()
{
	const float clearColor[4] = { _clearColor.r, _clearColor.g, _clearColor.b, _clearColor.a };
	devCon->ClearRenderTargetView(renderTargetView, clearColor);
	devCon->ClearDepthStencilView(depthStencilView, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
}

void GraphicsDevice::Clear(Color color)
{
	const float clearColor[4] = { color.r, color.g, color.b, color.a };
	devCon->ClearRenderTargetView(renderTargetView, clearColor);
	devCon->ClearDepthStencilView(depthStencilView, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
}

void GraphicsDevice::Clear(float r, float g, float b, float a)
{
	const float clearColor[4] = { r, g, b, a };
	devCon->ClearRenderTargetView(renderTargetView, clearColor);
	devCon->ClearDepthStencilView(depthStencilView, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
}

void GraphicsDevice::Clear(const float color[4])
{
	devCon->ClearRenderTargetView(renderTargetView, color);
	devCon->ClearDepthStencilView(depthStencilView, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
}

void GraphicsDevice::Display()
{
	swapChain->Present(ENABLE_VSYNC, 0);
}

void GraphicsDevice::SetRenderTarget()
{
	devCon->OMSetRenderTargets(1, &renderTargetView, depthStencilView);
}

void GraphicsDevice::ResetViewport()
{
	// Recreate the viewport and bind it
	viewport.TopLeftX = 0;
	viewport.TopLeftY = 0;
	viewport.Width = (float)windowWidth;
	viewport.Height = (float)windowHeight;
	viewport.MinDepth = 0.0f;
	viewport.MaxDepth = 1.0f;
	devCon->RSSetViewports(1, &viewport);
}


void GraphicsDevice::SetRasterizerState()
{

}

void GraphicsDevice::SetBlendState()
{ 

}

ID3D11Device* GraphicsDevice::GetDevice()
{
	return dev;
}

ID3D11DeviceContext* GraphicsDevice::GetDeviceContext()
{
	return devCon;
}

float GraphicsDevice::GetAspectRatio()
{
	return (float)WINDOW_WIDTH / WINDOW_HEIGHT;
}

bool GraphicsDevice::IsInitialized()const
{
	return isInitialized;
}
NS_END