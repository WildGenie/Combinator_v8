// *****************************************************************************
//
// $Id$
//
// cy1d02a1
//
// *****************************************************************************
//
//     Copyright (c) 2003, Pleora Technologies Inc., All rights reserved.
//
// *****************************************************************************
//
// File Name....: CySocketUDP.cpp
//
// *****************************************************************************
//
// $Log$
//
// *****************************************************************************

#ifndef _CY_SOCKET_UDP_H_
#define _CY_SOCKET_DDP_H_

// Includes
/////////////////////////////////////////////////////////////////////////////

// ===== CyUtilsLib =====
#include "CyTypes.h"

#include "CyErrorInterface.h"

// ===== This project =====
#include "CyComLib.h"
#include "CyConfig.h"
#include "CyDeviceFinder.h"

// Forward
/////////////////////////////////////////////////////////////////////////////

#ifdef __cplusplus
class CyDevice;
#ifndef _QNX_
class LinkDrv;
#endif
class LinkUDP;
#endif // __cplusplus

// Class
/////////////////////////////////////////////////////////////////////////////

/* ==========================================================================
@class	CySocketUDP

@since	2003-06-23
========================================================================== */
#ifdef __cplusplus
struct CySocketUDPInternal;
class CySocketUDP : public CyErrorInterface
{
// Data type
public:
	typedef struct
	{
		unsigned char  mIPAddress[ 4 ];
		unsigned short mUDPPort;
	}
	Address;

// Constants
public:
	static const unsigned short ANY_PORT;

// Constructors / Destructor
public:
	CY_COM_LIB_API CySocketUDP( void );

	CY_COM_LIB_API virtual ~CySocketUDP( void );

	CY_COM_LIB_API CyResult Initialize( const CyConfig & aConfig );
	CY_COM_LIB_API CyResult Initialize( const CyConfig::AccessMode aMode, const CyAdapterID& aDeviceID );
	CY_COM_LIB_API CyResult Initialize( const CyDevice & aDevice );
	CY_COM_LIB_API CyResult Initialize( const CyDeviceFinder::DeviceEntry & aInfo );
	CY_COM_LIB_API CyResult Initialize( const CySocketUDP & aSocket );

private:
    // Disabled
    CySocketUDP( const CySocketUDP& );
	const CySocketUDP & operator=( const CySocketUDP & aSocket );

// Accessors
public:
	bool IsBound( void ) const;
	bool IsConnected( void ) const;
	bool IsInitialized( void ) const;

	CyConfig::AccessMode GetAccessMode( void ) const;
	const CyAdapterID& GetAdapterID( void ) const;

// Methods
public:
	CY_COM_LIB_API int Bind( unsigned short aPort );
	CY_COM_LIB_API int CloseSocket( void );
	CY_COM_LIB_API int Connect( const Address * aName );
	CY_COM_LIB_API int Recv( char * aBuffer, int aLen, int aFlags );
	CY_COM_LIB_API int RecvFrom( char * aBuffer, int aLen, int aFlags, Address * aFrom );
	CY_COM_LIB_API int Send( const char * aBuffer, int aLen, int aFlags );
	CY_COM_LIB_API int SendTo( const char * aBuffer, int aLen, int aFlags, const Address * aTo );

private:
	void CheckBound( bool aNeeded = true ) const;
	void CheckConnected( bool aNeeded = true ) const;
	void CheckInitialized( bool aNeeded = true ) const;

	void Init0( void );
	void Init1( void );
	void Init2( void );
	void Init3( void );

// Data
private:
    struct CySocketUDPInternal* mInternal;
};
#endif // __cplusplus

#endif // _CY_SOCKET_UDP_H_
