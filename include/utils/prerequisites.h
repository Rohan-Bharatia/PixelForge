#pragma region LICENSE

//                    GNU GENERAL PUBLIC LICENSE
//                       Version 3, 29 June 2007
// 
// Copyright (C) 2007 Free Software Foundation, Inc. <https://fsf.org/>
// Everyone is permitted to copy and distribute verbatim copies
// of this license document, but changing it is not allowed.
// 
//                                   ...
// 
//                    Copyright (C) Rohan Bharatia 2024

#pragma endregion LICENSE

#pragma once

#ifndef _PF_UTILS_PRERQUISITES_h_
#define _PF_UTILS_PRERQUISITES_h_

#if defined(__clang__)

#define PF_COMPILER_CLANG
#define PF_COMPILER_CLANG_VER (__clang_major__ * 100 + __clang_minor__)
#define PF_DEPRECATED(txt) __attribute__((__deprecated__(txt)))
#define PF_PRETTY_FUNCTION __PRETTY_FUNCTION__

#define PF_CHECK_CLANG_VER(ver) (PF_COMPILER_CLANG_VER >= ver)
	
#define PF_PRAGMA(x) _Pragma(#x)

#define PF_WARNING_CLANG_DISABLE(warn) PF_PRAGMA(clang diagnostic ignored warn)
#define PF_WARNING_CLANG_GCC_DISABLE(warn) PF_PRAGMA(clang diagnostic ignored warn)
#define PF_WARNING_POP() PF_PRAGMA(clang diagnostic pop)
#define PF_WARNING_PUSH() PF_PRAGMA(clang diagnostic push)

#ifdef __MINGW32__

	#define PF_COMPILER_MINGW

	#ifdef __MINGW64_VERSION_MAJOR

		#define PF_COMPILER_MINGW_W64

	#endif // __MINGW64_VERSION_MAJOR

#endif // __MINGW32__

#elif defined(__GNUC__) || defined(__MINGW32__)

#define PF_COMPILER_GCC
#define PF_COMPILER_GCC_VER (__GNUC__ * 100 + __GNUC_MINOR__)
#define PF_DEPRECATED(txt) __attribute__((__deprecated__(txt)))
#define PF_PRETTY_FUNCTION __PRETTY_FUNCTION__

#define PF_CHECK_GCC_VER(ver) (PF_COMPILER_GCC_VER >= ver)

#define PF_PRAGMA(x) _Pragma(#x)

#define PF_WARNING_CLANG_GCC_DISABLE(warn) PF_PRAGMA(GCC diagnostic ignored warn)
#define PF_WARNING_GCC_DISABLE(warn) PF_PRAGMA(GCC diagnostic ignored warn)
#define PF_WARNING_POP() PF_PRAGMA(GCC diagnostic pop)
#define PF_WARNING_PUSH() PF_PRAGMA(GCC diagnostic push)

#ifdef __MINGW32__

	#define PF_COMPILER_MINGW

	#ifdef __MINGW64_VERSION_MAJOR

		#define PF_COMPILER_MINGW_W64

	#endif // __MINGW64_VERSION_MAJOR

#endif // __MINGW32__

#elif defined(__INTEL_COMPILER) || defined(__ICL)

#define PF_COMPILER_ICC
#define PF_COMPILER_ICC_VER __INTEL_COMPILER
#define PF_DEPRECATED(txt) [[deprecated(txt)]]
#define PF_PRETTY_FUNCTION __FUNCTION__
	
#define PF_CHECK_ICC_VER(ver) (PF_COMPILER_ICC_VER >= ver)

#define PF_PRAGMA(x) _Pragma(x)

#define PF_WARNING_ICC_DISABLE(...) PF_PRAGMA(warning(disable: __VA_ARGS__))
#define PF_WARNING_POP() PF_PRAGMA(warning(pop))
#define PF_WARNING_PUSH() PF_PRAGMA(warning(push))

#elif defined(_MSC_VER)

#define PF_COMPILER_MSVC
#define PF_COMPILER_MSVC_VER _MSC_VER
#define PF_DEPRECATED(txt) __declspec(deprecated(txt))
#define PF_PRETTY_FUNCTION __FUNCSIG__

#define PF_CHECK_MSVC_VER(ver) (PF_COMPILER_MSVC_VER >= ver)

