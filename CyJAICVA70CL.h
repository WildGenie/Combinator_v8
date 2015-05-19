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
// File Name....: CyJAICVA70CL.h
//
// Description..: Defines the interface of a CameraLink camera.
//
// *****************************************************************************
//
// $Log$
//
// *****************************************************************************

#ifndef __CY_JAICVA70CL_H__
#define __CY_JAICVA70CL_H__

// Headers
/////////////////////////////////////////////////////////////////////////////

// ===== This Project =====
#include "CyJAILib.h"
#include "CyCameraLink.h"


// Forward-Declaration
/////////////////////////////////////////////////////////////////////////////

class CXJaiM4PlusCL;


// Class
/////////////////////////////////////////////////////////////////////////////

class CyJAICVA70CL : public CyCameraLink
{
// Construction / Destruction
public:
    CY_JAI_LIB_API            CyJAICVA70CL( CyGrabber* aGrabber, bool aBayerVersion );
    CY_JAI_LIB_API virtual    ~CyJAICVA70CL();
 

// Update Camera
protected:
    CY_JAI_LIB_API virtual CyResult InternalUpdate( bool aDeviceReset ) const;
    CY_JAI_LIB_API virtual CyResult LocalUpdate( bool aDeviceReset ) const;


// Show Configuration Dialog
protected:
    CY_JAI_LIB_API virtual CyResult AddPropertyPage  ( void* aPropertySheet );
    CY_JAI_LIB_API virtual CyResult OnApply          ( void* aPropertyPage );


// Save/load settings from XML
public:
    CY_JAI_LIB_API virtual CyResult InternalSave ( CyXMLDocument& aDocument ) const;
    CY_JAI_LIB_API virtual CyResult InternalLoad ( CyXMLDocument& aDocument );

// Find out the version (Mono/Bayer)
protected:
	CY_JAI_LIB_API virtual bool IsBayerVersion ( ) const;


// Camera specific parameters
public:

    // Smearless enhencement.
    CY_JAI_LIB_API virtual CyResult SetSmearless( bool  aEnable );
    CY_JAI_LIB_API virtual CyResult GetSmearless( bool& aEnable ) const;

	// Trigger mode. The camera can be in one of five modes
    // Only applies when in external sync synchronization mode
	typedef enum 
	{
		TRIGGER_MODE_NORMAL,        // the sync mode determines the ex_sync
		TRIGGER_MODE_SENSOR_GATE,
		TRIGGER_MODE_RESTART_CONT
	} TriggerMode;
    CY_JAI_LIB_API virtual CyResult SetTriggerMode( TriggerMode  aEnable );
    CY_JAI_LIB_API virtual CyResult GetTriggerMode( TriggerMode& aEnable ) const;

    // Trigger Input.  The camera can be triggered by the CameraLink CC1
    // signal or by the Hirose 12 pin connector.
    typedef enum
    {
        CAMERA_LINK_CC1     = 0,
        HIROSE_CONNECTOR    = 1
    } TriggerInput;
    CY_JAI_LIB_API virtual CyResult SetTriggerInput( TriggerInput  aInput );
    CY_JAI_LIB_API virtual CyResult GetTriggerInput( TriggerInput& aInput ) const;

    // Trigger and FEN. LEN & EEN Polarity.
    typedef enum
    {
        POSITIVE,
        NEGATIVE
    } Polarity;
    CY_JAI_LIB_API virtual CyResult SetTriggerPolarity( Polarity  aPolarity );
    CY_JAI_LIB_API virtual CyResult GetTriggerPolarity( Polarity& aPolarity ) const;

    // Shutter mode and shutter speed
    typedef enum
    {
        SHUTTER_MODE_NORMAL,
        SHUTTER_MODE_PROGRAMMABLE_EXPOSURE,
        SHUTTER_MODE_AUTO
    } ShutterMode;
    CY_JAI_LIB_API virtual CyResult SetShutterMode( ShutterMode  aMode );
    CY_JAI_LIB_API virtual CyResult GetShutterMode( ShutterMode& aMode ) const;

