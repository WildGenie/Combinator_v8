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
// File Name....: CyJAICVM7CL.h
//
// Description..: Defines the interface of a CameraLink camera.
//
// *****************************************************************************
//
// $Log$
//
// *****************************************************************************

#ifndef __CY_JAICVM7CL_H__
#define __CY_JAICVM7CL_H__

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

class CyJAICVM7CL : public CyCameraLink
{
// Construction / Destruction
public:
    CY_JAI_LIB_API            CyJAICVM7CL( CyGrabber* aGrabber );
    CY_JAI_LIB_API virtual    ~CyJAICVM7CL();
 

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


// Camera specific parameters
public:
    // External Gain.  When this is true, the external potentiometer is 
    // used for the gain value.
    CY_JAI_LIB_API virtual CyResult SetExternalGain( bool  aEnable );
    CY_JAI_LIB_API virtual CyResult GetExternalGain( bool& aEnable ) const;

    // Smearless enhencement.
    CY_JAI_LIB_API virtual CyResult SetSmearless( bool  aEnable );
    CY_JAI_LIB_API virtual CyResult GetSmearless( bool& aEnable ) const;

    // Trigger Input.  The camera can be triggered by the CameraLink CC1
    // signal or by the Hirose 12 pin connector.
    typedef enum
    {
        HIROSE_CONNECTOR    = 0,
        CAMERA_LINK_CC1     = 1
    } TriggerInput;
    CY_JAI_LIB_API virtual CyResult SetTriggerInput( TriggerInput  aInput );
    CY_JAI_LIB_API virtual CyResult GetTriggerInput( TriggerInput& aInput ) const;

    // Frame Delay Readout Trigger Mode.  A special external sync, the trigger
    // controls the exposure and the read-out is done when an external VD signal
    // is given to the camera.  This has no effect if the camera is in free
    // running mode.
    CY_JAI_LIB_API virtual CyResult SetFrameDelayReadout( bool  aEnable );
    CY_JAI_LIB_API virtual CyResult GetFrameDelayReadout( bool& aEnable ) const;

    // In Frame Delay Readout mode.  It is possible to have multiple shutter
    // operations.
    CY_JAI_LIB_API virtual CyResult SetMultipleShutter( bool  aEnable );
    CY_JAI_LIB_API virtual CyResult GetMultipleShutter( bool& aEnable ) const;

    // Trigger and FEN. LEN & EEN Polarity.
    typedef enum
    {
        POSITIVE,
        NEGATIVE
    } Polarity;
    CY_JAI_LIB_API virtual CyResult SetTriggerPolarity( Polarity  aPolarity );
    CY_JAI_LIB_API virtual CyResult GetTriggerPolarity( Polarity& aPolarity ) const;
    CY_JAI_LIB_API virtual CyResult SetEENPolarity( Polarity  aPolarity );
    CY_JAI_LIB_API virtual CyResult GetEENPolarity( Polarity& aPolarity ) const;

    // Shutter mode and shutter speed
    typedef enum
    {
        SHUTTER_MODE_NORMAL,
        SHUTTER_MODE_PROGRAMMABLE_EXPOSURE
    } ShutterMode;
    CY_JAI_LIB_API virtual CyResult SetShutterMode( ShutterMode  aMode );
    CY_JAI_LIB_API virtual CyResult GetShutterMode( ShutterMode& aMode ) const;

    typedef enum
    {
        SHUTTER_SPEED_OFF,
        SHUTTER_SPEED_50,
        SHUTTER_SPEED_100,
        SHUTTER_SPEED_200,
        SHUTTER_SPEED_400,
        SHUTTER_SPEED_800,
        SHUTTER_SPEED_1500,
        SHUTTER_SPEED_3000,
        SHUTTER_SPEED_5500,
        SHUTTER_SPEED_10000
    } ShutterSpeed;
    CY_JAI_LIB_API virtual CyResult SetShutterSpeed( ShutterSpeed  aSpeed, bool aRuntimeChange );
    CY_JAI_LIB_API virtual CyResult GetShutterSpeed( ShutterSpeed& aSpeed ) const;

    // Select the signal to send to the signal output pin of the Hirose
    // connector.  (Pin 9)
    typedef enum
    {
        OUTPUT_SYNC,
        OUTPUT_EEN,
        OUTPUT_OFF
    } SignalOutput;
    CY_JAI_LIB_API virtual CyResult SetSignalOutput( SignalOutput  aOutput );
    CY_JAI_LIB_API virtual CyResult GetSignalOutput( SignalOutput& aOutput ) const;

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

    // Extra parameter
    CY_JAI_LIB_API virtual CyResult SetParameter     ( const CyString& aName,
                                                       unsigned char      aValue );
    CY_JAI_LIB_API virtual CyResult SetParameter     ( const CyString& aName,
                                                       bool               aValue );
    CY_JAI_LIB_API virtual CyResult GetParameter     ( const CyString& aName,
                                                       unsigned char&     aValue ) const;
    CY_JAI_LIB_API virtual CyResult GetParameter     ( const CyString& aName,
                                                       bool&              aValue ) const;


private:
    // Members
    bool            mExternalGain;
    bool            mSmearless;
    TriggerInput    mTriggerInput;
    bool            mFrameDelayReadout;
    bool            mMultipleShutter;
    Polarity        mTriggerPolarity;
    Polarity        mEENPolarity;
    ShutterMode     mShutterMode;
    ShutterSpeed    mShutterSpeed;
    SignalOutput    mSignalOutput;
    ScanMode        mScanMode;

    // Property page
    void*           mPropertyPage;
};


#endif // __CY_JAICVM7CL_H__

