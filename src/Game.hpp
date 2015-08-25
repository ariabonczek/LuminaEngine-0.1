#ifndef GAME_HPP
#define GAME_HPP

#include "Lumina.hpp"

#include "TestGame\TestScene.hpp"

NS_BEGIN

/// <summary>
/// Singleton class to represent our entire game
/// </summary>
class Game
{
public:
	~Game();

	/// <summary>
	/// Returns a pointer to the game instance
	/// </summary>
	static Game* GetInstance();

	/// <summary>
	/// Initializes the game and its subsystems
	/// </summary>
	bool Initialize();

	/// <summary>
	/// Launches the game and enters the game loop
	/// </summary>
	int Run();

	/// <summary>
	/// Handles safe shutdown of the game and its subsystems
	/// </summary>
	bool Shutdown();

	/// <summary>
	/// Handles Windows messages
	/// </summary>
	LRESULT MsgProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
private:
	Game();
	static Game instance;

	Window window;
	GraphicsDevice graphicsDevice;

	TestScene scene;
};
NS_END


#endif