    typedef enum
    {
        SHUTTER_SPEED_OFF,
        SHUTTER_SPEED_100,
        SHUTTER_SPEED_120,
        SHUTTER_SPEED_250,
        SHUTTER_SPEED_500,
        SHUTTER_SPEED_1000,
        SHUTTER_SPEED_2000,
        SHUTTER_SPEED_4000,
        SHUTTER_SPEED_8000,
        SHUTTER_SPEED_15000,
        SHUTTER_SPEED_25000,
        SHUTTER_SPEED_75000,
        SHUTTER_SPEED_100000,
        SHUTTER_SPEED_150000,
        SHUTTER_SPEED_300000
    } ShutterSpeed;
    CY_JAI_LIB_API virtual CyResult SetShutterSpeed( ShutterSpeed  aSpeed, bool aRuntimeChange );
    CY_JAI_LIB_API virtual CyResult GetShutterSpeed( ShutterSpeed& aSpeed ) const;

    // Scan mode.  Enables the camera to send all the frame data or half a frame,
    // a quarter of a frame or an eight of a frame.
    typedef enum
    {
        SCAN_MODE_FULL,
        SCAN_MODE_HALF,
        SCAN_MODE_QUARTER,
        SCAN_MODE_EIGHT
    } ScanMode;
    CY_JAI_LIB_API virtual CyResult SetScanMode( ScanMode  aMode );
    CY_JAI_LIB_API virtual CyResult GetScanMode( ScanMode& aMode ) const;

	// Gamma Select - false = Off, true - ON (0.45 gamma correction)
	typedef enum
	{
		GAMMA_OFF_1,
		GAMMA_ON_0_45
	} GammaSelect;
	CY_JAI_LIB_API virtual CyResult SetGammaSelect( GammaSelect aGamma );
	CY_JAI_LIB_API virtual CyResult GetGammaSelect( GammaSelect &aGamma ) const;

	// Gain Select - manual or AGC
	typedef enum
	{
		GAIN_MANUAL,
		GAIN_AGC
	} GainSelect;
	CY_JAI_LIB_API virtual CyResult SetGainSelect( GainSelect aGain );
	CY_JAI_LIB_API virtual CyResult GetGainSelect( GainSelect &aGain ) const;

	// Partial vertical scan. This is not the same as offset because this only works in a certain
	// mode of operation
    CY_JAI_LIB_API virtual CyResult SetAGCReference( unsigned short  aAGCRef );
    CY_JAI_LIB_API virtual CyResult GetAGCReference( unsigned short& aAGCRef ) const;

    // Extra parameter
    CY_JAI_LIB_API virtual CyResult SetParameter     ( const CyString& aName,
                                                       unsigned char      aValue );
    CY_JAI_LIB_API virtual CyResult SetParameter     ( const CyString& aName,
                                                       bool               aValue );
    CY_JAI_LIB_API virtual CyResult SetParameter     ( const CyString& aName,
                                                       unsigned short     aValue );
    CY_JAI_LIB_API virtual CyResult GetParameter     ( const CyString& aName,
                                                       unsigned char&     aValue ) const;
    CY_JAI_LIB_API virtual CyResult GetParameter     ( const CyString& aName,
                                                       bool&              aValue ) const;
    CY_JAI_LIB_API virtual CyResult GetParameter     ( const CyString& aName,
                                                       unsigned short&    aValue ) const;


private:
    // Members
    bool            mSmearless;
    TriggerInput    mTriggerInput;
    Polarity        mTriggerPolarity;
	TriggerMode     mTriggerMode;
    ShutterMode     mShutterMode;
    ShutterSpeed    mShutterSpeed;
    ScanMode        mScanMode;
	GammaSelect     mGammaSelect;
	GainSelect      mGainSelect;
	unsigned short  mAGCReference;

    // Property page
    void*           mPropertyPage;
};


#endif // __CY_JAICVA70CL_H__

