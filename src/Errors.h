#ifndef ERRORS_H
#define ERRORS_H

#include "PrintStackTrace.h"
#include "log/Log.hpp"
//TODO: Handle errors better

#if CODE_ANALYSIS
#include<codeanalysis\sourceannotations.h>
#define ANALYSIS_ASSUME( EXPR ) __analysis_assume( EXPR )
#else
#define ANALYSIS_ASSUME( EXPR )
#endif

// An assert isn't necessarily fatal, but we want to stop anyways
#define WPAssert( EXPR ) if (!(EXPR)) { ((void(*)())0)(); } ANALYSIS_ASSUME( EXPR )

#define WPError( assertion, errmsg ) if( ! (assertion) ) { Log::getSingleton( ).outError( "%s:%i ERROR:\n  %s\n", __FILE__, __LINE__, (char *)errmsg ); assert( false ); }
#define WPWarning( assertion, errmsg ) if( ! (assertion) ) { Log::getSingleton( ).outError( "%s:%i WARNING:\n  %s\n", __FILE__, __LINE__, (char *)errmsg ); }

// This should always halt everything.  If you ever find yourself wanting to remove the assert( false ), switch to WPWarning or WPError
#define WPFatal( assertion, errmsg ) if( ! (assertion) ) { Log::getSingleton( ).outError( "%s:%i FATAL ERROR:\n  %s\n", __FILE__, __LINE__, (char *)errmsg ); assert( #assertion &&0 ); abort(); }

#define ASSERT WPAssert

#endif
