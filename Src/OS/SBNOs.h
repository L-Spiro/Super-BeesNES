/**
 * Copyright L. Spiro 2022
 *
 * Written by: Shawn (L. Spiro) Wilcoxen
 *
 * Description: Includes all OS headers.
 */

#pragma once

#if defined( _WIN32 ) || defined( _WIN64 )
#include "SBNWindows.h"
#elif defined( __APPLE__ )
#include "SBNApple.h"
#else
#endif  // #if defined( _WIN32 ) || defined( _WIN64 )

#ifndef SBN_FASTCALL
#define SBN_FASTCALL
#endif	// SBN_FASTCALL


#if defined( _MSC_VER )
    // Microsoft Visual Studio Compiler
    #define SBN_ALIGN( n ) 						__declspec( align( n ) )
#elif defined( __GNUC__ ) || defined( __clang__ )
    // GNU Compiler Collection (GCC) or Clang
    #define SBN_ALIGN( n ) 						__attribute__( (aligned( n )) )
#else
    #error "Unsupported compiler"
#endif


#if defined( _MSC_VER )
	#define SBN_FORCEINLINE 					__forceinline
	#define SBN_PREFETCH_LINE( ADDR )			_mm_prefetch( reinterpret_cast<const char *>(ADDR), _MM_HINT_T0 );
#elif defined( __GNUC__ )
	#define SBN_FORCEINLINE 					__inline__ __attribute__( (__always_inline__) )
	#define SBN_PREFETCH_LINE( ADDR )			__builtin_prefetch( reinterpret_cast<const void *>(ADDR), 1, 1 );
#else
	#define SBN_FORCEINLINE inline
#endif
