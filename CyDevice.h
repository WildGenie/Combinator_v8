// *****************************************************************************
//
// $Id$
//
// cy1h02b1
//
// *****************************************************************************
//
//     Copyright (c) 2002-2003, Pleora Technologies Inc., All rights reserved.
//
// *****************************************************************************
//
// File Name....: CyDevice.h
//
// Description..: CyComLib main class. It manage all device configuration and
//                communication.
//
// *****************************************************************************
//
// $Log$
//
// *****************************************************************************

#ifndef _CY_DEVICE_H_
#define _CY_DEVICE_H_

// Includes
/////////////////////////////////////////////////////////////////////////////

// ===== CyUtilsLib =====
#include <CyTypes.h>
#include <CyPersistentRepository.h>
#include <CyResultEvent.h>
#include <CyAssert.h>

// ===== This project =====
#include "CyComLib.h"
#include "CyConfig.h"
#include "CyChannel.h"
#include "CyAdapterID.h"
#include "CyDeviceConstants.h"
#include "CyDeviceExtension.h"
#include "CyDeviceExtensionConstants.h"


// Forward declarations
/////////////////////////////////////////////////////////////////////////////

// ===== CyDrvLib =====
#ifdef __cplusplus
class  DataReceiverSetting;
#endif
struct DriverSharedMemory;


// Types
/////////////////////////////////////////////////////////////////////////////

// interrupt status hen Callback2 is invoked
union CyInterruptStatus
{
    unsigned long mValue;

    struct
    {
        unsigned    mReserved0      : 1;
        unsigned    mFIFOFull       : 1;
        unsigned    mFIFOOverflow   : 1;
        unsigned    mFIFOCount      : 3;
        unsigned    mReserved1      : 10;
        unsigned    mGPIOLUTInputs  : 8;
        unsigned    mInterruptID    : 4;
        unsigned    mReserved2      : 4;
    };
};

// Callback for the C functions
typedef CyResult (CY_CALLING_CONV * CyDeviceCallback ) ( void*             aContext,
                                                         unsigned long     aId );
typedef CyResult (CY_CALLING_CONV * CyDeviceCallback2 )( void *            aContext,
                                                         unsigned long     aId,
                                                         unsigned long     aTimeStamp,
                                                         union CyInterruptStatus aStatus );


// Class
/////////////////////////////////////////////////////////////////////////////

/* ==========================================================================
@class	CyDevice

@since	2002-09-03
========================================================================== */
#ifdef __cplusplus
struct CyDeviceInternal;
class CyDevice : public CyPersistentRepository
{
// Data type
public:
    typedef unsigned long CallbackId;
    typedef CyInterruptStatus InterruptStatus;
	typedef unsigned long Port;
	typedef CyDeviceCallback  Callback;
    typedef CyDeviceCallback2 Callback2;

// Constructor / Destructor
public:
	CY_COM_LIB_API CyDevice( void );
	CY_COM_LIB_API virtual ~CyDevice( void );

// Accessors
public:

	CY_COM_LIB_API bool     IsConnected( void );

    CY_COM_LIB_API const CyConfig&
                            GetConfig() const;

	CY_COM_LIB_API bool     GetChangedStatus( void );
    CY_COM_LIB_API CyResult GetId( unsigned char *aDevId,
                                   unsigned char *aModId,
                                   unsigned char *aSubId,
                                   unsigned char *aVendorId = NULL );
    CY_COM_LIB_API CyResult GetDeviceInfo( unsigned char *aDevId,
                                           unsigned char *aModId,
                                           unsigned char *aSubId,
                                           unsigned char *aVendorId,
                                           unsigned char *aMac1,
                                           unsigned char *aMac2,
                                           unsigned char *aMac3,
                                           unsigned char *aMac4,
                                           unsigned char *aMac5,
                                           unsigned char *aMac6,
                                           unsigned char *aIP1,
                                           unsigned char *aIP2,
                                           unsigned char *aIP3,
                                           unsigned char *aIP4,
                                           unsigned char *aVersionMajor,
                                           unsigned char *aVersionMinor,
                                           unsigned char *aChannelCount = 0 );

