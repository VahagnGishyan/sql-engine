
//////////////////////////////////////////////////////////////////////////
//                                                                      //
//////////////////////////////////////////////////////////////////////////

#pragma once

//////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////

#if defined UTILITY_BUILD
#define SHARE_LIB
#endif

//////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////

#if defined(_WIN32) || defined(WIN32) || defined(_WIN64) || defined(WIN64) || \
    defined(__WIN32__) || defined(__TOS_WIN__) || defined(__WINDOWS__) ||     \
    defined(_WINDOWS) || defined(_WIN32_WINCE)
#define IS_WINDOWS
#elif defined(__linux) || defined(__linux__) || defined(linux)
#define IS_LINUX
#elif __APPLE__
#define IS_MACOS
#else
#error "Unsupported OS"
#endif

#if defined IS_WINDOWS
#if defined(SHARE_LIB)
#define PROJECT_SHARED_EXPORT __declspec(dllexport)
#else
#define PROJECT_SHARED_EXPORT __declspec(dllimport)
#endif
#define PROJECT_SHARED_CCA __cdecl
#elif defined IS_LINUX
#if __GNUC__ >= 4
#define PROJECT_SHARED_EXPORT __attribute__((visibility("default")))
#else
#define PROJECT_SHARED_EXPORT
#endif
#define PROJECT_SHARED_CCA
#elif defined IS_MACOS
#define PROJECT_SHARED_EXPORT __attribute__((visibility("default")))
#define PROJECT_SHARED_CCA
#else
#define PROJECT_SHARED_EXPORT
#define PROJECT_SHARED_CCA __attribute__((cdecl))
#endif

//////////////////////////////////////////////////////////////////////////
//                                                                      //
//////////////////////////////////////////////////////////////////////////
