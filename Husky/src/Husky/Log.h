#pragma once
#include <SDL.h>
#include <ostream>

namespace husky {

	void logSDLError(std::ostream& os, const std::string& msg)
	{
		os << "SDL Error: " << msg << ". " << SDL_GetError() << std::endl;
	}

	void logClientError(std::ostream& os, const std::string& msg)
	{
		os << "Client Error: " << msg << "." << std::endl;
	}

	void logClientTrace(std::ostream& os, const std::string& msg)
	{
		os << "Client Trace: " << msg << "." << std::endl;
	}

	void logCoreTrace(std::ostream& os, const std::string& msg)
	{
		os << "Core Trace: " << msg << "." << std::endl;
	}

}

#ifdef _DEBUG
	#define HS_LOG(os, msg) husky::logClientTrace(os, msg)
	#define HS_CORE_LOG(os, msg) husky::logCoreTrace(os, msg)
	#define HS_ERROR(os, msg) husky::logClientError(os, msg)
	#define HS_CORE_ERROR(os, msg) husky::logSDLError(os, msg)
#else
	#define HS_LOG(os, msg)
	#define HS_CORE_LOG(os, msg)
	#define HS_ERROR(os, msg)
	#define HS_CORE_ERROR(os, msg)
#endif
