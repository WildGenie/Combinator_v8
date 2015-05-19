// *****************************************************************************
//
//     Copyright (c) 2003-2005, Pleora Technologies Inc., All rights reserved.
//
// *****************************************************************************
//
// File Name....: CyBuffer.h
//
// Description..: Multi-thread buffer implementation. Support queuing of write 
//                requests.
//
// *****************************************************************************

#ifndef _CY_BUFFER_H_
#define _CY_BUFFER_H_

// Includes
/////////////////////////////////////////////////////////////////////////////

#include "CyResultEvent.h"
#include "CyTypes.h"
#include "CyGate.h"
#include "CyEvent.h"
#include "CyComLib.h"
#include "CyMemoryManager.h"
#include "CyPerfMonitor.h"
#include "CyBufferConstants.h"


// Forward
/////////////////////////////////////////////////////////////////////////////

#ifdef __cplusplus
class FrameBuffer;
class CyMemoryManager;
struct CyBufferInternal;
#endif // __cplusplus

struct DriverSharedMemory;


// Class
/////////////////////////////////////////////////////////////////////////////

/* ==========================================================================
@since	2002-09-03
========================================================================== */
#ifdef __cplusplus
class CyBuffer : public CyErrorInterface
{

// Data types
public:
    typedef union
    {
        unsigned long mValue;

        struct
        {
            unsigned mFrameOverrun          : 1;
            unsigned mGrabberFIFOOverrun    : 1;
            unsigned mImageDropped          : 1;
            unsigned mPartialLineMissing    : 1;
            unsigned mFullLineMissing       : 1;
            unsigned mReserved0             : 3;
            unsigned mInterlaced            : 1;
            unsigned mFirstGrabbedField     : 1;
            unsigned mFieldFirstLine        : 1;
            unsigned mReserved1             : 3;
            unsigned mHorizontalUnlocked    : 1;
            unsigned mVerticalUnlocked      : 1;
            unsigned mEOFByLineCount        : 1;
            unsigned mReserved2             : 15;

        };
    } ImageStatus;

    // Buffer lock ID
    typedef void* WriteLockID;
    typedef void* ReadLockID;

// Constants
public:

    // ----- LockForRead -----
	CY_COM_LIB_API static const unsigned long FLAG_ERROR_IF_EMPTY;
    CY_COM_LIB_API static const unsigned long FLAG_NO_WAIT;
    CY_COM_LIB_API static const unsigned long FLAG_NO_DOUBLE_BUFFER;
    CY_COM_LIB_API static const unsigned long FLAG_MASK;


// Constructors / Destructor
public:

	CY_COM_LIB_API CyBuffer( unsigned long aCapacity );

	CY_COM_LIB_API virtual ~CyBuffer( void );

private:

    // Disabled
	CyBuffer( const CyBuffer & );
	const CyBuffer &operator=( const CyBuffer & );

// Accessors
public:
    // Buffer Capacity
    CY_COM_LIB_API virtual unsigned long GetCapacity() const;
    CY_COM_LIB_API virtual CyResult      SetCapacity( unsigned long aCapacity );

    // Read locked buffer access
    CY_COM_LIB_API virtual unsigned long GetReadImageStatus() const;
    CY_COM_LIB_API virtual unsigned char GetReadSubChannelID() const;
    CY_COM_LIB_API virtual unsigned long GetReadTimestamp() const;
    CY_COM_LIB_API virtual unsigned long GetReadSize() const;
    CY_COM_LIB_API virtual unsigned long GetReadImageID() const;
    CY_COM_LIB_API virtual unsigned long GetReadExpectedResendCount() const;
    CY_COM_LIB_API virtual unsigned long GetReadIgnoredPacketCount() const;
    CY_COM_LIB_API virtual unsigned long GetReadLostPacketCount() const;
    CY_COM_LIB_API virtual unsigned long GetReadResendRequestCount() const;
    CY_COM_LIB_API virtual unsigned long GetReadStartPacketCount() const;
    CY_COM_LIB_API virtual unsigned long GetReadUnexpectedResendCount() const;

    CY_COM_LIB_API virtual unsigned long GetReadImageStatus( ReadLockID aID ) const;
    CY_COM_LIB_API virtual unsigned char GetReadSubChannelID( ReadLockID aID ) const;
    CY_COM_LIB_API virtual unsigned long GetReadTimestamp( ReadLockID aID ) const;
    CY_COM_LIB_API virtual unsigned long GetReadSize( ReadLockID aID ) const;
    CY_COM_LIB_API virtual unsigned long GetReadImageID( ReadLockID aID ) const;
    CY_COM_LIB_API virtual unsigned long GetReadExpectedResendCount( ReadLockID aID ) const;
    CY_COM_LIB_API virtual unsigned long GetReadIgnoredPacketCount( ReadLockID aID ) const;
    CY_COM_LIB_API virtual unsigned long GetReadLostPacketCount( ReadLockID aID ) const;
    CY_COM_LIB_API virtual unsigned long GetReadResendRequestCount( ReadLockID aID ) const;
    CY_COM_LIB_API virtual unsigned long GetReadStartPacketCount( ReadLockID aID ) const;
    CY_COM_LIB_API virtual unsigned long GetReadUnexpectedResendCount( ReadLockID aID ) const;

