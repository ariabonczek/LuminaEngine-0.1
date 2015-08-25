#include "Debug.hpp"

#ifdef DEBUG

NS_BEGIN

HANDLE Debug::consoleHandle;

void Debug::Initialize()
{
	AllocConsole();
	AttachConsole(GetCurrentProcessId());
	consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
}

void Debug::Shutdown()
{
	FreeConsole();
}

void Debug::Log(std::string s)
{
	s.append("\n");
	SetConsoleTextAttribute(consoleHandle, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
	DWORD written;
	WriteConsole(consoleHandle, s.c_str(), strlen(s.c_str()), &written, NULL);
}

void Debug::LogError(std::string s)
{
	s.append("\n");
	SetConsoleTextAttribute(consoleHandle, FOREGROUND_RED | FOREGROUND_INTENSITY);
	DWORD written;
	WriteConsole(consoleHandle, s.c_str(), strlen(s.c_str()), &written, NULL);
}

NS_END

#endif