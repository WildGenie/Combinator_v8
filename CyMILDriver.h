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
// File Name....: CyMILDriver.h
//
// *****************************************************************************
//
// $Log$
//
// *****************************************************************************

#ifndef _CY_MIL_DRIVER_H_
#define _CY_MIL_DRIVER_H_

// Includes
/////////////////////////////////////////////////////////////////////////////

#include <mil.h>


// DLL declaration
/////////////////////////////////////////////////////////////////////////////

#ifdef _LINUX_

#define CY_MIL_DRIVER_API

#endif // _LINUX_

#ifdef WIN32

#ifdef CY_MIL_DRIVER_EXPORTS
#define CY_MIL_DRIVER_API __declspec(dllexport)
#else // CY_MIL_DRIVER_EXPORTS
#define CY_MIL_DRIVER_API __declspec(dllimport)
#endif // CY_MIL_DRIVER_EXPORTS

#endif // WIN32


/* C++ directive if needed */
#ifdef __cplusplus
extern "C"
{
#endif

// Prototypes - Creations
/////////////////////////////////////////////////////////////////////////////

MFTYPE32 MDIGHOOKFCTPTR CY_MIL_DRIVER_API MFTYPE
    CyMdigHookFunction      ( MIL_ID            DigitizerId,
                              long              HookType,
                              MDIGHOOKFCTPTR    HandlerPtr,
                              void MPTYPE *     UserPtr );
                                                
MFTYPE32 CY_MIL_DRIVER_API MIL_ID MFTYPE
    CyMdigAlloc             ( MIL_ID            SystemId,
                              long              DeviceNum,
                              MIL_TEXT_PTR      DataFormat,
                              long              InitFlag,
                              MIL_ID MPTYPE *   IdVarPtr );

MFTYPE32 CY_MIL_DRIVER_API void MFTYPE
    CyMdigFree             ( MIL_ID             DevId );



// Prototypes - Control
/////////////////////////////////////////////////////////////////////////////

MFTYPE32 CY_MIL_DRIVER_API void MFTYPE
    CyMdigChannel           ( MIL_ID            DevId,
                              long              Channel );

MFTYPE32 CY_MIL_DRIVER_API void MFTYPE
    CyMdigReference         ( MIL_ID            DevId,
                              long              ReferenceType,
                              long              ReferenceLevel );

MFTYPE32 CY_MIL_DRIVER_API void MFTYPE
    CyMdigLut               ( MIL_ID            DevId,
                              MIL_ID            LutBufId );

MFTYPE32 CY_MIL_DRIVER_API void MFTYPE
    CyMdigHalt              ( MIL_ID            DevId );

MFTYPE32 CY_MIL_DRIVER_API long MFTYPE
    CyMdigInquire           ( MIL_ID            DevId,
                              long              InquireType,
                              void MPTYPE *     ResultPtr );

MFTYPE32 CY_MIL_DRIVER_API void MFTYPE
    CyMdigControl           ( MIL_ID            DigitizerId,
                              long              ControlType,
                              double            Value );

MFTYPE32 CY_MIL_DRIVER_API void MFTYPE
    CyMdigGrabWait          ( MIL_ID            DevId,
                              long              Flag );



// Prototypes - Access
/////////////////////////////////////////////////////////////////////////////

MFTYPE32 CY_MIL_DRIVER_API void MFTYPE
    CyMdigGrab              ( MIL_ID            SrcDevId,
                              MIL_ID            DestImageId );

MFTYPE32 CY_MIL_DRIVER_API void MFTYPE 
    CyMdigGrabContinuous    ( MIL_ID            SrcDevId,
                              MIL_ID            DestImageId );

MFTYPE32 CY_MIL_DRIVER_API void MFTYPE
    CyMdigAverage           ( MIL_ID            Digitizer,
                              MIL_ID            DestImageId,
                              long              WeightFactor,
                              long              AverageType,
                              long              NbIteration );

MFTYPE32 CY_MIL_DRIVER_API void MFTYPE
    CyMdigFocus             ( MIL_ID            DigId,
                              MIL_ID            DestImageId,
                              MIL_ID            FocusImageRegionId,
                              MFOCUSHOOKFCTPTR  FocusHookPtr,
                              void MPTYPE *     UserDataPtr,
                              long              MinPosition, 
                              long              StartPosition, 
                              long              MaxPosition,
                              long              MaxPositionVariation,
                              long              ProcMode,
                              long *            ResultPtr );


// Prototypes - Pleora Specific
/////////////////////////////////////////////////////////////////////////////

MFTYPE32 CY_MIL_DRIVER_API void* // really a CyCameraInterface*
    CyMdigGetCamera( MIL_ID DigId );

MFTYPE32 CY_MIL_DRIVER_API void
    CyMdigSetBufferCount( unsigned long BufferCount );

MFTYPE32 CY_MIL_DRIVER_API unsigned long
    CyMdigGetBufferCount( );


/* C++ directive if needed */
#ifdef __cplusplus
}
#endif


// Macros to automatically use the CyMdig... functions
/////////////////////////////////////////////////////////////////////////////

#ifndef CY_MIL_DRIVER_NO_FUNCTION_REPLACE

#define MdigHookFunction    CyMdigHookFunction
#define MdigAlloc           CyMdigAlloc
#define MdigFree            CyMdigFree
#define MdigChannel         CyMdigChannel
#define MdigReference       CyMdigReference
#define MdigLut             CyMdigLut
#define MdigHalt            CyMdigHalt
#define MdigInquire         CyMdigInquire
#define MdigControl         CyMdigControl
#define MdigGrabWait        CyMdigGrabWait
#define MdigGrab            CyMdigGrab
#define MdigGrabContinuous  CyMdigGrabContinuous
#define MdigAverage         CyMdigAverage
#define MdigFocus           CyMdigFocus

#endif // CY_MIL_DRIVER_NO_FUNCTION_REPLACE


// Automatic Library Linking
/////////////////////////////////////////////////////////////////////////////

// force the inclusing of the CyMILDriver(_Dbg).lib file
#ifndef CY_MIL_DRIVER_EXPORTS
#pragma comment(lib,"CyMILDriver.lib")
#pragma message( "Linking with CyMILDriver.lib" )
#endif

#endif // _CY_MIL_DRIVER_H_


