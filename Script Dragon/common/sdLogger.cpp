#include "sdLogger.h"

sdLogger::sdLogger(
	std::string i_LogFileName,
	std::string i_ModName,
	std::string i_ModVersion
	)
  : m_LogFileName( i_LogFileName ),
	m_ModName( i_ModName ),
	m_ModVersion( i_ModVersion ),
	m_LoggingEnabled( false )
{
	// Open file.
	m_LogFile.open( m_LogFileName.c_str(), std::ios_base::out|std::ios_base::trunc );

	// Initial writes.
	time_t curTime(0);
	struct tm * locTime = localtime( &curTime );
	m_LogFile << "Debug Logger by NullCascade" << std::endl;
	m_LogFile << " --- Mod Info ---" << std::endl;
	m_LogFile << i_ModName << " " << i_ModVersion << std::endl;
	m_LogFile << "Build: " << __TIMESTAMP__ << std::endl;
	m_LogFile << " --- Generated ---" << std::endl;
	m_LogFile << "Date: " << locTime->tm_year << "-" << locTime->tm_mon << "-" << locTime->tm_mday << std::endl;
	m_LogFile << "Time: " << locTime->tm_hour << ":" << locTime->tm_min << ":" << locTime->tm_sec << std::endl;
	m_LogFile << " --- Action Log ---" << std::endl;
}

sdLogger::~sdLogger(
	)
{
	if ( m_LogFile.is_open() ) m_LogFile.close();
}

void
sdLogger::WriteLogMessage(
	LogType i_Type,
	char* i_Pattern,
	...
	)
{
	// Is debugging enabled?
	if ( !m_LoggingEnabled ) return;

	// Is this a high enough log level?
	if ( i_Type > m_LogLevel ) return;

	// Build the message.
	char dbgMessage[SDLOG_MAX_MSG_LENGTH];
	va_list vlist;
	va_start( vlist, i_Pattern );
	vsprintf_s( dbgMessage, i_Pattern, vlist );
	va_end( vlist );

	// Output Windows debug message.
	OutputDebugStringA( dbgMessage );

	// Log to file.
	if ( m_LogFile.is_open() ) {
		m_LogFile << "[" << time(0) << "] " << dbgMessage << std::endl;
	}
}

bool
sdLogger::GetLoggerEnabled(
	)
{
	return m_LoggingEnabled;
}

void
sdLogger::SetLoggerEnabled(
	bool i_Enabled
	)
{
	m_LoggingEnabled = i_Enabled;
}

void
sdLogger::SetLogLevel(
	LogType i_Type
	)
{
	m_LogLevel = i_Type;
}