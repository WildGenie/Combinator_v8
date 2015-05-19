// *****************************************************************************
//
// $Id$
//
// 
//
// *****************************************************************************
//
//     Copyright (c) 2003, Pleora Technologies Inc., All rights reserved.
//
// *****************************************************************************
//
// File Name....: CyTypes.h
//
// Description..: General data types and constants definition
//
// *****************************************************************************
//
// $Log$
//
// *****************************************************************************

#ifndef _CY_TYPES_H_
#define _CY_TYPES_H_

// Compiler options
/////////////////////////////////////////////////////////////////////////////

#ifdef WIN32
#pragma warning ( disable : 4786 )
#pragma warning ( disable : 4290 )
#pragma warning ( disable : 4251 )
#pragma warning ( disable : 4200 )
#pragma warning ( disable : 4201 )
#endif // WIN32

// Header Files
/////////////////////////////////////////////////////////////////////////////

#include "CyUtilsLib.h"


// SDK version
/////////////////////////////////////////////////////////////////////////////

#define COYOTE_SDK_VERSION  ( 0220 )    // MMmm ( major minor )


// Macros
/////////////////////////////////////////////////////////////////////////////

#if ( defined( _WIN32 ) || defined( __BORLANDC__) || defined( UNDER_CE ) ) && !defined( WIN32 )
#define WIN32
#endif // ( defined( _WIN32 ) || defined( __BORLANDC__) || defined( UNDER_CE ) ) && !defined( WIN32 )

#if defined( _WIN64 ) && ! defined( WIN64 )
#define WIN64
#endif // defined( _WIN64 ) && ! defined( WIN64 )

#if defined( DEBUG ) && !defined( _DEBUG )
#define _DEBUG
#endif // defined( DEBUG) && !defined( _DEBUG )

#ifdef WIN32
#define CY_CALLING_CONV __cdecl
#endif // WIN32

#ifdef _UNIX_
#define CY_CALLING_CONV
#endif

#ifdef UNDER_CE
#define CE_VERSION UNDER_CE
#endif // UNDER_CE

#ifdef WIN32

#ifdef __BORLANDC__

#define CY_INLINE         inline
#define CY_FORCE_INLINE   inline

#else


#ifdef _MSC_VER

#define CY_INLINE         __forceinline
#define CY_FORCE_INLINE   __forceinline

#else

#define CY_INLINE         inline
#define CY_FORCE_INLINE   inline

#endif

#endif

#endif

#ifdef _UNIX_
#define CY_INLINE         inline
#define CY_FORCE_INLINE   inline
#endif


// Data types
/////////////////////////////////////////////////////////////////////////////

// This SDK's main result code type.
typedef unsigned long CyResult;

// Defines system handles, mostly for drivers and synchronization objects.
#ifdef _UNIX_
    typedef int CySysHandle;
    #define INVALID_HANDLE (-1)
#else // _UNIX_
    typedef void* CySysHandle;
    #define INVALID_HANDLE (NULL)
#endif // _UNIX_

#ifndef WIN32
	#define __int64 long long
	#define _atoi64( a ) strtoll( a, NULL, 10 )
	#define _I64_MAX ( 9223372036854775807LL )
	#define _I64_MIN ( -_I64_MAX - 1LL )
#endif // WIN32

// The error information structure.  Can be obtained from objects
// that are derived from the error interface.
struct CyErrorInfo
{
	char          mMessage[ 256 ];
	CyResult      mResult;
	char          mSourceFile[ 256 ];
	unsigned long mSourceLine;
	unsigned long mSystemCode;

#if !defined( _BORLANDC_ ) && defined( __cplusplus ) && !defined ( _DRIVER_ )
    // Constructor for convenience
    CY_UTILS_LIB_API CyErrorInfo( );
    CY_UTILS_LIB_API CyErrorInfo( const char*    aMessage,
                                  CyResult       aResult,
                                  const char*    aSourceFile,
                                  unsigned long  aSourceLine,
                                  unsigned long  aSystemCode );
#endif // !defined( _BORLANDC_ ) && defined( __cplusplus ) && !defined ( _DRIVER_ )
};

