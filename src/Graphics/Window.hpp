#ifndef WINDOW_HPP
#define WINDOW_HPP

#include "../Config.hpp"

NS_BEGIN

/// <summary>
/// Handles the opening, running, and closing of the game window
/// </summary>
class Window
{
public:
	Window();
	~Window();

	/// <summary>
	/// Sets up a window and initializes Direct3D
	/// </summary>
	bool Initialize(HINSTANCE hInstance, UINT windowWidth = 800, UINT windowHeight = 600, char* windowTitle = "Windows Application");

	/// <summary>
	/// Handles resizing of the window
	/// </summary>
	void OnResize(UINT newWidth, UINT newHeight);

	/// <summary>
	/// Closes the window
	/// </summary>
	void Close(void);

	float GetAspectRatio()const;
	bool GetOpen()const;
	UINT GetWindowWidth()const;
	UINT GetWindowHeight()const;
	HWND GetWindowHandle()const;
	bool GetFullScreen()const;
private:
	HINSTANCE hInstance;
	HWND	  hWnd;

	UINT windowWidth;
	UINT windowHeight;
	char* windowTitle;
	bool isFullScreen;
	bool isOpen;
};

NS_END

#endif