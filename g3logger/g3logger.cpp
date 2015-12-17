#pragma once

#include "g3logger.h"

#if (defined (_WIN32) || defined (_WIN64))
	#include "g3log/stacktrace_windows.cpp"
	#include "g3log/crashhandler_windows.cpp"
#elif defined (__APPLE_CPP__) || defined(__APPLE_CC__)
	#include "g3log/crashhandler_unix.cpp"
#endif

#include "g3log/time.cpp"
#include "g3log/logworker.cpp"
#include "g3log/logmessage.cpp"
#include "g3log/loglevels.cpp"
#include "g3log/logcapture.cpp"
#include "g3log/g3log.cpp"
#include "g3log/filesink.cpp"