    CY_COM_LIB_API unsigned short GetNextRequestID();


// Methods
public:
	// ===== Connection =====
    CY_COM_LIB_API CyResult Connect   ( unsigned long aFlags = 0 );
	CY_COM_LIB_API CyResult Connect   ( const CyConfig& aConfig, unsigned long   aFlags = 0 );
	CY_COM_LIB_API CyResult Disconnect();


    // ===== Device Extensions =====

    // Get the number of extensions on the device
    CY_COM_LIB_API unsigned long GetExtensionCount() const;
    CY_COM_LIB_API unsigned long GetExtensionCountByType( unsigned long aTypeExtensionID ) const;


    // Returns the index of an extension
    CY_COM_LIB_API unsigned long GetExtensionIndex( unsigned long   aExtensionID ) const;

    // Indicates if an extension exist
    CY_COM_LIB_API bool HasExtensionByIndex( unsigned long   aIndex ) const;
    CY_COM_LIB_API bool HasExtension       ( unsigned long   aExtensionID ) const;

    // returns an extension
    CY_COM_LIB_API CyDeviceExtension& GetExtensionByIndex( unsigned long   aIndex ) const;
    CY_COM_LIB_API CyDeviceExtension& GetExtension       ( unsigned long   aExtensionID ) const;


	// ===== Command and answer =====

    // Indicates ths availability of ports
    CY_COM_LIB_API bool IsPortAvailable( Port aPort ) const;

    // Indicates if the port is using "interrupts" for communications
    // with the device.
    CY_COM_LIB_API bool IsPortUsingInterrupts( Port aPort ) const;

    // Configure the port, see documentation for configuration string format
    CY_COM_LIB_API CyResult ConfigPort( Port aPort, const CyString& aConfig );
    CY_COM_LIB_API CyResult GetPortConfig( Port aPort, CyString& aConfig ) const;
    CY_COM_LIB_API CyResult GetPortConfigFormat( Port aPort, CyString& aFormat ) const;


    // Sends bytes to a port of the device
	CY_COM_LIB_API CyResult SendCommand( Port aPort, const void *aSrc, unsigned int aSize, unsigned long aInfo = 0 );

    // Read bytes from the answer queue, wait if no data is available until data arrives or internal timeout
	CY_COM_LIB_API CyResult ReceiveAnswer( Port aPort, void *aDst, unsigned int *aSize, unsigned long aInfo = 0, unsigned char aTermination = 0 );

    // Flushes the content of the answer queue for a port
	CY_COM_LIB_API CyResult ResetAnswerQueue( Port aPort );

    // Returns the number of bytes available in the answer queue of the port
    CY_COM_LIB_API unsigned long GetAnswerQueueSize( Port aPort );


    // ===== Serial Port Server =====
    // When using virtual COM ports, there are two virtual COM linked ports added to
    // the system.  These functions enable the device to monitor one of these ports
    // so that an external application can connect to the other and use the device
    // serial port through a system serial port.

    CY_COM_LIB_API CyResult EnableSystemSerialPort( Port aPort, unsigned short aSystemPort, const char * aConfig = 0 );
    CY_COM_LIB_API CyResult DisableSystemSerialPort();
    CY_COM_LIB_API bool     IsSystemSerialPortEnabled() const;


	// ===== Data =====

    CY_COM_LIB_API CyResult FlushData  ( const CyChannel &aChannel );
	CY_COM_LIB_API CyResult ReceiveData( const CyChannel &aChannel,
                                         void                      * aDst,
										 unsigned int                aSize,
										 CyResultEvent             * aEvent,
                                         DriverSharedMemory        * aSharedMemory = NULL, 
										 unsigned long             * aValue   = NULL,
										 unsigned long               aFlag    = 0,
                                         const DataReceiverSetting * aSetting = NULL );
    CY_COM_LIB_API CyResult ReceiveDataToHighMemory( const CyChannel & aChannel,
                                                     unsigned long     aBufferSize,
                                                     unsigned long     aFirstBufferIndex,
                                                     unsigned long     aLastBufferIndex,
                                                     CyResultEvent   * aEvent,
                                                     CyResult        * aResult,
                                                     unsigned long   * aValue = NULL );

