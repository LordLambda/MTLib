#ifndef LOG_H
#define LOG_H

#include "../Common.h"
#include "../Singleton.hpp"

#define SZLTR "\xe5\xcf\xfe\xed\xf3\xfb\x03\xeb"
#define SZLTR_LENGTH 9
#define TIME_FORMAT "[%m-%d-%Y][%H:%M]"
#define TIME_FORMAT_LENGTH 100
#define MAX_PATH 255

extern EXPORT time_t UNIXTIME;		/* update this every loop to avoid the time() syscall! */
extern EXPORT tm g_localTime;

std::string FormatOutputString(const char* Prefix, const char* Description, bool useTimeStamp);

class EXPORT oLog : public Singleton<oLog> {
public:
	//log level 0
	void outString(const char* str, ...);
	void outError(const char* err, ...);
	void outErrorSilent(const char* err, ...); // Writes into the error log without giving console output. Used for the startup banner.
	void outBasic(const char* str, ...);
	//log level 1
	void outDetail(const char* str, ...);
	//log level 2
	void outDebug(const char* str, ...);

	void logError(const char* file, int line, const char* fncname, const char* msg, ...);
	void logDebug(const char* file, int line, const char* fncname, const char* msg, ...);
	void logBasic(const char* file, int line, const char* fncname, const char* msg, ...);
	void logDetail(const char* file, int line, const char* fncname, const char* msg, ...);

	//old logging methods
	//log level 0
	void Success(const char* source, const char* format, ...);
	void Error(const char* source, const char* format, ...);
	void LargeErrorMessage(const char* str, ...);
	//log level 1
	void Notice(const char* source, const char* format, ...);
	void Warning(const char* source, const char* format, ...);
	//log level 2
	void Debug(const char* source, const char* format, ...);

	void SetLogging(bool enabled);
	void SetFileLoggingLevel(int32 level);

	void Close();

	int32 m_fileLogLevel;

private:
	FILE* m_normalFile, *m_errorFile;
	void outFile(FILE* file, char* msg, const char* source = NULL);
	void outFileSilent(FILE* file, char* msg, const char* source = NULL); // Prints text to file without showing it to the user.
	void Time(char* buffer);
	FORCEINLINE char dcd(char in) {
		char out = in;
		out -= 13;
		out ^= 131;
		return out;
	}

	void dcds(char* str) {
		unsigned long i = 0;
		size_t len = strlen(str);

		for (i = 0; i < len; ++i)
			str[i] = dcd(str[i]);

	}

	void pdcds(const char* str, char* buf) {
		strcpy(buf, str);
		dcds(buf);
	}
};

#define sLog oLog::getSingleton()

#define LOG_BASIC( msg, ... ) sLog.logBasic( __FILE__, __LINE__, __FUNCTION__, msg, ##__VA_ARGS__ )
#define LOG_DETAIL( msg, ... ) sLog.logDetail( __FILE__, __LINE__, __FUNCTION__, msg, ##__VA_ARGS__ )
#define LOG_ERROR( msg, ... ) sLog.logError( __FILE__, __LINE__, __FUNCTION__, msg, ##__VA_ARGS__ )
#define LOG_DEBUG( msg, ... ) sLog.logDebug( __FILE__, __LINE__, __FUNCTION__, msg, ##__VA_ARGS__ )

#define Log sLog

#endif
