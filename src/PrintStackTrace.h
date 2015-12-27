#ifndef PRINTSTACKTRACE_H
#define PRINTSTACKTRACE_H

#include "StackTrace.hpp"
#include "file/MapFile.hpp"
#include "Common.h"

/**
* Prints formatted call stack to the user defined buffer,
* always terminating the buffer with 0.
* Uses stack frame to find out the caller function address and
* the map file to find out the function name.
*/
extern EXPORT void printStackTrace(char* buffer, int bufferSize);
extern EXPORT void printStackTrace();
extern EXPORT void AssertFailed(const char* fname, int line, const char* expr);

#endif
