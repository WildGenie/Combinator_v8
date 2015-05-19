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
// File Name....: CyJAICVM2.h
//
// Description..: Defines the interface of a CameraLink camera.
//
// *****************************************************************************
//
// $Log$
//
// *****************************************************************************

#ifndef __CY_JAICVM2_H__
#define __CY_JAICVM2_H__

// Headers
/////////////////////////////////////////////////////////////////////////////

// ===== This Project =====
#include "CyJAILib.h"
#include "CyCameraLink.h"


// Forward-Declaration
/////////////////////////////////////////////////////////////////////////////

class CXJaiM4Plus;


// Class
/////////////////////////////////////////////////////////////////////////////

class CyJAICVM2 : public CyCameraLink
{
// Construction / Destruction
public:
    CY_JAI_LIB_API            CyJAICVM2( CyGrabber* aGrabber );
    CY_JAI_LIB_API virtual    ~CyJAICVM2();
 

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
    // Gains & offsets
    CY_JAI_LIB_API virtual CyResult SetGain  ( unsigned short  aIndex,
                                               short           aGain );

    // External Gain.  When this is true, the external potentiometer is 
    // used for the gain value.
    CY_JAI_LIB_API virtual CyResult SetExternalGain( bool  aEnable );
    CY_JAI_LIB_API virtual CyResult GetExternalGain( bool& aEnable ) const;

	// Trigger mode. The camera can be in one of six modes
    // Only applies when in external sync synchronization mode
	typedef enum
	{
		TRIGGER_MODE_NORMAL,        // the sync mode determines the ex_sync
		TRIGGER_MODE_RESTART_CONT,
		TRIGGER_MODE_BURST_EPS,
		TRIGGER_MODE_PIV
	} TriggerMode;
    CY_JAI_LIB_API virtual CyResult SetTriggerMode( TriggerMode  aEnable );
    CY_JAI_LIB_API virtual CyResult GetTriggerMode( TriggerMode& aEnable ) const;

    // Trigger Input.  The camera can be triggered by the CameraLink CC1
    // signal or by the Hirose 12 pin connector.
    typedef enum
    {
        CAMERA_LINK_CC1,
        HIROSE_CONNECTOR
    } TriggerInput;
    CY_JAI_LIB_API virtual CyResult SetTriggerInput( TriggerInput  aInput );
    CY_JAI_LIB_API virtual CyResult GetTriggerInput( TriggerInput& aInput ) const;

