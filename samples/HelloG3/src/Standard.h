
#pragma once

#include <string>

const std::string appName = "HelloG3";
const float appHeight = 600.0f;
const float appWidth = 1.618f * appHeight;

#define APP_MAJOR_VERSION      0
#define APP_MINOR_VERSION      8
#define APP_POINT_RELEASE      0
#define APP_VERSION (( APP_MAJOR_VERSION << 16) + ( APP_MINOR_VERSION << 8))

inline std::string getAppVersion()
{
	return std::to_string(APP_MAJOR_VERSION) + "." +
		std::to_string(APP_MINOR_VERSION) + "." +
		std::to_string(APP_POINT_RELEASE);
}

inline std::string getTitle()
{
	std::string name = appName;
	std::string version = getAppVersion();
	std::string mode = "";
#ifndef NDEBUG
	mode = " debug";
#endif
	return  name + " " + version + mode;
}