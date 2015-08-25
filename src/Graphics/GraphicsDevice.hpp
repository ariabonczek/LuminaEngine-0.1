#ifndef GRAPHICS_DEVICE_HPP
#define GRAPHICS_DEVICE_HPP

#include "../Config.hpp"

#include "Color.hpp"

#include "States\BlendState.hpp"
#include "States\DepthStencilState.hpp"
#include "States\RasterizerState.hpp"

NS_BEGIN

class Window;
class Texture2D;

/// <summary>
/// Interfaces with graphics hardware to facilitate rendering
/// </summary>
class GraphicsDevice
{
public:
	GraphicsDevice();
	~GraphicsDevice();

	/// <summary>
	/// Initializes Direct3D and sets up the graphics device
	/// </summary>
	bool Initialize(Window window);

	/// <summary>
	/// Handles resizing of the graphics environment
	/// </summary>
	void OnResize(UINT newWidth, UINT newHeight);

	/// <summary>
	/// Handles finishing resizing of the graphics environment
	/// </summary>
	void OnResizeExit();

	/// <summary>
	/// Clears the back buffer to clearColor member
	/// </summary>
	void Clear();

	/// <summary>
	/// Clears the back buffer to given color
	/// </summary>
	void Clear(Color color);

	/// <summary>
	/// Clears the back buffer to given color
	/// </summary>
	void Clear(float r, float g, float b, float a);

	/// <summary>
	/// Clears the back buffer to given color
	/// </summary>
	void Clear(const float color[4]);

	/// <summary>
	/// Present the buffer to the screen
	/// </summary>
	void Display();

	/// <summary>
	/// Bind the back buffer as the render target
	/// </summary>
	static void SetRenderTarget();

	/// <summary>
	/// Reset the viewport
	/// </summary>
	static void ResetViewport();

	static void SetRasterizerState();
	static void SetBlendState();

	// TODO: Need to find a better way to encapsulate this

	/// <summary>
	/// Returns a pointer to the graphics device
	/// </summary>
	static ID3D11Device* GetDevice();

	/// <summary>
	/// Returns a pointer to the graphics device context
	/// </summary>
	static ID3D11DeviceContext* GetDeviceContext();

	/// <summary>
	/// Returns width / height
	/// </summary>
	static float GetAspectRatio();
	
	/// <summary>
	/// Returns whether or not the GraphicsDevice has been initialized
	/// </summary>
	bool IsInitialized()const;
private:
	static ID3D11Device* dev;
	static ID3D11DeviceContext* devCon;
	static IDXGISwapChain* swapChain;
	static ID3D11Texture2D* depthBuffer;
	static ID3D11RenderTargetView* renderTargetView;
	static ID3D11DepthStencilView* depthStencilView;
	static D3D11_VIEWPORT viewport;
	static D3D_FEATURE_LEVEL featureLevel;

	static Color _clearColor;
	static UINT windowWidth;
	static UINT windowHeight;
	static bool isInitialized;
};

NS_END

#endif