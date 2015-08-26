#ifndef DEBUG_HPP
#define DEBUG_HPP

#ifdef DEBUG

#include "../../Config.hpp"

NS_BEGIN

struct Vector2;
struct Vector3;
struct Vector4;
struct Matrix;

// TODO: Create a debug console library! Some debug draws wouldn't be so bad either!

class Debug
{
public:
	
	static void Initialize();

	static void Shutdown();

	/// <summary>
	/// Log a message in white text
	/// </summary>
	static void Log(std::string s);
	static void Log(float f);
	static void Log(double d);
	static void Log(int i);
	static void Log(Vector2 v);
	static void Log(Vector3 v);
	static void Log(Vector4 v);
	static void Log(Matrix m);

	/// <summary>
	/// Log a message in red text
	/// </summary>
	static void LogError(std::string s);
private:
	static HANDLE consoleHandle;
};

NS_END

#endif
#endif