    // Write locked buffer access
    CY_COM_LIB_API virtual unsigned long GetWriteSize   ( WriteLockID aID ) const;
    CY_COM_LIB_API virtual void          SetWriteSize   ( WriteLockID aID, unsigned long aSize );
    CY_COM_LIB_API virtual unsigned long GetWriteImageID( WriteLockID aID ) const;

    // change the memory manager for the buffer.
    // Will clean all the current buffers.

    CY_COM_LIB_API virtual CyResult      SetMemoryManager( CyMemoryManager& aMemoryManager );
    CY_COM_LIB_API virtual CyResult      ResetMemoryManager();
    CY_COM_LIB_API virtual const CyMemoryManager&
                                         GetMemoryManager() const;


    // Changes the size of the acquired buffer queue.
    CY_COM_LIB_API virtual CyResult      SetQueueSize( unsigned long aSize );
    CY_COM_LIB_API virtual unsigned long GetQueueSize() const;
    CY_COM_LIB_API virtual unsigned long GetQueueItemCount() const;
    CY_COM_LIB_API virtual void          ClearQueue();

    // Change the mode of the queue.
    //  aDropNewFramesWhenFull
    //      false: when a new frame is available and the queue is full, the first item in the
    //            queue is removed and the new item is added at the end of the queue.
    //
    //      true: when a new frame is available and the queue is full, this new frame is dropped.
    //

    CY_COM_LIB_API virtual void          SetQueueMode( bool aDropNewFramesWhenFull );
    CY_COM_LIB_API virtual bool          GetQueueMode() const;

// Methods
public:

	// ===== Synchro =====

	CY_COM_LIB_API virtual CyResult LockForRead(  void **        aPtr,
                                                  unsigned long* aSize,
                                                  unsigned long  aFlags = FLAG_NO_WAIT );
	CY_COM_LIB_API virtual CyResult LockForRead(  void **        aPtr,
                                                  unsigned long* aSize,
                                                  ReadLockID*    aID,
                                                  unsigned long  aFlags );

	CY_COM_LIB_API virtual CyResult LockForWrite( void **          aPtr,
                                                  CyResultEvent ** aEvent,
                                                  WriteLockID*     aID,
                                                  unsigned long    aFlags = 0,
                                                  CyPerfMonitor *  aPerfMonitor = NULL );

	CY_COM_LIB_API virtual void SignalReadEnd ( void );
    CY_COM_LIB_API virtual void SignalReadEnd ( ReadLockID aID );
    CY_COM_LIB_API virtual void SignalWriteEnd( WriteLockID aID );

	// ===== Undocumented =====

    CY_COM_LIB_API virtual void AbortRead( void );
	CY_COM_LIB_API virtual void AbortWrite( void );
	CY_COM_LIB_API virtual void Wait( void );
    CY_COM_LIB_API virtual DriverSharedMemory* GetSharedMemory( WriteLockID aID ) const;

private:

    void         AbortThread( unsigned int aWP );
    FrameBuffer *AllocateFrameBuffer( void );
	void         Free( void );
    void         FreeNoLock();
    void         FreeFrameBuffer( FrameBuffer *aBuffer );
    CyResult     LockForRead( unsigned long aFlags );
    FrameBuffer *LockForWrite( unsigned long aFlags, CyPerfMonitor *aPerfMonitor );
    CyResult     OnUnexpectedException( void );
    void         ResumeThread( unsigned int aWP, CyResult aResult );
    CyResult     SuspendThread( unsigned int aWP );
	CyResult     WaitForWriteEnd( void );

// Data
private:
    struct CyBufferInternal* mInternal;
};
#endif // __cplusplus


// Standard C Wrapper
/////////////////////////////////////////////////////////////////////////////

// CyBuffer Handle
typedef void* CyBufferH;

// Construction - Destruction
CY_COM_LIB_C_API CyBufferH CyBuffer_Init   ( unsigned long aCapacity );
CY_COM_LIB_C_API void      CyBuffer_Destroy( CyBufferH     aHandle );

// Access to the buffer's capacity
CY_COM_LIB_C_API unsigned long CyBuffer_GetCapacity( CyBufferH aHandle );
CY_COM_LIB_C_API CyResult      CyBuffer_SetCapacity( CyBufferH     aHandle,
                                                     unsigned long aCapacity );

// Read-locked buffer accessors
CY_COM_LIB_C_API unsigned long CyBuffer_GetReadImageStatus          ( CyBufferH     aHandle,
                                                                      void*         aReadID );