	CY_COM_LIB_API CyResult SendData   ( const CyChannel &aChannel, 
                                         const void      *aSrc,
                                         unsigned int     aSize );

    CY_COM_LIB_API CyResult AbortReceiveData( const CyChannel& aChannel );


	// ===== Control =====

	CY_COM_LIB_API void     RegisterCallback( CallbackId aId,  CyDeviceCallback  aFunction, void *aContext );
    CY_COM_LIB_API void     RegisterCallback2( CallbackId aId, CyDeviceCallback2 aFunction, void *aContext );
	CY_COM_LIB_API CyResult Reset( void );
	CY_COM_LIB_API CyResult ResetLink( void );
    CY_COM_LIB_API CyResult ResetModule( void );


    // ===== Save configuration to flash memory ====

    CY_COM_LIB_API bool     SupportsStaticConfiguration() const;
    CY_COM_LIB_API CyResult SaveConfiguration( bool aIP,
                                               bool aName,
                                               bool aConfig,
                                               bool aState );


	// ===== Access to device registers =====
	CY_COM_LIB_API CyResult ReadRegisters( unsigned long  aAddress,
								           unsigned long *aValue,
					                       unsigned short aCount = 1,
										   unsigned long  aFlags = 0 );

	CY_COM_LIB_API CyResult ReadRegisters( const unsigned long *aAddresses,
								           unsigned long *aValue,
					                       unsigned short aCount = 1,
										   unsigned long  aFlags = 0 );

	CY_COM_LIB_API CyResult WriteRegister( unsigned long aAddress,
                                           unsigned long aValue,
                                           unsigned long aFlags = 0 );

	CY_COM_LIB_API CyResult WriteRegisters( unsigned long  aAddress,
							                const unsigned long *aValue,
											unsigned short aCount = 1,
										    unsigned long  aFlags = 0 );

	CY_COM_LIB_API CyResult WriteRegisters( const unsigned long *aAddresses,
							                const unsigned long *aValue,
											unsigned short aCount = 1,
										    unsigned long  aFlags = 0 );

    // ===== Access to device configurations =====
    CY_COM_LIB_API CyResult ReadConfigs( unsigned short  aAddress,
								         unsigned short *aValue,
					                     unsigned short aCount = 1,
										 unsigned long  aFlags = 0 );

	CY_COM_LIB_API CyResult WriteConfig( unsigned short  aAddress,
							             unsigned short  aValue,
										 unsigned long   aFlags = 0 );

	CY_COM_LIB_API CyResult WriteConfigs( unsigned short  aAddress,
							              const unsigned short *aValue,
										  unsigned short aCount = 1,
									 	  unsigned long  aFlags = 0 );

    // ===== Undocumented =====
	CY_COM_LIB_API CyResult DeviceIoControl( unsigned long aCode,
		                                     const void *aIn,  unsigned long aInSize,
											 void       *aOut, unsigned long aOutSize );
	CY_COM_LIB_API CyResult DeviceIoControl( unsigned long   aCode,
		                                     const void    * aIn,
                                             unsigned long   aInSize,
											 void          * aOut,
                                             unsigned long   aOutSize,
                                             CyResultEvent * aEvent,
                                             CyResult      * aResult );


// Show Configuration Dialog
public:
    // Using void* to avoid windows.h dependency
    CY_COM_LIB_API CyResult ShowDialog       ( void* aParent = NULL );
public: // should be protected, but public for technical reasons
    CY_COM_LIB_API CyResult OnApply          ( void* aPropertyPage );
    CY_COM_LIB_API CyResult AddPropertyPage  ( void* aPropertySheet );

// Save/load settings from XML
public:
    CY_COM_LIB_API CyResult SaveToXML    ( CyXMLDocument& aDocument ) const;
    CY_COM_LIB_API CyResult LoadFromXML  ( CyXMLDocument& aDocument );

// protected: // The following are public, but should be treated as private
    CY_COM_LIB_API CyResult InternalSave ( CyXMLDocument& aDocument ) const;
    CY_COM_LIB_API CyResult InternalLoad ( CyXMLDocument& aDocument );

