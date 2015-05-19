// *****************************************************************************
//
// $Id$
//
// cy1h02b1
//
// *****************************************************************************
//
//     Copyright (c) 2003, Pleora Technologies Inc., All rights reserved.
//
// *****************************************************************************
//
// File Name....: CySharedMemory.h
//
// Description..: Contains information that is place by the driver/udp link when
//                data is being received
//
// *****************************************************************************
//
// $Log$
//
// *****************************************************************************

#ifndef __CY_SHARED_MEMORY_H__
#define __CY_SHARED_MEMORY_H__

// Include
/////////////////////////////////////////////////////////////////////////////

// ===== CyUtilsLib =====
#include <CyTypes.h>
#include <CyObject.h>

// ===== This project =====
#include "CyComLib.h"
#include "CyBuffer.h"


// Forward declaration
/////////////////////////////////////////////////////////////////////////////

#ifdef __cplusplus
struct DriverSharedMemory;
#endif // __cplusplus


// class
/////////////////////////////////////////////////////////////////////////////

#ifdef __cplusplus
class CySharedMemory : public CyObject
{
// Construction / Destruction
public:
    CY_COM_LIB_API CySharedMemory();
    CY_COM_LIB_API ~CySharedMemory();

// Accessors
    // returns the internal DriverSharedMemory object.  Used internally by the SDK
    CY_COM_LIB_API DriverSharedMemory& GetSharedMemory() const;
    CY_COM_LIB_API operator DriverSharedMemory* () const;

    // Reset the shared memory
    CY_COM_LIB_API void Reset();

    // Returns the status of the operation.
    CY_COM_LIB_API CyResult GetStatus() const;

    // Returns the status of the frame.  Available only when the buffer has been
    // received completely, which is out of the scope of this class
#ifndef _QNX_
    CY_COM_LIB_API CyBuffer::ImageStatus GetImageStatus() const;
#else
    CY_COM_LIB_API unsigned long GetImageStatus() const;
#endif

    // Returns the time stamp of the frame.  Also only applies to a
    // completely received frame
    CY_COM_LIB_API unsigned long GetTimestamp() const;

    // Returns the ID of the frame and the sub-channel it comes from, if applicable.
    // Also only applies to a completely received frame
    CY_COM_LIB_API unsigned long GetImageID() const;
    CY_COM_LIB_API unsigned char GetSubChannelID() const;

    // Returns the current of the image, may be update by the driver
    CY_COM_LIB_API unsigned long GetSize() const;

    // Returns acquisition information 
    CY_COM_LIB_API unsigned long GetExpectedResendCount() const;
    CY_COM_LIB_API unsigned long GetIgnoredPacketCount() const;
    CY_COM_LIB_API unsigned long GetLostPacketCount() const;
    CY_COM_LIB_API unsigned long GetResendRequestCount() const;
    CY_COM_LIB_API unsigned long GetStartPacketCount() const;
    CY_COM_LIB_API unsigned long GetUnexpectedResendCount() const;

private:
    DriverSharedMemory* mSharedMemory;
};
#endif // __cplusplus


// Standard C Wrapper
/////////////////////////////////////////////////////////////////////////////

// CySharedMemory Handle
typedef void* CySharedMemoryH;

// Construction / Destruction
CY_COM_LIB_C_API CySharedMemoryH CySharedMemory_Init();
CY_COM_LIB_C_API void            CySharedMemory_Destroy( CySharedMemoryH aHandle );

// Reset the shared memory
CY_COM_LIB_C_API void          CySharedMemory_Reset( CySharedMemoryH aHandle );

// Accessors
CY_COM_LIB_C_API unsigned long CySharedMemory_GetStatus( CySharedMemoryH aHandle );
CY_COM_LIB_C_API unsigned long CySharedMemory_GetImageStatus( CySharedMemoryH aHandle );
CY_COM_LIB_C_API unsigned long CySharedMemory_GetTimestamp( CySharedMemoryH aHandle );
CY_COM_LIB_C_API unsigned long CySharedMemory_GetImageID( CySharedMemoryH aHandle );
CY_COM_LIB_C_API unsigned long CySharedMemory_GetSubChannelID( CySharedMemoryH aHandle );
CY_COM_LIB_C_API unsigned long CySharedMemory_GetSize( CySharedMemoryH aHandle );
CY_COM_LIB_C_API unsigned long CySharedMemory_GetExpectedResendCount( CySharedMemoryH aHandle );
CY_COM_LIB_C_API unsigned long CySharedMemory_GetIgnoredPacketCount( CySharedMemoryH aHandle );
CY_COM_LIB_C_API unsigned long CySharedMemory_GetLostPacketCount( CySharedMemoryH aHandle );
CY_COM_LIB_C_API unsigned long CySharedMemory_GetResendRequestCount( CySharedMemoryH aHandle );
CY_COM_LIB_C_API unsigned long CySharedMemory_GetStartPacketCount( CySharedMemoryH aHandle );
CY_COM_LIB_C_API unsigned long CySharedMemory_GetUnexpectedResendCount( CySharedMemoryH aHandle );

#endif // __CY_SHARED_MEMORY_H__