    // Trigger Polarity.
    typedef enum
    {
        ACTIVE_LOW,
        ACTIVE_HIGH
    } Polarity;
    CY_JAI_LIB_API virtual CyResult SetTriggerPolarity( Polarity  aPolarity );
    CY_JAI_LIB_API virtual CyResult GetTriggerPolarity( Polarity& aPolarity ) const;

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
        SHUTTER_SPEED_1_60,
        SHUTTER_SPEED_1_120,
        SHUTTER_SPEED_1_250,
        SHUTTER_SPEED_1_500,
        SHUTTER_SPEED_1_1000,
        SHUTTER_SPEED_1_2000,
        SHUTTER_SPEED_1_4000,
        SHUTTER_SPEED_1_8000,
        SHUTTER_SPEED_1_14000
    } ShutterSpeed;
    CY_JAI_LIB_API virtual CyResult SetShutterSpeed( ShutterSpeed  aSpeed, bool aRuntimeChange = false );
    CY_JAI_LIB_API virtual CyResult GetShutterSpeed( ShutterSpeed& aSpeed ) const;

    // Scan mode.  Enables the camera to send all the frame data or half a frame,
    // a quarter of a frame or an eight of a frame.
    typedef enum
    {
        SCAN_MODE_FULL,
        SCAN_MODE_HALF,
        SCAN_MODE_QUARTER,
        SCAN_MODE_EIGHTH,
		SCAN_MODE_PROG_PARTIAL_SCAN
    } ScanMode;
    CY_JAI_LIB_API virtual CyResult SetScanMode( ScanMode  aMode );
    CY_JAI_LIB_API virtual CyResult GetScanMode( ScanMode& aMode ) const;

	// Partial vertical scan. This is not the same as offset because this only works in a certain
	// mode of operation
    CY_JAI_LIB_API virtual CyResult SetPartialScanStart( unsigned short  aMode );
    CY_JAI_LIB_API virtual CyResult GetPartialScanStart( unsigned short& aMode ) const;
    CY_JAI_LIB_API virtual CyResult SetPartialScanHeight( unsigned short  aMode );
    CY_JAI_LIB_API virtual CyResult GetPartialScanHeight( unsigned short& aMode ) const;


	// EPS Burst shutter speeds
	// Indexes are from 1 to 5 to conform with camera naming convention
	// The speed is in nanoseconds to conform with the exposure time, and other time methods
	CY_JAI_LIB_API virtual CyResult SetEPSBurstShutterTime( unsigned short aIndex, unsigned long aSpeed );
	CY_JAI_LIB_API virtual CyResult GetEPSBurstShutterTime( unsigned short aIndex, unsigned long &aSpeed ) const;

	// Gamma Select - false = Off, true - ON (0.45 gamma correction)
	typedef enum
	{
		GAMMA_OFF_1,
		GAMMA_ON_0_45
	} GammaSelect;
	CY_JAI_LIB_API virtual CyResult SetGammaSelect( GammaSelect aGamma );
	CY_JAI_LIB_API virtual CyResult GetGammaSelect( GammaSelect &aGamma ) const;

	// Sensor Gate control
	typedef enum
	{
		SENSOR_GATE_OFF,
		SENSOR_GATE_ON
	} SensorGate;
	CY_JAI_LIB_API virtual CyResult SetSensorGate( SensorGate aGate );
	CY_JAI_LIB_API virtual CyResult GetSensorGate( SensorGate &aGate ) const;

	// LVAL sync accum
	typedef enum
	{
		LVAL_SYNC_ACCUM,
		LVAL_ASYNC_ACCUM
	} LVALSyncAccum;
	CY_JAI_LIB_API virtual CyResult SetLVALSyncAccum( LVALSyncAccum aLVALSyncAccum );
	CY_JAI_LIB_API virtual CyResult GetLVALSyncAccum( LVALSyncAccum &aLVALSyncAccum ) const;

	// Knee adjustment
	CY_JAI_LIB_API virtual CyResult SetKneeSelect( bool aKneeSelect );
	CY_JAI_LIB_API virtual CyResult GetKneeSelect( bool &aKneeSelect ) const;
	CY_JAI_LIB_API virtual CyResult SetKneeLevel( short aKneeLevel );
	CY_JAI_LIB_API virtual CyResult GetKneeLevel( short &aKneeLevel ) const;
	CY_JAI_LIB_API virtual CyResult SetKneeLevelRFine( short aKneeLevelRFine );
	CY_JAI_LIB_API virtual CyResult GetKneeLevelRFine( short &aKneeLevelRFine ) const;

	typedef enum
	{
		ADA_OFF,
		ADA_ABA,
		ADA_AWA
	} AutoDualAdjust;
	CY_JAI_LIB_API virtual CyResult SetAutoDualAdjust( AutoDualAdjust aAutoDualAdjust );
	CY_JAI_LIB_API virtual CyResult GetAutoDualAdjust( AutoDualAdjust &aAutoDualAdjust ) const;


    // Extra parameter
    CY_JAI_LIB_API virtual CyResult SetParameter     ( const CyString& aName,
                                                       unsigned char      aValue );
    CY_JAI_LIB_API virtual CyResult SetParameter     ( const CyString& aName,
                                                       bool               aValue );
    CY_JAI_LIB_API virtual CyResult SetParameter     ( const CyString& aName,
                                                       unsigned short     aValue );
    CY_JAI_LIB_API virtual CyResult SetParameter     ( const CyString& aName,
                                                       unsigned long      aValue );

    CY_JAI_LIB_API virtual CyResult GetParameter     ( const CyString& aName,
                                                       unsigned char&     aValue ) const;
    CY_JAI_LIB_API virtual CyResult GetParameter     ( const CyString& aName,
                                                       bool&              aValue ) const;
    CY_JAI_LIB_API virtual CyResult GetParameter     ( const CyString& aName,
                                                       unsigned short&    aValue ) const;
    CY_JAI_LIB_API virtual CyResult GetParameter     ( const CyString& aName,
                                                       unsigned long&     aValue ) const;


private:
    CyResult SendCharacters ( const char*  aData,
                              unsigned int aDataSize ) const;
    CyResult SendCommand    ( const char*  aData,
                              unsigned int aDataSize ) const;
    CyResult ReceiveAnswer  ( const char*  aData,
                              unsigned int aDataSize,
                              long*        aValue ) const;

private:
    // Members
    ScanMode        mScanMode;
	unsigned short  mPartialScanStart;
	unsigned short  mPartialScanHeight;
	TriggerMode     mTriggerMode;
    ShutterMode     mShutterMode;
    ShutterSpeed    mShutterSpeed;
	unsigned short  mEPSBurstShutter[5]; // stored in camera units
	LVALSyncAccum   mLVALSyncAccum;
    TriggerInput    mTriggerInput;
    Polarity        mTriggerPolarity;
	SensorGate      mSensorGate;
	bool            mKneeSelect;
	short           mKneeLevel;
	short           mKneeLevelRFine;
	GammaSelect     mGammaSelect;
    bool            mExternalGain;
	AutoDualAdjust  mAutoDualAdjust;
	double          mH; // the time increment size

    // Property page
    void*           mPropertyPage;
};

#endif // __CY_JAICVM2_H__

