#ifndef LOGMANAGER_H
#define LOGMANAGER_H

#include <cstdarg>

#include "Base.h"
#include "Object.h"

#ifdef __ANDROID__
#include <android/log.h>
#endif

namespace KillerbyteGameEngine
{
	class LogManager : public Object
	{
	public:
		~LogManager();

		static LogManager* GetInstance();

		void WriteLog(std::string message);

		// Windows, Mac, Linux Log file writer methods
#if defined WIN32 || defined __linux__ || defined TARGET_OS_OSX
		bool LoadLogFile(const char* file);
#endif
		
		// Default log to console
		void WriteLogToConsole(const char *message, ...);
	protected:
		LogManager();
	private:
		std::ofstream out;
	};
}

#endif