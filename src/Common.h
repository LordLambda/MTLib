#ifndef COMMON_H
#define COMMON_H

#if defined( __WIN32__ ) || defined( WIN32 ) || defined( _WIN32 ) //if windows machine
#  define WIN32_LEAN_AND_MEAN //cut out dependencies on windows.h
#  include <windows.h>
#  undef NOMINMAX
#endif

#include <cstring>

#ifdef WIN32 //if 32 bit windows
#pragma warning(disable:4996) //Disable stupid dll-warnings
#define _CRT_SECURE_NO_DEPRECATE 1
#define _CRT_SECURE_COPP_OVERLOAD_STANDARD_NAMES 1
#pragma warning(disable:4251)		// Windows needs this disabled because it sucks
#endif

enum TimeVariables //Regular time variables
{
	TIME_SECOND = 1,
	TIME_MINUTE = TIME_SECOND * 60,
	TIME_HOUR = TIME_MINUTE * 60,
	TIME_DAY = TIME_HOUR * 24,
	TIME_MONTH = TIME_DAY * 30,
	TIME_YEAR = TIME_MONTH * 12
};

enum MsTimeVariables //Millisecond time variables.
{
	MSTIME_SECOND = 1000,
	MSTIME_6SECONDS = MSTIME_SECOND * 6,
	MSTIME_MINUTE = MSTIME_SECOND * 60,
	MSTIME_HOUR = MSTIME_MINUTE * 60,
	MSTIME_DAY = MSTIME_HOUR * 24
};

#define PLATFORM_WIN32 0
#define PLATFORM_UNIX  1
#define PLATFORM_APPLE 2

#define UNIX_FLAVOUR_LINUX 1
#define UNIX_FLAVOUR_BSD 2
#define UNIX_FLAVOUR_OTHER 3
#define UNIX_FLAVOUR_OSX 4

//Check the platform we're running on
#if defined( __WIN32__ ) || defined( WIN32 ) || defined( _WIN32 )
#  define PLATFORM PLATFORM_WIN32
#elif defined( __APPLE_CC__ )
#  define PLATFORM PLATFORM_APPLE
#else
#  define PLATFORM PLATFORM_UNIX
#endif

//Include the correct copy of stdint.h (windows doesn't have this by default).
#if PLATFORM == PLATFORM_WIN32
#include "./compat/pstdint.h"
#else
#include <stdint.h>
#include <sys/time.h>
#endif

//Compilier definitions
#define COMPILER_MICROSOFT 0
#define COMPILER_GNU	   1
#define COMPILER_BORLAND   2

//Check compilier
#ifdef _MSC_VER
#  define COMPILER COMPILER_MICROSOFT
#elif defined( __BORLANDC__ )
#  define COMPILER COMPILER_BORLAND
#elif defined( __GNUC__ )
#  define COMPILER COMPILER_GNU
#else
#  define COMPILER
#endif

//Integer types woohoo!
#if COMPILER != COMPILER_GNU
typedef signed __int64 int64;
typedef signed __int32 int32;
typedef signed __int16 int16;
typedef signed __int8 int8;

typedef unsigned __int64 uint64;
typedef unsigned __int32 uint32;
typedef unsigned __int16 uint16;
typedef unsigned __int8 uint8;
#else
//For ease.
typedef int64_t int64;
typedef int32_t int32;
typedef int16_t int16;
typedef int8_t int8;
typedef uint64_t uint64;
typedef uint32_t uint32;
typedef uint16_t uint16;
typedef uint8_t uint8;
#endif

#if (defined(__APPLE__) && defined(__MACH__))
#define HAVE_DARWIN
#endif

#if PLATFORM == PLATFORM_UNIX || PLATFORM == PLATFORM_APPLE
#ifdef HAVE_DARWIN
#define PLATFORM_TEXT "MacOSX"
#define UNIX_FLAVOUR UNIX_FLAVOUR_OSX
#else
#ifdef USE_KQUEUE
#define PLATFORM_TEXT "FreeBSD"
#define UNIX_FLAVOUR UNIX_FLAVOUR_BSD
#else
#define PLATFORM_TEXT "Linux"
#define UNIX_FLAVOUR UNIX_FLAVOUR_LINUX
#endif
#endif
#endif
#if PLATFORM == PLATFORM_WIN32
#define PLATFORM_TEXT "Win32"
#endif

#include <cstdlib>
#include <cstdio>
#include <set>
#include <list>
#include <string>
#include <map>
#include <queue>
#include <sstream>
#include <algorithm>
#include <climits>
#include <cstdlib>
#include <cctype>
#include <ctime>
#include <cstdarg>

