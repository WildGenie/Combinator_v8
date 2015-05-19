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
// File Name....: CySemaphore.h
//
// Description..: Base synchronization object.
//
// *****************************************************************************
//
// $Log$
//
// *****************************************************************************

#ifndef _CY_SEMAPHORE_H_
#define _CY_SEMAPHORE_H_

// Includes
/////////////////////////////////////////////////////////////////////////////

#ifdef _UNIX_
//#include <semaphore.h>
#include <pthread.h>
#endif // _UNIX_

#include "CySynchro.h"
#include "CyUtilsLib.h"
#include "CyTypes.h"
#include "CyString.h"

// Class
/////////////////////////////////////////////////////////////////////////////

#ifdef __cplusplus
struct CySemaphoreInternal;
class CySemaphore : public CySynchro
{
// Constructors / Destructor
public:

    // Create an unnamed semaphore
	CY_UTILS_LIB_API CySemaphore( unsigned long aInitialCount,
                                  unsigned long aMaximumCount );

#ifdef WIN32
    // Create a named semaphore
    CY_UTILS_LIB_API CySemaphore( const CyString& aName,
                                  unsigned long      aInitialCount,
                                  unsigned long      aMaximumCount );

#ifndef UNDER_CE
    // Create an semaphore that already exists under name
	CY_UTILS_LIB_API CySemaphore( const CyString& aName );
#endif // UNDER_CE

#endif // WIN32

	CY_UTILS_LIB_API virtual ~CySemaphore( void );

// Methods
public:

    CY_UTILS_LIB_API virtual CyResult Release ( unsigned long aCount = 1 );

    // ===== CySynchro =====

#ifdef _UNIX_
    CY_UTILS_LIB_API virtual CyResult WaitUntilSignaled( void );
    CY_UTILS_LIB_API virtual CyResult WaitUntilSignaled( unsigned long aTime );
#endif // _UNIX_

// Data
private:
    struct CySemaphoreInternal* mInternal;
   
private:
    CySemaphore( const CySemaphore& );
    CySemaphore& operator=( const CySemaphore& );
};
#endif // __cplusplus

// Standard C Wrapper
/////////////////////////////////////////////////////////////////////////////

// CySemaphore Handle
typedef void* CySemaphoreH;

// Note the CySynchro functions can be used with this type


#ifdef WIN32

// Construction - Destruction
CY_UTILS_LIB_C_API CySemaphoreH CySemaphore_Init( const char *  aName,
                                                  unsigned long aInitialCount,
                                                  unsigned long aMaximumCount );
#ifndef UNDER_CE
CY_UTILS_LIB_C_API CySemaphoreH CySemaphore_Open( const char *  aName );
#endif // UNDER_CE
CY_UTILS_LIB_C_API void         CySemaphore_Destroy( CySemaphoreH aHandle );

// Semaphore functions
CY_UTILS_LIB_C_API CyResult     CySemaphore_Release( CySemaphoreH  aHandle,
                                                     unsigned long aCount );

#endif // WIN32

#endif // _CY_SEMAPHORE_H_
