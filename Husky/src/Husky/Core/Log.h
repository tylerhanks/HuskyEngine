#pragma once
#include <ostream>
#include <string>

namespace husky {
	namespace log {

		void SetLogOutput(std::ostream& os);

		void logSDLError(const std::string& msg);

		void logClientError(const std::string& msg);

		void logClientTrace(const std::string& msg);

		void logCoreTrace(const std::string& msg);

	}
}
#ifdef HS_DEBUG
	#define HS_LOG(msg) husky::log::logClientTrace(msg)
	#define HS_CORE_LOG(msg) husky::log::logCoreTrace(msg)
	#define HS_ERROR(msg) husky::log::logClientError(msg)
	#define HS_CORE_ERROR(msg) husky::log::logSDLError(msg)
#else
	#define HS_LOG(msg)
	#define HS_CORE_LOG(msg)
	#define HS_ERROR(msg)
	#define HS_CORE_ERROR(msg)
#endif
