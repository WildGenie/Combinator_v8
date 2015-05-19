// *****************************************************************************
//
// $Id$
//
// cy1c01b1
//
// *****************************************************************************
//
//     Copyright (c) 2003, Pleora Technologies Inc., All rights reserved.
//
// *****************************************************************************
//
// File Name....: CyBaslerL304KC.h
//
// Description..: Defines the interface of a CameraLink camera.
//
// *****************************************************************************
//
// $Log$
//
// *****************************************************************************

#ifndef __CY_BASLER_L304KC_H__
#define __CY_BASLER_L304KC_H__

// Headers
/////////////////////////////////////////////////////////////////////////////

// ===== This Project =====
#include "CyBaslerLib.h"
#include "CyCameraLink.h"


// Forward-Declaration
/////////////////////////////////////////////////////////////////////////////

class BaslerCam;



// Class
/////////////////////////////////////////////////////////////////////////////

class CyBaslerL304KC : public CyCameraLink
{
public:
// Constants
#if COYOTE_SDK_VERSION < 0220
    enum
    { 
        BASLER_L304KC = 0x02000000,
    } Flags;

    // 60 Mhz 2 tap 8 bit output
    CY_BASLER_LIB_API static const CyPixelTypeID  s60MHz2Tap8Bit;

    // 60 Mhz 2 tap 10 bit output
    CY_BASLER_LIB_API static const CyPixelTypeID  s60MHz2Tap10Bit;
#endif

// Construction / Destruction
public:
    CY_BASLER_LIB_API            CyBaslerL304KC( CyGrabber* aGrabber );
    CY_BASLER_LIB_API virtual    ~CyBaslerL304KC();

#if COYOTE_SDK_VERSION >= 0220
    CY_BASLER_LIB_API virtual bool SupportsPixelType( const CyPixelTypeID& aPixel,
                                                      unsigned char        aTapQuantity ) const;
#endif

// Update Camera
protected:
    CY_BASLER_LIB_API virtual CyResult InternalUpdate( bool aDeviceReset ) const;
    CY_BASLER_LIB_API virtual CyResult LocalUpdate( bool aDeviceReset ) const;

	CY_BASLER_LIB_API CyResult ReadRegister(
		unsigned short  aAddress,
		unsigned char  *aBuffer,
		unsigned long  &aSize) const;

	CY_BASLER_LIB_API CyResult WriteRegister(
		unsigned short  aAddress,
		unsigned char  *aBuffer,
		unsigned long   aSize) const;

// Camera specific parameters
public:

private:
};


#endif // __CY_BASLER_L304KC_H__
