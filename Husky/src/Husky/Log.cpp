#include "Log.h"
#include <SDL.h>
#include <iostream>
#include <Windows.h>

static std::ostream* s_log_os = &std::cout;
static auto handle = GetStdHandle(STD_OUTPUT_HANDLE);

void husky::log::logSDLError(const std::string& msg)
{
	SetConsoleTextAttribute(handle, 4);
	(*s_log_os) << "SDL Error: " << msg << ". " << SDL_GetError() << std::endl;
}

void husky::log::logClientError(const std::string& msg)
{
	SetConsoleTextAttribute(handle, 14);
	(*s_log_os) << "Client Error: " << msg << "." << std::endl;
}

void husky::log::logClientTrace(const std::string& msg)
{
	SetConsoleTextAttribute(handle, 5);
	(*s_log_os) << "Client Trace: " << msg << "." << std::endl;
}

void husky::log::logCoreTrace(const std::string& msg)
{
	SetConsoleTextAttribute(handle, 9);
	(*s_log_os) << "Core Trace: " << msg << "." << std::endl;
}

void husky::log::SetLogOutput(std::ostream& os)
{
	s_log_os = &os;
}
