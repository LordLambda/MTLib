#include "../file/config/ConfigEnv.h"
#include <cstdarg>

string FormatOutputString(const char* Prefix, const char* Description, bool useTimeStamp) {
	char p[MAX_PATH];
	p[0] = 0;
	time_t t = time(NULL);
	tm* a = gmtime(&t);
	strcat(p, Prefix);
	strcat(p, "/");
	strcat(p, Description);
	if (useTimeStamp) {
		char ftime[100];
		snprintf(ftime, 100, "-%-4d-%02d-%02d %02d-%02d-%02d", a->tm_year + 1900, a->tm_mon + 1, a->tm_mday, a->tm_hour, a->tm_min, a->tm_sec);
		strcat(p, ftime);
	}
	strcat(p, ".log");
	return string(p);
}

createFileSingleton(oLog);

EXPORT time_t UNIXTIME;
EXPORT tm g_localTime;

void oLog::outFile(FILE* file, char* msg, const char* source) {
	char time_buffer[TIME_FORMAT_LENGTH];
	char szltr_buffer[SZLTR_LENGTH];
	Time(time_buffer);
	pdcds(SZLTR, szltr_buffer);

	if (source != NULL) {
		fprintf(file, "%s%s%s: %s\n", time_buffer, szltr_buffer, source, msg);
		printf("%s%s%s: %s\n", time_buffer, szltr_buffer, source, msg);
	}else {
		fprintf(file, "%s%s%s\n", time_buffer, szltr_buffer, msg);
		printf("%s%s%s\n", time_buffer, szltr_buffer, msg);
	}
}

/// Prints text to file without showing it to the user.
void oLog::outFileSilent(FILE* file, char* msg, const char* source) {
	char time_buffer[TIME_FORMAT_LENGTH];
	char szltr_buffer[SZLTR_LENGTH];
	Time(time_buffer);
	pdcds(SZLTR, szltr_buffer);

	if (source != NULL) {
		fprintf(file, "%s%s%s: %s\n", time_buffer, szltr_buffer, source, msg);
		// Don't use printf to prevent text from being shown in the console output.
	}else {
		fprintf(file, "%s%s%s\n", time_buffer, szltr_buffer, msg);
		// Don't use printf to prevent text from being shown in the console output.
	}
}

void oLog::Time(char* buffer) {
	time_t now;
	struct tm* timeinfo = NULL;

	time(&now);
	timeinfo = localtime(&now);

	if (timeinfo != NULL) {
		strftime(buffer, TIME_FORMAT_LENGTH, TIME_FORMAT, timeinfo);
	}else {
		buffer[0] = '\0';
	}
}

void oLog::outString(const char* str, ...) {
	if (m_normalFile == NULL)
		return;

	char buf[32768];
	va_list ap;

	va_start(ap, str);
	vsnprintf(buf, 32768, str, ap);
	va_end(ap);

	outFile(m_normalFile, buf);
}

void oLog::outError(const char* err, ...) {
	if (m_errorFile == NULL)
		return;

	char buf[32768];
	va_list ap;

	va_start(ap, err);
	vsnprintf(buf, 32768, err, ap);
	va_end(ap);

	outFile(m_errorFile, buf);
}

/// Writes into the error log without giving console output. Used for the startup banner.
void oLog::outErrorSilent(const char* err, ...) {
	if (m_errorFile == NULL)
		return;

	char buf[32768];
	va_list ap;

	va_start(ap, err);
	vsnprintf(buf, 32768, err, ap);
	va_end(ap);

	outFileSilent(m_errorFile, buf); // This uses a function that won't give console output.
}

void oLog::outBasic(const char* str, ...) {
	if (m_normalFile == NULL)
		return;

	char buf[32768];
	va_list ap;

	va_start(ap, str);
	vsnprintf(buf, 32768, str, ap);
	va_end(ap);

	outFile(m_normalFile, buf);
}

void oLog::outDetail(const char* str, ...) {
	if (m_fileLogLevel < 1 || m_normalFile == NULL)
		return;

	char buf[32768];
	va_list ap;

	va_start(ap, str);
	vsnprintf(buf, 32768, str, ap);
	va_end(ap);

	outFile(m_normalFile, buf);
}

void oLog::outDebug(const char* str, ...) {
	if (m_fileLogLevel < 2 || m_errorFile == NULL)
		return;

	char buf[32768];
	va_list ap;

	va_start(ap, str);
	vsnprintf(buf, 32768, str, ap);
	va_end(ap);

	outFile(m_errorFile, buf);
}

void oLog::logBasic(const char* file, int line, const char* fncname, const char* msg, ...) {
	if (m_normalFile == NULL)
		return;

	char buf[32768];
	char message[32768];

	snprintf(message, 32768, " [BSC] %s:%d %s %s", file, line, fncname, msg);
	va_list ap;

	va_start(ap, msg);
	vsnprintf(buf, 32768, message, ap);
	va_end(ap);

	outFile(m_normalFile, buf);
}

