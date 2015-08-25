#ifndef DEBUG_HPP
#define DEBUG_HPP

#ifdef DEBUG

#include "../../Config.hpp"

NS_BEGIN

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