#define PF_PRAGMA(x) __pragma(x)

#define PF_WARNING_MSVC_DISABLE(...) PF_PRAGMA(warning(disable: __VA_ARGS__))
#define PF_WARNING_POP() PF_PRAGMA(warning(pop))
#define PF_WARNING_PUSH() PF_PRAGMA(warning(push))

#define PF_CPP_VER _MSVC_LANG

#else // (NOT) defined(__clang__), defined(__GNUC__) || defined(__MINGW32__), defined(__INTEL_COMPILER) || defined(__ICL), defined(_MSC_VER)

#define PF_COMPILER_UNKNOWN
#define PF_DEPRECATED(txt)
#define PF_PRETTY_FUNCTION __func__

#error PixelForge does not support this compiler! Supported compilers: {clang, GCC, ICC, and MSVC}

#endif // defined(__clang__)

#ifdef PF_COMPILER_MINGW

	#if defined(__USING_MCFGTHREAD__)

		#define PF_COMPILER_MINGW_THREADS_MCF

	#elif defined(_REENTRANT)

		#define PF_COMPILER_MINGW_THREADS_POSIX

	#else // (NOT) defined(__USING_MCFGTHREAD__)

		#define PF_COMPILER_MINGW_THREADS_WIN32

	#endif // defined(__USING_MCFGTHREAD__)

#endif // PF_COMPILER_MINGW

#ifndef PF_CHECK_CLANG_VER
#define PF_CHECK_CLANG_VER(ver) 0
#endif // PF_CHECK_CLANG_VER

#ifndef PF_CHECK_ICC_VER
#define PF_CHECK_ICC_VER(ver) 0
#endif // PF_CHECK_ICC_VER

#ifndef PF_CHECK_GCC_VER
#define PF_CHECK_GCC_VER(ver) 0
#endif // PF_CHECK_GCC_VER

#ifndef PF_CHECK_MSVC_VER
#define PF_CHECK_MSVC_VER(ver) 0
#endif // PF_CHECK_MSVC_VER

#ifndef PF_CPP_VER
#define PF_CPP_VER __cplusplus
#endif // PF_CPP_VER

#ifndef PF_PRAGMA
#define PF_PRAGMA(x) _Pragma(#x)
#endif // PF_PRAGMA

#ifndef PF_WARNING_CLANG_DISABLE
#define PF_WARNING_CLANG_DISABLE(warn)
#endif // PF_WARNING_CLANG_DISABLE

#ifndef PF_WARNING_CLANG_GCC_DISABLE
#define PF_WARNING_CLANG_GCC_DISABLE(warn)
#endif // PF_WARNING_CLANG_GCC_DISABLE

#ifndef PF_WARNING_GCC_DISABLE
#define PF_WARNING_GCC_DISABLE(warn)
#endif // PF_WARNING_GCC_DISABLE

#ifndef PF_WARNING_ICC_DISABLE
#define PF_WARNING_ICC_DISABLE(warn)
#endif // PF_WARNING_ICC_DISABLE

#ifndef PF_WARNING_MSVC_DISABLE
#define PF_WARNING_MSVC_DISABLE(...)
#endif // PF_WARNING_MSVC_DISABLE

#ifndef PF_WARNING_POP
#define PF_WARNING_POP()
#endif // PF_WARNING_POP

#ifndef PF_WARNING_PUSH
#define PF_WARNING_PUSH()
#endif // PF_WARNING_PUSH

#define PF_CPP98 199711L
#define PF_CPP11 201103L
#define PF_CPP14 201402L
#define PF_CPP17 201703L
#define PF_CPP20 202002L
#define PF_CPP23 202302L

#define PF_CHECK_CPP_VER(ver) (PF_CPP_VER >= ver)

#if !PF_CHECK_CPP_VER(PF_CPP17)

#error PixelForge requires C++17 or higher!

#endif // !PF_CHECK_CPP_VER(PF_CPP17)

#if defined(_WIN32)

#define PF_PLATFORM_DESKTOP
#define PF_PLATFORM_WINDOWS