void oLog::logDetail(const char* file, int line, const char* fncname, const char* msg, ...) {
	if ((m_fileLogLevel < 1) || (m_normalFile == NULL))
		return;

	char buf[32768];
	char message[32768];

	snprintf(message, 32768, " [DTL] %s:%d %s %s", file, line, fncname, msg);
	va_list ap;

	va_start(ap, msg);
	vsnprintf(buf, 32768, message, ap);
	va_end(ap);

	outFile(m_normalFile, buf);
}

void oLog::logError(const char* file, int line, const char* fncname, const char* msg, ...) {
	if (m_errorFile == NULL)
		return;

	char buf[32768];
	char message[32768];

	snprintf(message, 32768, " [ERR] %s:%d %s %s", file, line, fncname, msg);
	va_list ap;

	va_start(ap, msg);
	vsnprintf(buf, 32768, message, ap);
	va_end(ap);

	outFile(m_errorFile, buf);
}

void oLog::logDebug(const char* file, int line, const char* fncname, const char* msg, ...) {
	if ((m_fileLogLevel < 2) || (m_errorFile == NULL))
		return;

	char buf[32768];
	char message[32768];

	snprintf(message, 32768, " [DBG] %s:%d %s %s", file, line, fncname, msg);
	va_list ap;

	va_start(ap, msg);
	vsnprintf(buf, 32768, message, ap);
	va_end(ap);

	outFile(m_errorFile, buf);
}

//old Log methods
void oLog::Notice(const char* source, const char* format, ...) {
	if (m_fileLogLevel < 1 || m_normalFile == NULL)
		return;

	char buf[32768];
	va_list ap;

	va_start(ap, format);
	vsnprintf(buf, 32768, format, ap);
	va_end(ap);

	outFile(m_normalFile, buf, source);
}

void oLog::Warning(const char* source, const char* format, ...) {
	if (m_fileLogLevel < 1 || m_normalFile == NULL)
		return;

	char buf[32768];
	va_list ap;

	va_start(ap, format);
	vsnprintf(buf, 32768, format, ap);
	va_end(ap);

	outFile(m_normalFile, buf, source);
}

void oLog::Success(const char* source, const char* format, ...) {
	if (m_normalFile == NULL)
		return;

	char buf[32768];
	va_list ap;

	va_start(ap, format);
	vsnprintf(buf, 32768, format, ap);
	va_end(ap);

	outFile(m_normalFile, buf, source);
}

void oLog::Error(const char* source, const char* format, ...) {
	if (m_errorFile == NULL)
		return;

	char buf[32768];
	va_list ap;

	va_start(ap, format);
	vsnprintf(buf, 32768, format, ap);
	va_end(ap);

	outFile(m_errorFile, buf, source);
}

void oLog::Debug(const char* source, const char* format, ...) {
	if (m_fileLogLevel < 2 || m_errorFile == NULL)
		return;

	char buf[32768];
	va_list ap;

	va_start(ap, format);
	vsnprintf(buf, 32768, format, ap);
	va_end(ap);

	outFile(m_errorFile, buf, source);
}

void oLog::LargeErrorMessage(const char* source, ...) {
	std::vector<char*> lines;
	char* pointer;
	va_list ap;
	va_start(ap, source);

	pointer = const_cast<char*>(source);
	lines.push_back(pointer);

	size_t i, j, k;
	pointer = va_arg(ap, char*);
	while (pointer != NULL) {
		lines.push_back(pointer);
		pointer = va_arg(ap, char*);
	}

	outError("*********************************************************************");
	outError("*                        MAJOR ERROR/WARNING                        *");
	outError("*                        ===================                        *");

	for (std::vector<char*>::iterator itr = lines.begin(); itr != lines.end(); ++itr) {
		stringstream sstext;
		i = strlen(*itr);
		j = (i <= 65) ? 65 - i : 0;
		sstext << "* " << *itr;
		for (k = 0; k < j; ++k) {
			sstext << " ";
		}

		sstext << " *";
		outError(sstext.str().c_str());
	}

	outError("*********************************************************************");
}

void oLog::Close() {
	if (m_normalFile != NULL) {
		fflush(m_normalFile);
		fclose(m_normalFile);
		m_normalFile = NULL;
	}

	if (m_errorFile != NULL) {
		fflush(m_errorFile);
		fclose(m_errorFile);
		m_errorFile = NULL;
	}
}

void oLog::SetFileLoggingLevel(int32 level) {
	//log level -1 is no more allowed
	if (level >= 0)
		m_fileLogLevel = level;
}
