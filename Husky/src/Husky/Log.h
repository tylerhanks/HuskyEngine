#pragma once
#include <ostream>
#include <string>

namespace husky {

	void logSDLError(std::ostream& os, const std::string& msg);

	void logClientError(std::ostream& os, const std::string& msg);

	void logClientTrace(std::ostream& os, const std::string& msg);

	void logCoreTrace(std::ostream& os, const std::string& msg);

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
