// *****************************************************************************
//
// $Id$
//
//
// *****************************************************************************
//
//     Copyright (c) 2003, Pleora Technologies Inc., All rights reserved.
//
// *****************************************************************************
//
// File Name....: CyAtmelAviivaM2.h
//
// Description..: Defines the interface of a CameraLink camera.
//
// *****************************************************************************
//
// $Log$
//
// *****************************************************************************

#ifndef __CY_ATMEL_AVIIVA_M2_H__
#define __CY_ATMEL_AVIIVA_M2_H__

// Headers
/////////////////////////////////////////////////////////////////////////////

// ===== This Project =====
#include "CyAtmelLib.h"
#include "CyCameraLink.h"


// Class
/////////////////////////////////////////////////////////////////////////////

class CyAtmelAviivaM2 : public CyCameraLink
{
// Types
public:
#if COYOTE_SDK_VERSION < 0220
    enum
    { 
        ATMEL_AVIIVA = 0x20000000,
    } Flags;

    // Serial 8 bit RGB
    CY_ATMEL_LIB_API static const CyPixelTypeID  sSerial8BitRGB;

    // Serial 12 bit RGB
    CY_ATMEL_LIB_API static const CyPixelTypeID  sSerial12BitRGB;

    // Parallel RGB with Interpolation 1
    CY_ATMEL_LIB_API static const CyPixelTypeID  s8BitRGBInterpolation1;

    // Parallel RGB with Interpolation 3
    CY_ATMEL_LIB_API static const CyPixelTypeID  s8BitRGBInterpolation3;
#endif

// Construction / Destruction
public:
    CY_ATMEL_LIB_API            CyAtmelAviivaM2( CyGrabber* aGrabber,
                                                 bool       aColour );
    CY_ATMEL_LIB_API            CyAtmelAviivaM2( CyGrabber*      aGrabber, 
                                                 bool            aColour,
                                                 CyCameraLimits& aLimits );
    CY_ATMEL_LIB_API virtual    ~CyAtmelAviivaM2();
protected:
    CY_ATMEL_LIB_API virtual CyResult Construct();

 

// Update Camera
protected:
    CY_ATMEL_LIB_API virtual CyResult InternalUpdate( bool aDeviceReset ) const;
    CY_ATMEL_LIB_API virtual CyResult LocalUpdate   ( bool aDeviceReset ) const;


// Show Configuration Dialog
protected:
    CY_ATMEL_LIB_API virtual CyResult AddPropertyPage  ( void* aPropertySheet );
    CY_ATMEL_LIB_API virtual CyResult OnApply          ( void* aPropertyPage );


// Save/load settings from XML
public:
    CY_ATMEL_LIB_API virtual CyResult InternalSave ( CyXMLDocument& aDocument ) const;
    CY_ATMEL_LIB_API virtual CyResult InternalLoad ( CyXMLDocument& aDocument );


// Camera Specific parameters
public:
    // Clock settings
    typedef enum
    {
        EXTERNAL,
        INTERNAL_20_MHZ,
        INTERNAL_30_MHZ,
        INTERNAL_40_MHZ,
        INTERNAL_60_MHZ,
        EXTERNAL_FREQUENCY_DIV_2,
    } ClockMode;
    CY_ATMEL_LIB_API virtual CyResult SetClockMode( ClockMode  aMode );
    CY_ATMEL_LIB_API virtual CyResult GetClockMode( ClockMode& aMode ) const;


    // Time controlled with 2 inputs
    // When synchronization mode is EX_SYNC_LEVEL_CONTROLLED, it is
    // possible to have the camera use one or two inputs.
    CY_ATMEL_LIB_API virtual CyResult SetTimeControlledInputs( unsigned char  aInputs );
    CY_ATMEL_LIB_API virtual CyResult GetTimeControlledInputs( unsigned char& aInputs ) const;


    // Extra parameter
    CY_ATMEL_LIB_API virtual CyResult SetParameter     ( const CyString& aName,
                                                         unsigned char      aValue );
    CY_ATMEL_LIB_API virtual CyResult GetParameter     ( const CyString& aName,
                                                         unsigned char&     aValue ) const;


private:
    // Members
    ClockMode       mClockMode;
    unsigned char   mInputs;
    const bool      mColourCamera;

    // Property page
    void*           mPropertyPage;
};


#endif // __CY_ATMEL_AVIIVA_M2_H__
