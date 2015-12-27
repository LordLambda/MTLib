#ifndef STACKTRACE_HPP
#define STACKTRACE_HPP

#include "Common.h"

class MapFile;

/** Stack tracing utility. */
class EXPORT StackTrace {
public:
	/**
	* Prints formatted call stack to the user buffer.
	* Always terminates the user buffer with 0.
	*
	* @param map Array of pointers to map files.
	* @param maps Number of map files.
	* @param initLevel Number of functions to skip before starting the tracing.
	* @param maxDepth Maximum number of levels in the stack trace.
	* @param buffer [out] Output buffer for the formatted stack trace.
	* @param bufferSize Size of the output buffer.
	* @return Needed buffer size.
	*/
	static int	printStackTrace(MapFile** map, int maps,
		int initLevel, int maxDepth,
		char* buffer, int bufferSize);
};

#endif