CY_UTILS_LIB_C_API struct CyErrorInfo* CyErrorInfo_Init  ( struct CyErrorInfo* aInfo );
CY_UTILS_LIB_C_API struct CyErrorInfo* CyErrorInfo_InitEx( struct CyErrorInfo* aInfo,
                                                           const char*         aMessage,
                                                           CyResult            aResult,
                                                           const char*         aSourceFile,
                                                           unsigned long       aSourceLine,
                                                           unsigned long       aSystemCode );

// Functions
/////////////////////////////////////////////////////////////////////////////

#ifndef _DRIVER_
CY_UTILS_LIB_C_API const char* CoyoteStatusMessage( CyResult aResult );
#endif


// Constants
/////////////////////////////////////////////////////////////////////////////

// Possible values for CyResult
#define CY_RESULT_OK                     (0)
#define CY_RESULT_ABORTED                (1)
#define CY_RESULT_ARGUMENT_TOO_LONG      (2)
#define CY_RESULT_BAD_ADDRESS            (3)
#define CY_RESULT_BUFFER_TOO_SMALL       (4)
#define CY_RESULT_CANNOT_CREATE_EVENT    (5)
#define CY_RESULT_CANNOT_OPEN_FILE       (6)
#define CY_RESULT_CANNOT_SET_EVENT       (7)
#define CY_RESULT_CONSTRUCTOR_FAILED     (8)
#define CY_RESULT_CORRUPTED_FILE	     (9)
#define CY_RESULT_D3D_ERROR              (10)
#define CY_RESULT_DD_ERROR               (11)
#define CY_RESULT_DEVICE_ERROR			 (12)
#define CY_RESULT_DEVICE_RESET           (13)
#define CY_RESULT_DRIVER_ERROR			 (14)
#define CY_RESULT_EMPTY_SEQUENCE         (15)
#define CY_RESULT_FILE_ERROR             (16)
#define CY_RESULT_INTERNAL_ERROR         (17)
#define CY_RESULT_INVALID_ARGUMENT       (18)
#define CY_RESULT_NETWORK_ERROR          (19)
#define CY_RESULT_NO_AVAILABLE_DATA      (20)
#define CY_RESULT_NO_MORE_ITEM           (21)
#define CY_RESULT_NO_SELECTED_ITEM       (22)
#define CY_RESULT_NOT_CONNECTED		     (23)
#define CY_RESULT_NOT_ENOUGH_MEMORY      (24)
#define CY_RESULT_NOT_FOUND              (25)
#define CY_RESULT_NOT_SUPPORTED          (26)
#define CY_RESULT_OVERFLOW               (27)
#define CY_RESULT_STATE_ERROR            (28)
#define CY_RESULT_THREAD_ERROR           (29)
#define CY_RESULT_TIMEOUT		         (30)
#define CY_RESULT_UNDERFLOW              (31)
#define CY_RESULT_UNEXPECTED_ERROR       (32)
#define CY_RESULT_UNEXPECTED_EXCEPTION   (33)
#define CY_RESULT_UNKNOWN_ERROR          (34)
#define CY_RESULT_UNSUPPORTED_CONVERSION (35)
#define CY_RESULT_OPERATION_PENDING      (36)
#define CY_RESULT_IMAGE_ERROR            (37)
#define CY_RESULT_CORRUPTED_IMAGE        (38)
#define CY_RESULT_MISSING_PACKETS        (39)
#define CY_RESULT_NETWORK_LINK_DOWN      (40)

#define CY_RESULT_MAX                    (41)


// Returns the Location of the software
/////////////////////////////////////////////////////////////////////////////

#ifndef _DRIVER_
CY_UTILS_LIB_C_API CyResult CoyoteSoftwareLocation( char* aLocation, unsigned long aSize );
CY_UTILS_LIB_C_API CyResult CoyoteBinariesLocation( char* aLocation, unsigned long aSize );
#endif


// Include important headers for convenience
/////////////////////////////////////////////////////////////////////////////

#if defined( __cplusplus ) && !defined( _DRIVER_ )

    #include "CyString.h"
    #include "CyObject.h"

#endif // defined( __cplusplus ) && !defined( _DRIVER_ )

#endif // _CY_TYPES_H_
