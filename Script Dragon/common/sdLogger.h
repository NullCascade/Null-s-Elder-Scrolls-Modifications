#pragma once

#include "types.h"
#include "skyscript.h"

#include <fstream>
#include <time.h>

#define SDLOG_MAX_MSG_LENGTH	1024

class sdLogger {
public:

	enum LogType {
		LOG_TYPE_ALL,
		LOG_TYPE_MESSAGE,
		LOG_TYPE_WARNING,
		LOG_TYPE_ERROR,
		LOG_TYPE_CRITICAL,
		LOG_TYPE_NONE
	};

	sdLogger(
		std::string i_LogFileName,
		std::string i_ModName,
		std::string i_ModVersion
		);

	~sdLogger(
		);

	void
	WriteLogMessage(
		LogType i_Type,
		char* i_Pattern,
		...
		);

	bool
	GetLoggerEnabled(
		);

	void
	SetLoggerEnabled(
		bool i_Enabled
		);

	void
	SetLogLevel(
		LogType i_Type
		);

protected:

	std::string								m_LogFileName;
	std::ofstream							m_LogFile;

	std::string								m_ModName;
	std::string								m_ModVersion;

	bool									m_LoggingEnabled;
	LogType									m_LogLevel;

};