#define PF_EXPORT __declspec(dllexport)
#define PF_IMPORT __declspec(dllimport)

	#if defined(PF_BUILD)
		#ifndef WIN32_LEAN_AND_MEAN
		#define WIN32_LEAN_AND_MEAN
		#endif // WIN32_LEAN_AND_MEAN

		#ifndef NOMINMAX
		#define NOMINMAX
		#endif // NOMINMAX

		#if PF_UTILS_WINDOWS_NT6

			#define PF_WINNT 0x0600

		#else // (NOT) PF_UTILS_WINDOWS_NT6

			#define PF_WINNT 0x0501
			
		#endif // PF_UTILS_WINDOWS_NT6

		#if defined(_WIN32_WINNT)

			#if _WIN32_WINNT < PF_WINNT

				#undef _WIN32_WINNT
				#define _WIN32_WINNT PF_WINNT

			#endif // _WIN32_WINNT < PF_WINNT

		#else // (NOT) defined(_WIN32_WINNT)

			#define _WIN32_WINNT PF_WINNT

		#endif // defined(_WIN32_WINNT)
	#endif // defined(PF_BUILD)

#elif defined(__ANDROID__)

#if !__has_include(<android/ndk-version.h>)

	#error PixelForge requires a more recent Android NDK version, please update!

#endif // !__has_include(<android/ndk-version.h>)

#include <android/ndk-version.h>

#define PF_PLATFORM_MOBILE
#define PF_PLATFORM_ANDROID
#define PF_PLATFORM_POSIX

#define PF_PLATFORM_ANDROID_NDK_VER __NDK_MAJOR__
#define PF_CHECK_NDK_VER(ver) (PF_PLATFORM_ANDROID_NDK_VER >= ver)

#define PF_EXPORT __attribute__((visibility("default")))
#define PF_IMPORT __attribute__((visibility("default")))

#elif defined(__linux__)

#define PF_PLATFORM_DESKTOP
#define PF_PLATFORM_LINUX
#define PF_PLATFORM_POSIX

#define PF_EXPORT __attribute__((visibility("default")))
#define PF_IMPORT __attribute__((visibility("default")))

#elif defined(__FreeBSD__)

#define PF_PLATFORM_BSD
#define PF_PLATFORM_FREEBSD
#define PF_PLATFORM_POSIX

#define PF_EXPORT __attribute__((visibility("default")))
#define PF_IMPORT __attribute__((visibility("default")))

#elif defined(__APPLE__)

#include <TargetConditionals.h>

#if TARGET_OS_IPHONE

	#define PF_PLATFORM_MOBILE
	#define PF_PLATFORM_IOS

#else // (NOT) TARGET_OS_IPHONE

	#define PF_PLATFORM_DESKTOP
	#define PF_PLATFORM_MACOS

#endif // TARGET_OS_IPHONE

#define PF_PLATFORM_BSD
#define PF_PLATFORM_POSIX

#define PF_EXPORT __attribute__((visibility("default")))
#define PF_IMPORT __attribute__((visibility("default")))

#elif defined(__EMSCRIPTEN__)

#define PF_PLATFORM_WEB
#define PF_PLATFORM_POSIX

#define PF_EXPORT __attribute__((visibility("default")))
#define PF_IMPORT __attribute__((visibility("default")))

#else // (NOT) defined(_WIN32), defined(__ANDROID__), defined(__linux__), defined(__FreeBDS__), defined(__APPLE__), defined(__EMSCRIPTEN__)

#error PixelForge does not support this OS! Supported OS's: {Windows, Android, Linux, FreeBDS, MacOS, IOS, and EMSCRIPTEN (web)}

#define PF_PLATFORM_UNKNOWN
#define PF_EXPORT
#define PF_IMPORT

#endif // defined(_WIN32)

#ifndef PF_CHECK_NDK_VER
#define PF_CHECK_NDK_VER(ver) 0
#endif // PF_CHECK_NDK_VER

#ifdef __has_cpp_attribute

#define PF_HAS_CPP_ATTRIBUTE(attr) __has_cpp_attribute(attr)

#else // (NOT) __has_cpp_attribute

#define PF_HAS_CPP_ATTRIBUTE(attr) (0)

#endif // __has_cpp_attribute

#ifndef PF_NO_ASSUME_ATTRIBUTE

#if PF_CHECK_CPP_VER(PF_CPP23) || PF_HAS_CPP_ATTRIBUTE(assume)

#define PF_ASSUME(expr) [[assume(expr)]]

