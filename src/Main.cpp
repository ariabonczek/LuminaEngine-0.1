#include "Game.hpp"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR cmdLine, int showCmd)
{
	Lumina::Game* game = Lumina::Game::GetInstance();

	if (!game->Initialize())
		return 0;
	return game->Run();
}