CY_COM_LIB_C_API unsigned long CyBuffer_GetReadSubChannelID         ( CyBufferH     aHandle,
                                                                      void*         aReadID );
CY_COM_LIB_C_API unsigned long CyBuffer_GetReadTimestamp            ( CyBufferH     aHandle,
                                                                      void*         aReadID );
CY_COM_LIB_C_API unsigned long CyBuffer_GetReadSize                 ( CyBufferH     aHandle,
                                                                      void*         aReadID );
CY_COM_LIB_C_API unsigned long CyBuffer_GetReadImageID              ( CyBufferH     aHandle,
                                                                      void*         aReadID );
CY_COM_LIB_C_API unsigned long CyBuffer_GetReadExpectedResendCount  ( CyBufferH     aHandle,
                                                                      void*         aReadID );
CY_COM_LIB_C_API unsigned long CyBuffer_GetReadIgnoredPacketCount   ( CyBufferH     aHandle,
                                                                      void*         aReadID );
CY_COM_LIB_C_API unsigned long CyBuffer_GetReadLostPacketCount      ( CyBufferH     aHandle,
                                                                      void*         aReadID );
CY_COM_LIB_C_API unsigned long CyBuffer_GetReadResendRequestCount   ( CyBufferH     aHandle,
                                                                      void*         aReadID );
CY_COM_LIB_C_API unsigned long CyBuffer_GetReadStartPacketCount     ( CyBufferH     aHandle,
                                                                      void*         aReadID );
CY_COM_LIB_C_API unsigned long CyBuffer_GetReadUnexpectedResendCount( CyBufferH     aHandle,
                                                                      void*         aReadID );

// Write-locked buffer accessors
CY_COM_LIB_C_API unsigned long CyBuffer_GetWriteSize   ( CyBufferH     aHandle,
                                                         void*         aWriteID );
CY_COM_LIB_C_API void          CyBuffer_SetWriteSize   ( CyBufferH     aHandle,
                                                         void*         aWriteID,
                                                         unsigned long aSize );
CY_COM_LIB_C_API unsigned long CyBuffer_GetWriteImageID( CyBufferH     aHandle,
                                                         void*         aWriteID );

// Memory Manager functions
CY_COM_LIB_C_API CyResult         CyBuffer_SetMemoryManager  ( CyBufferH        aHandle,
                                                               CyMemoryManagerH aMemoryManager );
CY_COM_LIB_C_API CyResult         CyBuffer_ResetMemoryManager( CyBufferH        aHandle );
CY_COM_LIB_C_API CyMemoryManagerH CyBuffer_GetMemoryManager  ( CyBufferH        aHandle );

// Control the available read buffer queue
CY_COM_LIB_C_API CyResult      CyBuffer_SetQueueSize     ( CyBufferH     aHandle,
                                                           unsigned long aSize );
CY_COM_LIB_C_API unsigned long CyBuffer_GetQueueSize     ( CyBufferH     aHandle );
CY_COM_LIB_C_API unsigned long CyBuffer_GetQueueItemCount( CyBufferH     aHandle );
CY_COM_LIB_C_API void          CyBuffer_ClearQueue       ( CyBufferH     aHandle );
CY_COM_LIB_C_API void          CyBuffer_SetQueueMode     ( CyBufferH     aHandle,
                                                           int aDropNewFramesWhenFull );
CY_COM_LIB_C_API int           CyBuffer_GetQueueMode     ( CyBufferH     aHandle );

// Locking for reading
CY_COM_LIB_C_API CyResult CyBuffer_LockForRead  ( CyBufferH      aHandle,
                                                  void **        aPtr,
                                                  unsigned long* aSize,
                                                  void**         aReadID,
                                                  unsigned long  aFlags );
CY_COM_LIB_C_API void     CyBuffer_SignalReadEnd( CyBufferH      aHandle,
                                                  void*          aReadID );
CY_COM_LIB_C_API void     CyBuffer_AbortRead    ( CyBufferH      aHandle );

// Locking for writing
CY_COM_LIB_C_API CyResult CyBuffer_LockForWrite  ( CyBufferH       aHandle,
                                                   void **         aPtr,
                                                   CyResultEventH* aEvent,
                                                   void**          aWriteID,
                                                   unsigned long   aFlags,
                                                   CyPerfMonitorH  aPerfMonitor );
CY_COM_LIB_C_API void     CyBuffer_SignalWriteEnd( CyBufferH       aHandle,
                                                   void*           aWriteID );
CY_COM_LIB_C_API void     CyBuffer_AbortWrite    ( CyBufferH       aHandle );

// Accessors to the buffer's shared memory object
CY_COM_LIB_C_API struct DriverSharedMemory* CyBuffer_GetSharedMemory( CyBufferH     aHandle,
                                                                      unsigned long aWriteID );

#endif // _CY_BUFFER_H_