#endif // PF_CHECK_CPP_VER(PF_CPP23) || PF_HAS_CPP_ATTRIBUTE(assume)

#ifndef PF_ASSUME

#if defined(PF_COMPILER_CLANG)

#define PF_ASSUME(expr) __builtin_assume(expr)

#endif // defined(PF_COMPILER_CLANG)

#if defined(PF_COMPILER_GCC)

#if __GNUC__ >= 13

#define PF_ASSUME(expr) __attribute__(assume(expr))

#endif // __GNUC__ >= 13

#endif // defined(PF_COMPILER_GCC)

#if defined(PF_COMPILER_MSVC)

#define PF_ASSUME(expr) __assume(expr)

#endif // defined(PF_COMPILER_MSVC)

#endif // PF_ASSUME

#endif // PF_NO_ASSUME_ATTRIBUTE

#ifndef PF_NO_FORCEINLINE_ATTRIBUTE

#ifndef PF_FORCEINLINE

#if defined(PF_COMPILER_CLANG) || defined(PF_COMPILER_GCC)

#define PF_FORCEINLINE __attribute__((always_inline)) inline

#endif // defined(PF_COMPILER_CLANG) || defined(PF_COMPILER_GCC)

#if defined(PF_COMPILER_MSVC)

#define PF_FORCEINLINE __forceinline

#endif // defined(PF_COMPILER_MSVC)

#endif // PF_FORCEINLINE

#endif // PF_NO_FORCEINLINE_ATTRIBUTE

#ifndef PF_NO_LIKELY_ATTRIBUTE

#if PF_CHECK_CPP_VER(PF_CPP20) || PF_HAS_CPP_ATTRIBUTE(likely)

#define PF_LIKELY(expr) (expr) [[likely]]

#endif // PF_CHECK_CPP_VER(PF_CPP20) || PF_HAS_CPP_ATTRIBUTE(likely)

#if PF_CHECK_CPP_VER(PF_CPP20) || PF_HAS_CPP_ATTRIBUTE(unlikely)

#define PF_UNLIKELY(expr) (expr) [[unlikely]]

#endif // PF_CHECK_CPP_VER(PF_CPP20) || PF_HAS_CPP_ATTRIBUTE(unlikely)

#if defined(PF_COMPILER_CLANG) || defined(PF_COMPILER_GCC) || defined(PF_COMPILER_INTEL)

#ifndef PF_LIKELY

#define PF_LIKELY(expr) (__builtin_expect(!!(expr), 1))

#endif // PF_LIKELY

#ifndef PF_UNLIKELY

#define PF_UNLIKELY(expr) (__builtin_expect(!!(expr), 0))

#endif // PF_UNLIKELY

#endif // defined(PF_COMPILER_CLANG) || defined(PF_COMPILER_GCC) || defined(PF_COMPILER_INTEL)

#endif // PF_NO_LIKELY_ATTRIBUTE

#ifndef PF_NO_UNREACHABLE_MACRO

#if defined(PF_COMPILER_CLANG) || defined(PF_COMPILER_GCC) || defined(PF_COMPILER_INTEL)

#define PF_UNREACHABLE() __builtin_unreachable()

#elif defined(PF_COMPILER_MSVC)

#define PF_UNREACHABLE() __assume(false)

#endif // defined(PF_COMPILER_CLANG) || defined(PF_COMPILER_GCC) || defined(PF_COMPILER_INTEL)

#endif // PF_NO_UNREACHABLE_MACRO

#ifndef PF_ASSUME
#define PF_ASSUME(expr)
#endif // PF_ASSUME

#ifndef PF_FORCEINLINE
#define PF_FORCEINLINE inline
#endif // PF_FORCEINLINE

#ifndef PF_LIKELY
#define PF_LIKELY(expr) (expr)
#endif // PF_LIKELY

#ifndef PF_UNLIKELY
#define PF_UNLIKELY(expr) (expr)
#endif // PF_UNLIKELY

#ifndef PF_UNREACHABLE
#define PF_UNREACHABLE() throw pf::UnreachableError{};
#endif // PF_UNREACHABLE

#ifndef PF_NO_ARCH_DETECTION

#if defined(__arm__) || defined(__thumb__) || defined(__ARM_ARCH_7__) || defined(_M_ARM)

#define PF_ARCH_arm

