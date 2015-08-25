#include "Game.hpp"

NS_BEGIN

Game Game::instance;

Game::Game()
{}

Game::~Game()
{}

bool Game::Initialize()
{
#ifdef DEBUG
	Debug::Initialize();
#endif

	if (!window.Initialize(GetModuleHandle(NULL), WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_TITLE))
		return false;
	if (!graphicsDevice.Initialize(window))
		return false;
	if (!ResourceManager::Initialize(&graphicsDevice))
		return false;
	if (!Renderer::Initialize())
		return false;

	Shader::InitializeStatic();
	Material::InitializeStatic();
	Sampler::InitializeStatic();

	return true;	
}

int Game::Run()
{
	MSG msg = { 0 };

	// TODO: Implement SceneManager to handle transitions, loading/unloading resources dynamically
	scene.LoadResources();
	Renderer::InitializeScene(scene);

	while (msg.message != WM_QUIT)
	{

		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			graphicsDevice.Clear();

			scene.Update(0.0f);
			Renderer::RenderScene(scene);
			
			graphicsDevice.Display();
		}

	}

	// UnloadResources

	Shutdown();

	return (int)msg.wParam;
}

bool Game::Shutdown()
{
#if DEBUG
	Debug::Shutdown();
#endif
	// Be sure to do this later in the process
	ResourceManager::FreeResources();
	Renderer::Shutdown();
	Material::ShutdownStatic();
	Shader::Shutdown();

	return true;
}

Game* Game::GetInstance()
{
	return &instance;
}

LRESULT Game::MsgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_SIZE:
		if (graphicsDevice.IsInitialized())
		{
			window.OnResize(LOWORD(lParam), HIWORD(lParam));
			graphicsDevice.OnResize(LOWORD(lParam), HIWORD(lParam));
		}
		return 0;
	case WM_ENTERSIZEMOVE:
		return 0;
	case WM_EXITSIZEMOVE:
		graphicsDevice.OnResizeExit();
		return 0;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	case WM_MENUCHAR:
		return MAKELRESULT(0, MNC_CLOSE);
	case WM_GETMINMAXINFO:
		((MINMAXINFO*)lParam)->ptMinTrackSize.x = 200;
		((MINMAXINFO*)lParam)->ptMinTrackSize.y = 200;
		return 0;
	}
	return DefWindowProc(hWnd, msg, wParam, lParam);
}
NS_END