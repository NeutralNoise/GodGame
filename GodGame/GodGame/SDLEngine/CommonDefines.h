#ifndef COMMMON_DEFINES_H_INCLUDED
#define COMMMON_DEFINES_H_INCLUDED

#define USE_ERROR_MANAGER //Use the built in error manager

//Build Information
#if defined(_WIN32) || defined(_WIN64)
#define WIN_BUILD
#if defined(_WIN64)
#define WIN64_BUILD
#else
#define WIN32_BUILD
#endif
#elif __linux__
#define LIN_BUILD
#if defined(__LP64__ ) || defined(_LP64)
#define LIN64_BUILD
#else
#define LIN32_BUILD
#endif
//Treat cygwin builds likes its on linux
//have some cygwin ones just incase its needed for things like dll/so
#elif __CYGWIN__
#define LIN_BUILD
#define CYG_BUILD
#if defined(__LP64__ ) || defined(_LP64)
#define LIN64_BUILD
#define CYG64_BUILD
#else
#define LIN32_BUILD
#define CYG32_BUILD
#endif
#endif

//Function name
#if defined(WIN_BUILD)
#ifndef __FUNCTION_NAME__
#define __FUNCTION_NAME__   __FUNCTION__  
#endif //!__FUNCTION_NAME__
#elif defined(LIN_BUILD)
#ifndef __FUNCTION_NAME__
#define __FUNCTION_NAME__   __func__
#endif //!__FUNCTION_NAME__
#endif

// DLL/SO loading
//This is so we export the symbols for functions. This is only needed on windows platforms.
#ifdef WIN_BUILD
#define LOADABLELIB_API __declspec(dllexport)
#elif defined(LIN_BUILD)
#define LOADABLELIB_API
#endif

#endif //COMMMON_DEFINES_H_INCLUDED
