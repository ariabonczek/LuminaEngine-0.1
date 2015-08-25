#include "Window.hpp"

#include "../Game.hpp"

NS_BEGIN

LRESULT CALLBACK WindowProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	return Game::GetInstance()->MsgProc(hwnd, msg, wParam, lParam);
}

Window::Window():
hInstance(0),
hWnd(0),
windowWidth(0),
windowHeight(0),
windowTitle(""),
isFullScreen(false),
isOpen(false)
{}

Window::~Window()
{}

bool Window::Initialize(HINSTANCE hInstance, UINT windowWidth, UINT windowHeight, char* windowTitle)
{
	this->hInstance = hInstance;
	this->windowWidth = windowWidth;
	this->windowHeight = windowHeight;
	this->windowTitle = windowTitle;

	// TODO: Custom Cursor/Icon support
	WNDCLASS wc;
	ZeroMemory(&wc, sizeof(WNDCLASS));
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = WindowProc;
	wc.hInstance = hInstance;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hIcon = LoadIcon(0, IDI_APPLICATION);
	wc.lpszMenuName = NULL;
	wc.lpszClassName = "WindowClassMain";
	wc.hbrBackground = (HBRUSH)GetStockObject(NULL_BRUSH);
	wc.cbWndExtra = NULL;
	wc.cbClsExtra = NULL;

	if (!RegisterClass(&wc))
	{
		MessageBox(NULL, "RegisterClass failed.", NULL, NULL);
		return false;
	}

	RECT wr = { 0, 0, windowWidth, windowHeight };
	AdjustWindowRect(&wr, WS_OVERLAPPEDWINDOW, FALSE);

	hWnd = CreateWindow(
		"WindowClassMain",
		windowTitle,
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		wr.right - wr.left,
		wr.bottom - wr.top,
		NULL,
		NULL,
		hInstance,
		NULL);

	if (!hWnd)
	{
		MessageBox(NULL, "CreateWindow Failed.", NULL, NULL);
		return false;
	}

	ShowWindow(hWnd, SW_SHOW);
	UpdateWindow(hWnd);
	isOpen = true;

	return true;
}

void Window::OnResize(UINT newWidth, UINT newHeight)
{
	windowWidth = newWidth;
	windowHeight = newHeight;
}

void Window::Close()
{
	isOpen = false;
	Window::~Window();
}

float Window::GetAspectRatio(void)const
{
	return (float)windowWidth / windowHeight;
}

bool Window::GetOpen(void)const
{
	return isOpen;
}

UINT Window::GetWindowWidth()const
{
	return windowWidth;
}

UINT Window::GetWindowHeight()const
{
	return windowHeight;
}

HWND Window::GetWindowHandle()const
{
	return hWnd;
}

bool Window::GetFullScreen()const
{
	return isFullScreen;
}

NS_END