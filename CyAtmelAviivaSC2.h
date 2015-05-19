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
// File Name....: CyAtmelAviivaSC2.h
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

class CyAtmelAviivaSC2 : public CyCameraLink
{
// Types
public:
    typedef enum
    {
        FREE_RUN_PROGRAMMABLE,
        FREE_RUN_EDGE_CONTROLLED,
        EX_SYNC_LEVEL_CONTROLLED,
        EX_SYNC_PROGRAMMABLE,
        EX_SYNC_EDGE_CONTROLLED,
		EX_SYNC_LEVEL_CONTROLLED_TWO_INPUTS
    } SynchronizationMode;

	typedef enum
	{
		ALL_GAINS        = 0,
		GAIN             = 1,
		EVEN_PIXELS_GAIN = 2,
		ODD_PIXELS_GAIN  = 3,
		RED_GAIN         = 4,
		GREEN_GAIN       = 5,
		BLUE_GAIN        = 6,
		CRR_GAIN         = 7,
		CRG_GAIN         = 8,
		CRB_GAIN         = 9,
		CGR_GAIN         = 10,
		CGG_GAIN         = 11,
		CGB_GAIN         = 12,
		CBR_GAIN         = 13,
		CBG_GAIN         = 14,
		CBB_GAIN         = 15,
		DIGITAL_GAIN     = 16
	} Gains;

	typedef enum
	{
		ALL_OFFSETS      = 0,
		EVEN_DATA_OFFSET = 1,
		ODD_DATA_OFFSET  = 2,
		DIGITAL_OFFSET   = 3
	} Offsets;

#if COYOTE_SDK_VERSION < 0220
    enum
    { 
        ATMEL_AVIIVA = 0x20000000,
    } Flags;

    // Serial 8 bit RGB
    CY_ATMEL_LIB_API static const CyPixelTypeID  sSerial8BitRGB;

    // Serial 10 bit RGB
    CY_ATMEL_LIB_API static const CyPixelTypeID  sSerial10BitRGB;

    // Serial 12 bit RGB
    CY_ATMEL_LIB_API static const CyPixelTypeID  sSerial12BitRGB;
#endif

// Construction / Destruction
public:
    CY_ATMEL_LIB_API            CyAtmelAviivaSC2( CyGrabber* aGrabber );
    CY_ATMEL_LIB_API            CyAtmelAviivaSC2( CyGrabber*      aGrabber, 
                                                 CyCameraLimits& aLimits );
    CY_ATMEL_LIB_API virtual    ~CyAtmelAviivaSC2();
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
    // Triggering (Exposure control mode)
    CY_ATMEL_LIB_API virtual CyResult SetSynchronizationMode( const SynchronizationMode& aMode );
    CY_ATMEL_LIB_API virtual CyResult GetSynchronizationMode( SynchronizationMode& aMode ) const;

    CY_ATMEL_LIB_API virtual CyResult InternalSave ( CyXMLDocument& aDocument ) const;
    CY_ATMEL_LIB_API virtual CyResult InternalLoad ( CyXMLDocument& aDocument );


// Camera Specific parameters
public:
    // Clock settings
    typedef enum
    {
        EXTERNAL_CLOCK_2X,
		EXTERNAL_CLOCK,
		EXTERNAL_CLOCK_DIV_2,
        INTERNAL_20_MHZ,
        INTERNAL_30_MHZ,
        INTERNAL_40_MHZ,
        INTERNAL_60_MHZ,
    } ClockMode;
    CY_ATMEL_LIB_API virtual CyResult SetClockMode( ClockMode  aMode );
    CY_ATMEL_LIB_API virtual CyResult GetClockMode( ClockMode& aMode ) const;

	// Colour Space correction matrix
	typedef enum
	{
		DISABLE,
		ENABLE
	} ColourSpaceEnable;

	CY_ATMEL_LIB_API virtual CyResult SetColourSpaceCorrectionEnable( ColourSpaceEnable  aEnable );
	CY_ATMEL_LIB_API virtual CyResult GetColourSpaceCorrectionEnable( ColourSpaceEnable& aEnable ) const;

    // Extra parameter
    CY_ATMEL_LIB_API virtual CyResult SetParameter     ( const CyString& aName,
                                                         unsigned char      aValue );
    CY_ATMEL_LIB_API virtual CyResult GetParameter     ( const CyString& aName,
                                                         unsigned char&     aValue ) const;


private:
    // Members
    ClockMode         mClockMode;
	ColourSpaceEnable mColourSpaceEnable;
	bool              mTwoInputs;

    // Property page
    void*             mPropertyPage;
};


#endif // __CY_ATMEL_AVIIVA_M2_H__
