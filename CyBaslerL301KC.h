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
// File Name....: CyBaslerL301KC.h
//
// Description..: Defines the interface of a CameraLink camera.
//
// *****************************************************************************
//
// $Log$
//
// *****************************************************************************

#ifndef __CY_BASLER_L301KC_H__
#define __CY_BASLER_L301KC_H__

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

class CyBaslerL301KC : public CyCameraLink
{
// Constants
public:
#if COYOTE_SDK_VERSION < 0220
    enum
    { 
        BASLER_L301KC = 0x01000000,
    } Flags;

    // 20 Mhz 8 bit RGB
    CY_BASLER_LIB_API static const CyPixelTypeID  s20Mhz8BitRGB;

    // 60 Mhz 8 bit multiplexed RGB single tap
    CY_BASLER_LIB_API static const CyPixelTypeID  s60MhzSingle8BitMultiplexed;

    // 40 Mhz 8 bit multiplexed RGB dual tap
    CY_BASLER_LIB_API static const CyPixelTypeID  s40MhzDual8BitMultiplexed;

    // 60 Mhz 8 bit multiplexed RGB single tap
    CY_BASLER_LIB_API static const CyPixelTypeID  s60MhzSingle10BitMultiplexed;

    // 40 Mhz 8 bit multiplexed RGB dual tap
    CY_BASLER_LIB_API static const CyPixelTypeID  s40MhzDual10BitMultiplexed;
#endif


// Construction / Destruction
public:
    CY_BASLER_LIB_API            CyBaslerL301KC( CyGrabber* aGrabber );
    CY_BASLER_LIB_API virtual    ~CyBaslerL301KC();


// Update Camera
protected:
    CY_BASLER_LIB_API virtual CyResult InternalUpdate( bool aDeviceReset ) const;
    CY_BASLER_LIB_API virtual CyResult LocalUpdate( bool aDeviceReset ) const;


// Show Configuration Dialog
protected:
    CY_BASLER_LIB_API virtual CyResult AddPropertyPage  ( void* aPropertySheet );
    CY_BASLER_LIB_API virtual CyResult OnApply          ( void* aPropertyPage );


// Save/load settings from XML
public:
    CY_BASLER_LIB_API virtual CyResult InternalSave ( CyXMLDocument& aDocument ) const;
    CY_BASLER_LIB_API virtual CyResult InternalLoad ( CyXMLDocument& aDocument );


// Camera specific parameters
public:
    typedef enum
    {
        RED_LINE,
        BLUE_LINE
    } SpatialCorrectionStartingLine;
    CY_BASLER_LIB_API virtual CyResult SetSpatialCorrectionStartingLine( SpatialCorrectionStartingLine  aLine );
    CY_BASLER_LIB_API virtual CyResult GetSpatialCorrectionStartingLine( SpatialCorrectionStartingLine& aLine ) const;

    CY_BASLER_LIB_API virtual CyResult SetSpatialCorrectionDelay( unsigned char  aDelay );
    CY_BASLER_LIB_API virtual CyResult GetSpatialCorrectionDelay( unsigned char& aDelay ) const;

    // Extra parameter
    CY_BASLER_LIB_API virtual CyResult SetParameter     ( const CyString& aName,
                                                          unsigned char      aValue );
    CY_BASLER_LIB_API virtual CyResult GetParameter     ( const CyString& aName,
                                                          unsigned char&     aValue ) const;

    // Overload  SupportsPixelType because some pixel type are not good in 1-tap or 2-tap mode
    CY_BASLER_LIB_API virtual bool     SupportsPixelType( const CyPixelTypeID& aPixel,
                                                          unsigned char        aTapQuantity ) const;

    // Camera Information
    CY_BASLER_LIB_API virtual CyResult GetVendor       ( CyString& aInfo );
    CY_BASLER_LIB_API virtual CyResult GetCameraModel  ( CyString& aInfo );
    CY_BASLER_LIB_API virtual CyResult GetProductID    ( CyString& aInfo );
    CY_BASLER_LIB_API virtual CyResult GetSerialNumber ( CyString& aInfo );
    CY_BASLER_LIB_API virtual CyResult ResetCamera     ( );

private:
    BaslerCam*      mCamera;
    SpatialCorrectionStartingLine  mStartingLine;
    unsigned char   mSpatialCorrectionDelay;

    // Property page
    void*           mPropertyPage;
};


#endif // __CY_BASLER_L301KC_H__
