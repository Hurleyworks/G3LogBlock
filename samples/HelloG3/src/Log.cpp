// This source file was auto-generated by ClassMate++
// Created: 11 Oct 2015 5:21:41 pm
// Copyright (c) 2015, HurleyWorks

#include "Log.h"

// ctor
Log::Log(const std::string & logFolder, const std::string & appName)
	:logFolder(logFolder),
	 logger(g2::LogWorker::createWithDefaultLogger(appName, logFolder))
{	
	g2::initializeLogging(logger.worker.get());
	g2::setFatalExitHandler(&Log::onFatalError);

#if WIN32
	g2::setFatalPreLoggingHook([] {__debugbreak(); });
#endif

	g2::setLogLevel(TESTING, false);
	g2::setLogLevel(DBUG, true);
	g2::setLogLevel(INFO, true);
	g2::setLogLevel(WARNING, true);
	g2::setLogLevel(CRITICAL, true);
}

// dtor
Log::~Log ()
{	
	LOG(DBUG) << __FUNCTION__;
}

void Log::ReverseToOriginalFatalHandling()
{
	#if !(defined(DISABLE_FATAL_SIGNALHANDLING))
		if (SIG_ERR == signal(SIGABRT, SIG_DFL))
			perror("signal - SIGABRT");

		if (SIG_ERR == signal(SIGFPE, SIG_DFL))
			perror("signal - SIGABRT");

		if (SIG_ERR == signal(SIGSEGV, SIG_DFL))
			perror("signal - SIGABRT");

		if (SIG_ERR == signal(SIGILL, SIG_DFL))
			perror("signal - SIGABRT");

		if (SIG_ERR == signal(SIGTERM, SIG_DFL))
			perror("signal - SIGABRT");
	#endif
}

void Log::onFatalError(g2::FatalMessagePtr fatal_message)
{
	ReverseToOriginalFatalHandling();
	
	// maybe save your work here

	// now ready to exit, instead of reinventing the wheel we do it the g3log way
	g2::internal::pushFatalMessageToLogger(fatal_message);
}