using std::string;

#ifdef WIN32
#define FORCEINLINE __forceinline
#else
#define FORCEINLINE inline
#endif
#define INLINE inline

#if PLATFORM == PLATFORM_WIN32
#define EXPORT __declspec(dllexport)
#define IMPORT __declspec(dllimport)
#else
#define EXPORT __attribute__((visibility("default")))
#define IMPORT
#endif

//Architecture for int conversions, or anything else i need
#ifdef X64
#define ARCH "X64"
#else
#define ARCH "X86"
#endif

//Why does windows have to do things "their" way.
#if PLATFORM == PLATFORM_WIN32
#define STRCASECMP stricmp
#else
#define STRCASECMP strcasecmp
#endif

#if PLATFORM == PLATFORM_WIN32
#define sleep(a) Sleep(a * 1000)
#else
#include <unistd.h>
#endif

#if COMPILER == COMPILER_MICROSOFT

#define I64FMT "%016I64X"
#define I64FMTD "%I64u"
#define SI64FMTD "%I64d"
#define snprintf _snprintf
#define atoll __atoi64

#else

#define I64FMT "%016llX"
#define I64FMTD "%llu"
#define SI64FMTD "%lld"

#endif

#define atol(a) strtoul( a, NULL, 10)

#define STRINGIZE(a) #a

// fix buggy MSVC's for variable scoping to be reliable. Cause #Microsoft.
#define for if(true) for

#include <cassert>
#include "threading/Threading.h"

#include "threading/AtomicULong.hpp"
#include "threading/AtomicFloat.hpp"
#include "threading/AtomicCounter.hpp"
#include "threading/AtomicBoolean.hpp"

#include "ConditionVariable.hpp"

#include "Array.hpp"

//Note past here is a bunch of helper functions seemingly unrealted from Threading.
namespace MTLib {

	//Let's be precise for int conversion hmmm?
#if COMPILER == COMPILER_MICROSOFT && _MSC_VER >= 1400
#pragma float_control(push)
#pragma float_control(precise, on)
#endif

	//Fast INT ABS
	EXPORT FORCEINLINE int int32abs(const int value) {
		return (value ^ (value >> 31)) - (value >> 31);
	}

	// fast int abs and recast to unsigned
	EXPORT FORCEINLINE uint32 int32abs2uint32(const int value) {
		return (uint32)(value ^ (value >> 31)) - (value >> 31);
	}

	/// Fastest Method of float2int32
	EXPORT FORCEINLINE int float2int32(const float value) {
#if !defined(X64) && COMPILER == COMPILER_MICROSOFT && !defined(USING_BIG_ENDIAN)
		int i;
		__asm
		{
			fld value
				frndint
				fistp i
		}
		return i;
#else
		union { int asInt[2]; double asDouble; } n;
		n.asDouble = value + 6755399441055744.0;

		return n.asInt[0];
#endif
	}

	/// Fastest Method of long2int32
	EXPORT FORCEINLINE int long2int32(const double value) {
#if !defined(X64) && COMPILER == COMPILER_MICROSOFT && !defined(USING_BIG_ENDIAN)
		int i;
		__asm
		{
			fld value
				frndint
				fistp i
		}
		return i;
#else
		union { int asInt[2]; double asDouble; } n;
		n.asDouble = value + 6755399441055744.0;

		return n.asInt[0];
#endif
	}

#if COMPILER == COMPILER_MICROSOFT && _MSC_VER >= 1400
#pragma float_control(pop) //Okay thats good.
#endif

	//Reversing an entire array fastly.
	EXPORT FORCEINLINE void reverse_array(uint8* pointer, size_t count) {
		size_t x;
		uint8* temp = (uint8*)malloc(count);
		memcpy(temp, pointer, count);
		for (x = 0; x < count; ++x)
			pointer[x] = temp[count - x - 1];
		free(temp);
	}

	//tolower on a string is now much easier!
	EXPORT FORCEINLINE void TOLOWER(std::string & str) {
		for (size_t i = 0; i < str.length(); ++i)
			str[i] = (char)tolower(str[i]);
	}

	//toupper on a string is now much easier too!
	EXPORT FORCEINLINE void TOUPPER(std::string & str) {
		for (size_t i = 0; i < str.length(); ++i)
			str[i] = (char)toupper(str[i]);
	}

	EXPORT FORCEINLINE uint32 now() {
#ifdef WIN32
		return GetTickCount();
#else
		struct timeval tv;
		gettimeofday(&tv, NULL);
		return (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
#endif
	}
}

#endif