    // Locates the entry in an XML document for this device
    CY_COM_LIB_API CyResult LocateDeviceInXML( CyXMLDocument& aDocument ) const;

    // Creates the entry in an XML document for this device.  If it exists,
    // it is deleted, then recreated
    CY_COM_LIB_API CyResult CreateDeviceInXML( CyXMLDocument& aDocument ) const;


protected:
    CY_COM_LIB_API virtual CyResult OnParameterGet( unsigned long   aParameterIndex,
                                                    unsigned long   aParameterID,
                                                    const CyString& aParameterName );
    CY_COM_LIB_API virtual CyResult OnParameterSet( unsigned long   aParameterIndex,
                                                    unsigned long   aParameterID,
                                                    const CyString& aParameterName,
                                                    bool            aTest,
                                                    const CyString& aValueS,
                                                    __int64         aValueI,
                                                    double          aValueD );
    CY_COM_LIB_API virtual CyResult OnParameterChanged( unsigned long   aParameterIndex,
                                                        unsigned long   aParameterID,
                                                        const CyString& aParameterName,
                                                        const CyString& aValueS,
                                                        __int64         aValueI,
                                                        double          aValueD );

// Data
private:
    struct CyDeviceInternal* mInternal;
    friend struct CyDeviceInternal;
    friend class CyDeviceFlash;
    friend class CyDeviceEEPROM;

private:
    // Disabled methods
	CyDevice( const CyDevice & );
	const CyDevice &operator=( const CyDevice & );

#ifndef CY_DEVICE_NO_BACKWARD_COMPATIBILITY
#include "CyDeviceBackwardCompatibility.h"
#endif // CY_DEVICE_NO_BACKWARD_COMPATIBILITY
};
#endif // __cplusplus


// Standard C Wrapper
/////////////////////////////////////////////////////////////////////////////

// CyDeviceFinder handles
typedef void* CyDeviceH;

// Construction/Destruction
CY_COM_LIB_C_API CyDeviceH CyDevice_Init();
CY_COM_LIB_C_API void CyDevice_Destroy( CyDeviceH aHandle );


// Accessors
CY_COM_LIB_C_API int        CyDevice_IsConnected( CyDeviceH aHandle );
CY_COM_LIB_C_API CyConfigH  CyDevice_GetConfig( CyDeviceH aHandle);

CY_COM_LIB_C_API int        CyDevice_GetChangedStatus( CyDeviceH aHandle );
CY_COM_LIB_C_API CyResult   CyDevice_GetDeviceInfo( CyDeviceH      aHandle,
                                                    unsigned char* aDevId,
                                                    unsigned char* aModId,
                                                    unsigned char* aSubId,
                                                    unsigned char* aVendorId,
                                                    unsigned char* aMac1,
                                                    unsigned char* aMac2,
                                                    unsigned char* aMac3,
                                                    unsigned char* aMac4,
                                                    unsigned char* aMac5,
                                                    unsigned char* aMac6,
                                                    unsigned char* aIP1,
                                                    unsigned char* aIP2,
                                                    unsigned char* aIP3,
                                                    unsigned char* aIP4,
                                                    unsigned char* aVersionMajor,
                                                    unsigned char* aVersionMinor,
                                                    unsigned char* aChannelCount );
CY_COM_LIB_C_API unsigned short CyDevice_GetNextRequestID( CyDeviceH aHandle );


// Connection/Disconnection
CY_COM_LIB_C_API CyResult      CyDevice_Connect   ( unsigned long aFlags );
CY_COM_LIB_C_API CyResult      CyDevice_Connect2  ( CyDeviceH     aHandle,
                                                    CyConfigH     aConfig,
                                                    unsigned long aFlags );
