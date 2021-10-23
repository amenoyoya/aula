#pragma once

/*** プラットフォーム設定マクロ ***/

// WindowsOS
#if defined(_MSC_VER) || defined(WIN32) || defined(_WIN32_)
#define _WINDOWS
#pragma warning(disable: 4005)
#endif

// LinuxOS
#ifdef _linux_
#define _LINUX
#endif

// MacOS
#ifdef _APPLE_
#define _APPLE
#endif

// AndroidOS
#ifdef ANDROID_NDK
#define _ANDROID
#endif


// デスクトップ環境
#if defined(_WINDOWS) || defined(_LINUX) || defined(_APPLE)
#define _DESKTOP_APP
#endif

// スマートフォン環境
#ifdef _ANDROID
#define _SMARTPHONE_APP
#endif

// OS固有API
#ifdef _WINDOWS
    #define UNICODE
    #define STRICT
    #define _CRT_SECURE_NO_WARNINGS
    #include <windows.h>
#else
    #include <unistd.h>
#endif


// dllexport / dllimport
#if defined(_MSC_VER)
    #define __export __declspec(dllexport)
    #define __import __declspec(dllimport)
#else
    #define __export
    #define __import
#endif


/*** 整数型定義 ***/
typedef char               i8;
typedef unsigned char      u8;
typedef short              i16;
typedef unsigned short     u16;
typedef long               i32;
typedef unsigned long      u32;
typedef long long          i64;
typedef unsigned long long u64;