#endif // defined(__arm__) || defined(__thumb__) || defined(__ARM_ARCH_7__) || defined(_M_ARM)

#if defined(__aarch64__) || defined(_M_ARM64) || defined(_M_ARM64EC) || defined(__arm64__)

#define PF_ARCH_aarch64 // defined(__aarch64__) || defined(_M_ARM64) || defined(_M_ARM64EC) || defined(__arm64__)

#endif // defined(__aarch64__) || defined(_M_ARM64) || defined(_M_ARM64EC) || defined(__arm64__)

#if defined(__amd64__) || defined(__amd64) || defined(__x86_64__) || defined(__x86_64) || defined(_M_AMD64) || defined (_M_X64)

#define PF_ARCH_x86_64

#endif // defined(__amd64__) || defined(__amd64) || defined(__x86_64__) || defined(__x86_64) || defined(_M_AMD64) || defined (_M_X64)

#if defined(__i386__) || defined(_M_IX86) || defined(_X86_)

#define PF_ARCH_x86

#endif // defined(__i386__) || defined(_M_IX86) || defined(_X86_)

#if defined(__wasm32__)

#define PF_ARCH_wasm32

#endif // defined(__wasm32__)

#if defined(__wasm64__)

#define PF_ARCH_wasm64

#endif // defined(__wasm64__)

#if defined(PF_ARCH_arm) + defined(PF_ARCH_aarch64) + defined(PF_ARCH_x86_64)  + defined(PF_ARCH_x86) + defined(PF_ARCH_wasm32) + defined(PF_ARCH_wasm64) != 1

#error PixelForge does not support this CPU architecture! Supported CPU architectures: {arm, aarch64, x86-64, x86, wasm32, and wasm64} 

#endif // defined(PF_ARCH_arm) + defined(PF_ARCH_aarch64) + defined(PF_ARCH_x86_64)  + defined(PF_ARCH_x86) + defined(PF_ARCH_wasm32) + defined(PF_ARCH_wasm64) != 1

#endif // PF_NO_ARCH_DETECTION

#ifdef PF_UNITY_ID

	#define PF_ANONYMOUS_NAMESPACE PF_UNITY_ID
	#define PF_USE_ANONYMOUS_NAMESPACE using namespace PF_UNITY_ID;
	#define PF_ANONYMOUS_NAMESPACE_PREFIX(a) PF_UNITY_ID::a

#else // (NOT) PF_UNITY_ID

	#define PF_ANONYMOUS_NAMESPACE
	#define PF_USE_ANONYMOUS_NAMESPACE
	#define PF_ANONYMOUS_NAMESPACE_PREFIX(a) a

#endif // PF_UNITY_ID

#define pf_prefix(a, prefix) prefix ## a
#define pf_prefix_macro(a, prefix) pf_prefix(a, prefix)
#define pf_suffix(a, suffix) a ## suffix
#define pf_suffix_macro(a, suffix) pf_suffix(a, suffix)
#define pf_stringify(s) #s
#define pf_stringify_macro(s) pf_stringify(s)
#define pf_unused(a) (void) a

#include <climits>
#include <cstdint>

static_assert(CHAR_BIT == 8, "CHAR_BIT is expected to be 8!");

static_assert(sizeof(int8_t)  == 1, "int8_t is not of the correct size!");
static_assert(sizeof(int16_t) == 2, "int16_t is not of the correct size!");
static_assert(sizeof(int32_t) == 4, "int32_t is not of the correct size!");
static_assert(sizeof(int64_t) == 8, "int64_t is not of the correct size!");

static_assert(sizeof(uint8_t)  == 1, "uint8_t is not of the correct size!");
static_assert(sizeof(uint16_t) == 2, "uint16_t is not of the correct size!");
static_assert(sizeof(uint32_t) == 4, "uint32_t is not of the correct size!");
static_assert(sizeof(uint64_t) == 8, "uint64_t is not of the correct size!");

namespace pf
{
	using uint = unsigned int;

	using int8 = int8_t;
	using uint8 = uint8_t;

	using int16 = int16_t;
	using uint16 = uint16_t;

	using int32 = int32_t;
	using uint32 = uint32_t;

	using int64 = int64_t;
	using uint64 = uint64_t;

	struct UnreachableError {};
} // namespace pf

#endif // _PF_UTILS_PRERQUISITES_h_