CY_COM_LIB_C_API CyResult      CyDevice_Disconnect( CyDeviceH     aHandle );

// Extension functions
CY_COM_LIB_C_API unsigned long      CyDevice_GetExtensionCount      ( CyDeviceH     aHandle );
CY_COM_LIB_C_API unsigned long      CyDevice_GetExtensionCountByType( CyDeviceH     aHandle,
                                                                      unsigned long aTypeExtensionID );
CY_COM_LIB_C_API unsigned long      CyDevice_GetExtensionIndex      ( CyDeviceH     aHandle,
                                                                      unsigned long aExtensionID );
CY_COM_LIB_C_API int                CyDevice_HasExtensionByIndex    ( CyDeviceH     aHandle,
                                                                      unsigned long aIndex );
CY_COM_LIB_C_API int                CyDevice_HasExtension           ( CyDeviceH     aHandle,
                                                                      unsigned long aExtensionID );
CY_COM_LIB_C_API CyDeviceExtensionH CyDevice_GetExtensionByIndex    ( CyDeviceH     aHandle,
                                                                      unsigned long aIndex );
CY_COM_LIB_C_API CyDeviceExtensionH CyDevice_GetExtension           ( CyDeviceH     aHandle,
                                                                      unsigned long aExtensionID );

// Port communication functions
CY_COM_LIB_C_API int           CyDevice_IsPortAvailable   ( CyDeviceH     aHandle,
                                                            unsigned long aPort );
CY_COM_LIB_C_API int           CyDevice_IsPortUsingInterrupts( CyDeviceH     aHandle,
                                                               unsigned long aPort );
CY_COM_LIB_C_API CyResult      CyDevice_ConfigPort        ( CyDeviceH     aHandle,
                                                            unsigned long aPort,
                                                            const char*   aConfig );
CY_COM_LIB_C_API CyResult      CyDevice_GetPortConfig     ( CyDeviceH     aHandle,
                                                            unsigned long aPort,
                                                            char*         aBuffer,
                                                            unsigned long aBufferSize );
CY_COM_LIB_C_API CyResult      CyDevice_ReceiveAnswer     ( CyDeviceH     aHandle,
                                                            unsigned long aPort,
                                                            void*         aDst,
                                                            unsigned int* aSize,
                                                            unsigned long aInfo );
CY_COM_LIB_C_API CyResult      CyDevice_ResetAnswerQueue  ( CyDeviceH     aHandle,
                                                            unsigned long aPort );
CY_COM_LIB_C_API CyResult      CyDevice_SendCommand       ( CyDeviceH     aHandle,
                                                            unsigned long aPort,
                                                            void*         aSrc,
                                                            unsigned int  aSize,
                                                            unsigned long aInfo );
CY_COM_LIB_C_API unsigned long CyDevice_GetAnswerQueueSize( CyDeviceH     aHandle,
                                                            unsigned long aPort );


// Serial Port Server
CY_COM_LIB_C_API CyResult CyDevice_EnableSystemSerialPort   ( CyDeviceH      aHandle,
                                                              unsigned long  aPort,
                                                              unsigned short aSystemPort,
                                                              const char *   aConfig );
CY_COM_LIB_C_API CyResult CyDevice_DisableSystemSerialPort  ( CyDeviceH     aHandle );
CY_COM_LIB_C_API int      CyDevice_IsSystemSerialPortEnabled( CyDeviceH     aHandle );


// Data access
CY_COM_LIB_C_API CyResult CyDevice_FlushData  ( CyDeviceH   aHandle,
                                                CyChannelID aChannel );

CY_COM_LIB_C_API CyResult CyDevice_ReceiveData( CyDeviceH                   aHandle,
                                                CyChannelID                 aChannel,
                                                void*                       aDst,
                                                unsigned int                aSize,
                                                CyResultEventH              aEvent,
                                                struct DriverSharedMemory*  aSharedMemory, 
                                                unsigned long*              aValue,
                                                unsigned long               aFlags );

