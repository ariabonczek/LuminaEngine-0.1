#include "Debug.hpp"
#include "../../Lumina.hpp"

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

void Debug::Log(float f)
{
	Log(std::to_string(f));
}
void Debug::Log(double d)
{
	Log(std::to_string(d));
}
void Debug::Log(int i)
{
	Log(std::to_string(i));
}
void Debug::Log(Vector2 v)
{
	// TODO: Optimize
	Log("X: " + std::to_string(v.x) + " Y: " + std::to_string(v.y));
}
void Debug::Log(Vector3 v)
{
	Log("X: " + std::to_string(v.x) + " Y: " + std::to_string(v.y) + " Z: " + std::to_string(v.z));

}
void Debug::Log(Vector4 v)
{
	Log("X: " + std::to_string(v.x) + " Y: " + std::to_string(v.y) + " Z: " + std::to_string(v.z) + " W: " + std::to_string(v.w));
}
void Debug::Log(Matrix m)
{
	Log(std::to_string(m.m11) + " " + std::to_string(m.m12) + " " + std::to_string(m.m13) + " " + std::to_string(m.m14));
	Log(std::to_string(m.m21) + " " + std::to_string(m.m22) + " " + std::to_string(m.m23) + " " + std::to_string(m.m24));
	Log(std::to_string(m.m31) + " " + std::to_string(m.m32) + " " + std::to_string(m.m33) + " " + std::to_string(m.m34));
	Log(std::to_string(m.m41) + " " + std::to_string(m.m42) + " " + std::to_string(m.m43) + " " + std::to_string(m.m44));
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