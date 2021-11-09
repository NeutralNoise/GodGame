#ifndef ENGINE_ASSERT_H_INCLUDED
#define ENGINE_ASSERT_H_INCLUDED
#include "CommonDefines.h"
/*
#ifdef NDEBUG
#define	assert(x) (void)0
#else
#define assert(x) ((void)((x) || (__assert_fail(#x, __FILE__, __LINE__, __func__),0)))
#endif
*/

#ifdef NDEBUG
#define	LG_ASSERT(x) (void)0
#else
//#define LG_ASSERT(x) ((void)((x) || (__assert_fail(#x, __FILE__, __LINE__, __func__),0)))
#define LG_ASSERT(x) if(!x) assert_fail(#x, __FILE__, __FUNCTION_NAME__, __LINE__)
#endif

#ifdef __cplusplus
extern "C" {
#endif

	[[noreturn]] void assert_fail(const char * expr, const char * file, const char * func, const int &line);

#ifdef __cplusplus
}
#endif


#endif // !ENGINE_ASSERT_H_INCLUDED
