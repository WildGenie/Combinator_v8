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
// File Name....: CyTeliCS6910CL.h
//
// Description..: Defines the interface of a CameraLink camera.
//
// *****************************************************************************
//
// $Log$
//
// *****************************************************************************

#ifndef __CY_TELI_CS_6910_CL_H__
#define __CY_TELI_CS_6910_CL_H__

// Headers
/////////////////////////////////////////////////////////////////////////////

// ===== This Project =====
#include "CyTeliLib.h"
#include "CyCameraLink.h"


// Class
/////////////////////////////////////////////////////////////////////////////

class CyTeliCS6910CL : public CyCameraLink
{
// Types and constants
public:
    CY_TELI_LIB_API static const unsigned short sMainGainIndex;
    CY_TELI_LIB_API static const unsigned short sWBManualRedGainIndex;
    CY_TELI_LIB_API static const unsigned short sWBManualBlueGainIndex;

// Construction / Destruction
public:
    CY_TELI_LIB_API            CyTeliCS6910CL( CyGrabber* aGrabber );
    CY_TELI_LIB_API virtual    ~CyTeliCS6910CL();
 

// Update Camera
protected:
    CY_TELI_LIB_API virtual CyResult InternalUpdate( bool aDeviceReset ) const;
    CY_TELI_LIB_API virtual CyResult LocalUpdate   ( bool aDeviceReset ) const;


// Show Configuration Dialog
protected:
    CY_TELI_LIB_API virtual CyResult AddPropertyPage  ( void* aPropertySheet );
    CY_TELI_LIB_API virtual CyResult OnApply          ( void* aPropertyPage );

// Save/load settings from XML
public:
    CY_TELI_LIB_API virtual CyResult InternalSave ( CyXMLDocument& aDocument ) const;
    CY_TELI_LIB_API virtual CyResult InternalLoad ( CyXMLDocument& aDocument );

    // Grab operations.
    // Because the camera may stop sending data when we configure it, we need
    // to stop the device from grabbing while we send the configuration.
    // We override the start grabbing in order to save the channel and buffer
	CY_TELI_LIB_API virtual CyResult StartGrabbing ( const CyChannel& aChannel,
                                                     CyImageBuffer&   aBuf );

    
// Camera Specific parameters
public:
    // Enable automatic exposure mode
    CY_TELI_LIB_API virtual CyResult SetAutomaticExposure( bool  aEnabled );
    CY_TELI_LIB_API virtual CyResult GetAutomaticExposure( bool& aEnabled ) const;

    // Automatic Exposure Area 
    // 0: Center
    // 1: Spot
    CY_TELI_LIB_API virtual CyResult SetAutomaticExposureArea( unsigned char  aArea );
    CY_TELI_LIB_API virtual CyResult GetAutomaticExposureArea( unsigned char& aArea ) const;

    // Lock automatic exposure
    CY_TELI_LIB_API virtual CyResult SetAutomaticExposureLock( bool  aEnabled );
    CY_TELI_LIB_API virtual CyResult GetAutomaticExposureLock( bool& aEnabled ) const;

    // Gamma Correction
    typedef enum
    {
        GAMMA_0_45,
        GAMMA_1_00,
        GAMMA_PRESET1,
        GAMMA_PRESET2,
        GAMMA_SAMPLE_1,
        GAMMA_SAMPLE_2,
        GAMMA_SAMPLE_3,
        GAMMA_SAMPLE_4
    } Gamma;
    CY_TELI_LIB_API virtual CyResult SetGammaCorrection( Gamma  aGamma );
    CY_TELI_LIB_API virtual CyResult GetGammaCorrection( Gamma& aGamma ) const;

    // Aperture
    typedef enum
    {
        APERTURE_OFF,
        APERTURE_SOFT,
        APERTURE_NORMAL,
        APERTURE_HARD,
        APERTURE_4,
        APERTURE_5,
        APERTURE_6,
        APERTURE_7
    } Aperture;
    CY_TELI_LIB_API virtual CyResult SetAperture( Aperture  aAperture );
    CY_TELI_LIB_API virtual CyResult GetAperture( Aperture& aAperture ) const;

    // White Balance
    typedef enum
    {
        WB_MODE_MANUAL,
        WB_MODE_AUTOMATIC,
        WB_MODE_ONEPUSH
    } WBMode;
    CY_TELI_LIB_API virtual CyResult SetWhiteBalanceMode( WBMode  aMode );
    CY_TELI_LIB_API virtual CyResult GetWhiteBalanceMode( WBMode& aMode )const;

    // WB Manual temperature
    typedef enum
    {
        WB_TEMP_3000K,
        WB_TEMP_3700K,
        WB_TEMP_4000K,
        WB_TEMP_4500K,
        WB_TEMP_5500K,
        WB_TEMP_6500K,
        WB_TEMP_MANUAL
    } WBTemperature;
    CY_TELI_LIB_API virtual CyResult SetWhiteBalanceTemperature( WBTemperature  aTemp );
    CY_TELI_LIB_API virtual CyResult GetWhiteBalanceTemperature( WBTemperature& aTemp )const;

    // Execute the One-Push white balance
    CY_TELI_LIB_API virtual CyResult DoOnePushWhiteBalance() const;


    CY_TELI_LIB_API virtual CyResult SetParameter     ( const CyString& aName,
                                                        unsigned char      aValue );
    CY_TELI_LIB_API virtual CyResult SetParameter     ( const CyString& aName,
                                                        bool               aValue );
    CY_TELI_LIB_API virtual CyResult GetParameter     ( const CyString& aName,
                                                        unsigned char&     aValue ) const;
    CY_TELI_LIB_API virtual CyResult GetParameter     ( const CyString& aName,
                                                        bool&              aValue ) const;


private:
    // Members
    bool            mAutomaticExposure;
    unsigned char   mAutomaticExposureArea;
    bool            mAutomaticExposureLock;
    Gamma           mGamma;
    Aperture        mAperture;
    WBMode          mWBMode;
    WBTemperature   mWBTemp;

    // Current grabbing
    CyImageBuffer*  mBuffer;
    CyChannel       mChannel;

    // Property page
    void*           mPropertyPage;
};


#endif // __CY_TELI_CS_6910_CL_H__