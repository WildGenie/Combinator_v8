// *****************************************************************************
//
// $Id$
//
// cy1h08b1
//
// *****************************************************************************
//
//     Copyright (c) 2003, Pleora Technologies Inc., All rights reserved.
//
// *****************************************************************************
//
// File Name....: CyDalsa1M60.h
//
// Description..: Defines the interface of a basic dalsa camera CameraLink camera.
//
// *****************************************************************************
//
// $Log$
//
// *****************************************************************************

#ifndef __CY_DALSA_1M60_H__
#define __CY_DALSA_1M60_H__

// Headers
/////////////////////////////////////////////////////////////////////////////

// ===== This Project =====
#include "CyDalsaLib.h"
#include "CyCameraLink.h"


// Class
/////////////////////////////////////////////////////////////////////////////

class CyDalsa1M60 : public CyCameraLink
{
// Constants
public:
    // Common gains
    CY_DALSA_LIB_API static const unsigned short sAnalogGain;   // Gain 1
    CY_DALSA_LIB_API static const unsigned short sDigitalGain1; // Gain 2
    CY_DALSA_LIB_API static const unsigned short sDigitalGain2; // Gain 3


// Construction / Destruction
public:
    CY_DALSA_LIB_API            CyDalsa1M60( CyGrabber*            aGrabber,
                                             const CyCameraLimits& aLimits,
                                             bool                  a1M60 ); // true = 1M60, false = 1M30
    CY_DALSA_LIB_API virtual    ~CyDalsa1M60();


// Update Camera
protected:
    CY_DALSA_LIB_API virtual CyResult InternalUpdate( bool aDeviceReset ) const;
    CY_DALSA_LIB_API virtual CyResult LocalUpdate( bool aDeviceReset ) const;


// Camera Settings
public:
    CY_DALSA_LIB_API virtual CyResult GetVendor       ( CyString& aInfo );
    CY_DALSA_LIB_API virtual CyResult GetCameraModel  ( CyString& aInfo );
    CY_DALSA_LIB_API virtual CyResult GetSerialNumber ( CyString& aInfo );
    CY_DALSA_LIB_API virtual CyResult ResetCamera     ( );

// Utilities
protected:
    static void GetDataFromString( const CyString& aString,
                                   CyString&       aData );
    static void GetDataFromString( const CyString&  aString,
                                   unsigned char& aData );
    static void GetDataFromString( const CyString&   aString,
                                   unsigned short& aData );
    static CyResult ExtractInformation( const CyString& aData,
                                        const CyString& aTag,
                                        CyString&       aResult );

    CyResult ReadResponse( CyString& aResponse, unsigned int aTimeout, bool aIgnoreResponse = false ) const;
    
private:
    const bool  m1M60;
};


#endif // __CY_DALSA_1M60_H__

