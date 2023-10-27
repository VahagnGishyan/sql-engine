
//////////////////////////////////////////////////////////////////////////
//                                                                      //
//////////////////////////////////////////////////////////////////////////

#pragma once

//////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////

#define IS_WINDOWS defined(_WIN32) || defined(WIN32) || defined(_WIN64) || defined(WIN64) || defined(__WIN32__) || defined(__TOS_WIN__) || defined(__WINDOWS__) || defined(_WINDOWS) || defined(_WIN32_WINCE)
#define IS_LINUX defined(__linux) || defined(__linux__) || defined(linux)
#define IS_MACOS __APPLE__

#if IS_WINDOWS
#if defined(UTILITY_SHARE)
#define PROJECT_SHARED_EXPORT __declspec(dllexport)
#else
#define PROJECT_SHARED_EXPORT __declspec(dllimport)
#endif
#define PROJECT_SHARED_CCA __cdecl
#elif IS_LINUX
#if __GNUC__ >= 4
#define PROJECT_SHARED_EXPORT __attribute__((visibility("default")))
#else
#define PROJECT_SHARED_EXPORT
#endif
#define PROJECT_SHARED_CCA
#elif IS_MACOS
#define PROJECT_SHARED_EXPORT __attribute__((visibility("default")))
#define PROJECT_SHARED_CCA
#else
#define PROJECT_SHARED_EXPORT
#define PROJECT_SHARED_CCA __attribute__((cdecl))
#endif

//////////////////////////////////////////////////////////////////////////
//                                                                      //
//////////////////////////////////////////////////////////////////////////

namespace SQLEngine::Utility
{
}

//////////////////////////////////////////////////////////////////////////
//                                                                      //
//////////////////////////////////////////////////////////////////////////
