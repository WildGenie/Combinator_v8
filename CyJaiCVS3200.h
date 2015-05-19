// *****************************************************************************
//
// $Id$
//
// cy1h07b1
//
// *****************************************************************************
//
//     Copyright (c) 2003, Pleora Technologies Inc., All rights reserved.
//
// *****************************************************************************
//
// File Name....: CyJAICVS3200.h
//
// Description..: Defines the interface of a CameraLink camera.
//
// *****************************************************************************
//
// $Log$
//
// *****************************************************************************

#ifndef __CY_JAICVS3200_H__
#define __CY_JAICVS3200_H__

// Headers
/////////////////////////////////////////////////////////////////////////////

// ===== This Project =====
#include "CyJAILib.h"
#include <CyCameraInterface.h>


// Forward-Declaration
/////////////////////////////////////////////////////////////////////////////

class JaiS3200Protocol;


// Class
/////////////////////////////////////////////////////////////////////////////

class CyJAICVS3200 : public CyCameraInterface
{
// Construction / Destruction
public:
    CY_JAI_LIB_API            CyJAICVS3200( CyGrabber* aGrabber );
    CY_JAI_LIB_API virtual    ~CyJAICVS3200();
 

// Update Camera
protected:
    CY_JAI_LIB_API virtual CyResult InternalUpdate( bool aDeviceReset ) const;
    CY_JAI_LIB_API virtual CyResult LocalUpdate(  bool aDeviceReset ) const;


// Show Configuration Dialog
protected:
    CY_JAI_LIB_API virtual CyResult AddPropertyPage  ( void* aPropertySheet );
    CY_JAI_LIB_API virtual CyResult OnApply          ( void* aPropertyPage );


// Save/load settings from XML
public:
    CY_JAI_LIB_API virtual CyResult InternalSave ( CyXMLDocument& aDocument ) const;
    CY_JAI_LIB_API virtual CyResult InternalLoad ( CyXMLDocument& aDocument );


// Camera specific parameters
public:
    // Shutter Speed
    typedef enum
    {
        SHUTTER_SPEED_IRIS,
        SHUTTER_SPEED_OFF,
        SHUTTER_SPEED_FLICKERLESS,
        SHUTTER_SPEED_125,
        SHUTTER_SPEED_250,
        SHUTTER_SPEED_500,
        SHUTTER_SPEED_1000,
        SHUTTER_SPEED_2000,
        SHUTTER_SPEED_4000,
        SHUTTER_SPEED_10000
    } ShutterSpeed;
    CY_JAI_LIB_API virtual CyResult SetShutterSpeed( ShutterSpeed  aSpeed, bool aRuntimeChange = false );
    CY_JAI_LIB_API virtual CyResult GetShutterSpeed( ShutterSpeed& aSpeed ) const;

    // Sensitivity Control
    // Note: Some cameras may have a few of these sensitivity levels.  For such
    // cameras, the value after the last sensitivity is the OFF settings. For
    // example, the CV-S3200 has sensitivy 1 (MAX_2) and sensitivity 2 (MAX_4), thus
    // MAX_8 is the OFF value for that camera.
    typedef enum
    {
        SENSITIVITY_MAX_2,
        SENSITIVITY_MAX_4,
        SENSITIVITY_MAX_8,
        SENSITIVITY_MAX_16,
        SENSITIVITY_MAX_32,
        SENSITIVITY_MAX_64,
        SENSITIVITY_OFF
    } Sensitivity;
    CY_JAI_LIB_API virtual CyResult SetSensitivity( Sensitivity  aSensitivity, bool aRuntimeChange );
    CY_JAI_LIB_API virtual CyResult GetSensitivity( Sensitivity& aSensitivity ) const;


    // Automatic Gain Control
    // Manual Gain value will be stored in gain #TODO
    typedef enum
    {
        AGC_12_DB,
        AGC_24_DB,
        AGC_OFF,
        AGC_MANUAL
    } GainControl;
    CY_JAI_LIB_API virtual CyResult SetAGC( GainControl aGainControl, bool aRuntimeChange );
    CY_JAI_LIB_API virtual CyResult GetAGC( GainControl& aGainControl ) const;


    // Gamma correction
    typedef enum
    {
        GAMMA_0_45,
        GAMMA_0_60,
        GAMMA_1_00,
    } GammaCorrection;
    CY_JAI_LIB_API virtual CyResult SetGammaCorrection( GammaCorrection  aGamma, bool aRuntimeChange );
    CY_JAI_LIB_API virtual CyResult GetGammaCorrection( GammaCorrection& aGamma ) const;


    // Iris Level.  0..18
    CY_JAI_LIB_API virtual CyResult SetIrisLevel( unsigned char  aLevel, bool aRuntimeChange );
    CY_JAI_LIB_API virtual CyResult GetIrisLevel( unsigned char& aLevel ) const;


    // Luminance.   0..255
    CY_JAI_LIB_API virtual CyResult SetLuminance( unsigned char  aLevel, bool aRuntimeChange );
    CY_JAI_LIB_API virtual CyResult GetLuminance( unsigned char& aLevel ) const;


    // White Balance
    typedef enum
    {
        WB_AUTO,
        WB_MANUAL,
        WB_ONEPUSH,
        WB_3200K,
        WB_4600K,
        WB_5200K
    } WhiteBalanceMode;
    CY_JAI_LIB_API virtual CyResult SetWhiteBalanceMode( WhiteBalanceMode  aMode, bool aRuntimeChange );
    CY_JAI_LIB_API virtual CyResult GetWhiteBalanceMode( WhiteBalanceMode& aMode) const;

    // Manual WB value. 0..18
    CY_JAI_LIB_API virtual CyResult SetWhiteBalance( unsigned char  aValue, bool aRuntimeChange );
    CY_JAI_LIB_API virtual CyResult GetWhiteBalance( unsigned char& aValue ) const;


    // Back Light Compensation.
    typedef enum
    {
        BLC_OFF,
        BLC_PATTERN1,
        BLC_PATTERN2,
        BLC_PATTERN3,
    } BackLightCompensation;
    CY_JAI_LIB_API virtual CyResult SetBLC( BackLightCompensation  aBLC, bool aRuntimeChange );
    CY_JAI_LIB_API virtual CyResult GetBLC( BackLightCompensation& aBLC ) const;



    // Extra parameter
    CY_JAI_LIB_API virtual CyResult SetParameter     ( const CyString& aName,
                                                       unsigned char      aValue );
    CY_JAI_LIB_API virtual CyResult GetParameter     ( const CyString& aName,
                                                       unsigned char&     aValue ) const;


private:
    // Members
    ShutterSpeed    mShutterSpeed;
    Sensitivity     mSensitivity;
    GainControl     mGainControl;
    GammaCorrection mGamma;
    unsigned char   mIrisLevel;
    unsigned char   mLuminanceLevel;
    WhiteBalanceMode mWBMode;
    unsigned char    mWBValue;
    BackLightCompensation mBLC;

    JaiS3200Protocol* mProtocol;

    // Property page
    void*           mPropertyPage;
};


#endif // __CY_JAICVS3200_H__

