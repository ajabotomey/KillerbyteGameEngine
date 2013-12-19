#include "LogManager.h"

namespace KillerbyteGameEngine
{
	static LogManager* instance = NULL;

	LogManager::LogManager()
	{
		instance = this;
	}

	LogManager::~LogManager()
	{
		out.close();
	}

	LogManager* LogManager::GetInstance()
	{
		if (instance == NULL)
		{
			instance = new LogManager();
		}

		return instance;
	}

	// This will be different for each platform
	// If on a computer, we add this into a file
	// If on a mobile
	void LogManager::WriteLog(std::string message)
	{
#if defined WIN32 || defined __linux__ || defined TARGET_OS_OSX
		out << message << std::endl;
#elif __ANDROID__
		LOGI(message);
#elif TARGET_OS_IPHONE

#endif
	}

	void LogManager::WriteLogToConsole(const char* message, ...)
	{
		char ErrStr[128];
		char Status[128];
		int flag = 1;

#if defined WIN32 || defined __linux__ || defined TARGET_OS_OSX
		va_list arglist;

		va_start(arglist, message);

		//customized operations...
		if (flag<0)
			vsprintf(ErrStr, message, arglist);
		else if (flag >= 0)
			vsprintf(Status, message, arglist);

		va_end(arglist);
#elif defined __ANDROID__
		LOGI("%s", message);
#endif
	}

#if defined WIN32 || defined __linux__ || defined TARGET_OS_OSX
	bool LogManager::LoadLogFile(const char* filename)
	{
		out.open(filename, std::ofstream::out | std::ofstream::app);

		if (!out.is_open())
		{
			return false;
		}

		return true;
	}
#endif
}