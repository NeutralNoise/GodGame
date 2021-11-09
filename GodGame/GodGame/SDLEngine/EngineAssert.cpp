#include "EngineAssert.h"
#include <stdio.h>
#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif

	void assert_fail(const char * expr, const char * file, const char * func, const int & line)
	{
		//TODO allow this to output to a file.
		//NOTE should this display a window with the assert message?
		fprintf(stderr, "Assertion failed: %s (%s: %s: %d)\n", expr, file, func, line);
		abort();
	}

/*

*/
#ifdef __cplusplus
}
#endif