CY_COM_LIB_C_API CyResult CyDevice_ReceiveDataToHighMemory( CyDeviceH      aHandle,
                                                            CyChannelID    aChannel,
                                                            unsigned long  aBufferSize,
                                                            unsigned long  aFirstBufferIndex,
                                                            unsigned long  aLastBufferIndex,
                                                            CyResultEventH aEvent,
                                                            CyResult*      aResult,
                                                            unsigned long* aValue );

CY_COM_LIB_C_API CyResult CyDevice_SendData   ( CyDeviceH    aHandle,
                                                CyChannelID  aChannel,
                                                void*        aSrc,
                                                unsigned int aSize );

CY_COM_LIB_C_API CyResult CyDevice_AbortReceiveData( CyDeviceH   saHandle,
                                                     CyChannelID aChannel );

// Control
CY_COM_LIB_C_API void     CyDevice_RegisterCallback ( CyDeviceH         aHandle,
                                                      unsigned long     aId, 
                                                      CyDeviceCallback  aFunction,
                                                      void*             aContext );
CY_COM_LIB_C_API void     CyDevice_RegisterCallback2( CyDeviceH         aHandle,
                                                      unsigned long     aId,
                                                      CyDeviceCallback2 aFunction,
                                                      void*             aContext );
CY_COM_LIB_C_API CyResult CyDevice_Reset( CyDeviceH aHandle );
CY_COM_LIB_C_API CyResult CyDevice_ResetLink( CyDeviceH aHandle );
CY_COM_LIB_C_API CyResult CyDevice_ResetModule( CyDeviceH aHandle );

CY_COM_LIB_C_API int      CyDevice_SupportsStaticConfiguration( CyDeviceH aHandle );
CY_COM_LIB_C_API CyResult CyDevice_SaveConfiguration( CyDeviceH aHandle, 
                                                      int       aIP,
                                                      int       aName,
                                                      int       aConfig,
                                                      int       aState );

// GPIO Control Bits
CY_COM_LIB_C_API CyResult CyDevice_WriteGPIO( CyDeviceH       aHandle,
                                              unsigned short  aSet,
                                              unsigned short  aClear,
                                              int             aBroadcast );
CY_COM_LIB_C_API CyResult CyDevice_ReadGPIO ( CyDeviceH       aHandle,
                                              unsigned short* aBits,
                                              unsigned short* aInputs );


// Save/load settings from XML
CY_COM_LIB_C_API CyResult CyDevice_SaveToXML  ( CyDeviceH      aHandle,
                                                CyXMLDocumentH aDocument );
CY_COM_LIB_C_API CyResult CyDevice_LoadFromXML( CyDeviceH      aHandle,
                                                CyXMLDocumentH aDocument );

// Show Configuration Dialog
CY_COM_LIB_C_API CyResult CyDevice_ShowDialog ( CyDeviceH aHandle,
                                                void*     aParent );

// Register/Config access
CY_COM_LIB_C_API CyResult CyDevice_ReadRegister ( CyDeviceH       aHandle,
                                                  unsigned long   aAddress,
								                  unsigned long  *aValue,
					                              unsigned long   aFlags );
CY_COM_LIB_C_API CyResult CyDevice_WriteRegister( CyDeviceH       aHandle,
                                                  unsigned long   aAddress,
							                      unsigned long   aValue,
										          unsigned long   aFlags  );
CY_COM_LIB_C_API CyResult CyDevice_ReadConfig   ( CyDeviceH       aHandle,
                                                  unsigned short  aAddress,
								                  unsigned short *aValue,
					                              unsigned long   aFlags );
CY_COM_LIB_C_API CyResult CyDevice_WriteConfig  ( CyDeviceH       aHandle,
                                                  unsigned short  aAddress,
							                      unsigned short  aValue,
										          unsigned long   aFlags );

#endif // _CY_DEVICE_H_

