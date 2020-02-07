#include "Log.h"
#include <SDL.h>

void husky::logSDLError(std::ostream& os, const std::string& msg)
{
	os << "SDL Error: " << msg << ". " << SDL_GetError() << std::endl;
}

void husky::logClientError(std::ostream& os, const std::string& msg)
{
	os << "Client Error: " << msg << "." << std::endl;
}

void husky::logClientTrace(std::ostream& os, const std::string& msg)
{
	os << "Client Trace: " << msg << "." << std::endl;
}

void husky::logCoreTrace(std::ostream& os, const std::string& msg)
{
	os << "Core Trace: " << msg << "." << std::endl;
}
