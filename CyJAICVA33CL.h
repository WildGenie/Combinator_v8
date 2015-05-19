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

#ifndef __CY_JAICVA33CL_H__
#define __CY_JAICVA33CL_H__

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

class CyJAICVA33CL : public CyCameraLink
{
// Construction / Destruction
public:
    CY_JAI_LIB_API            CyJAICVA33CL( CyGrabber* aGrabber );
    CY_JAI_LIB_API virtual    ~CyJAICVA33CL();
 

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
    // Auto Trigger mode.  Only applies when synchro mode is Ex sync
    CY_JAI_LIB_API virtual CyResult SetAutoTriggerMode( bool  aEnabled );
    CY_JAI_LIB_API virtual CyResult GetAutoTriggerMode( bool& aEnabled ) const;

    // Auto trigger value
    CY_JAI_LIB_API virtual CyResult SetAutoTriggerValue( unsigned short  aValue );
    CY_JAI_LIB_API virtual CyResult GetAutoTriggerValue( unsigned short& aValue ) const;


    // Trigger Input.  The camera can be triggered by the CameraLink CC1
    // signal or by the Hirose 12 pin connector.
    typedef enum
    {
        CAMERA_LINK_CC1     = 0,
        HIROSE_CONNECTOR    = 1
    } TriggerInput;
    CY_JAI_LIB_API virtual CyResult SetTriggerInput( TriggerInput  aInput );
    CY_JAI_LIB_API virtual CyResult GetTriggerInput( TriggerInput& aInput ) const;

    // Trigger Polarity.
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
        SHUTTER_MODE_PROGRAMMABLE_EXPOSURE
    } ShutterMode;
    CY_JAI_LIB_API virtual CyResult SetShutterMode( ShutterMode  aMode );
    CY_JAI_LIB_API virtual CyResult GetShutterMode( ShutterMode& aMode ) const;

    // Shutter speed
    typedef enum
    {
        SHUTTER_SPEED_OFF,
        SHUTTER_SPEED_250,
        SHUTTER_SPEED_500,
        SHUTTER_SPEED_1000,
        SHUTTER_SPEED_2000,
        SHUTTER_SPEED_5000,
        SHUTTER_SPEED_10000,
        SHUTTER_SPEED_20000,
    } ShutterSpeed;
    CY_JAI_LIB_API virtual CyResult SetShutterSpeed( ShutterSpeed  aSpeed, bool aRuntimeChange );
    CY_JAI_LIB_API virtual CyResult GetShutterSpeed( ShutterSpeed& aSpeed ) const;

    // Calibrate the sensor
    CY_JAI_LIB_API virtual CyResult CalibrateSensor() const;


    // Camera Information
    CY_JAI_LIB_API virtual CyResult GetVendor       ( CyString& aInfo );
    CY_JAI_LIB_API virtual CyResult GetCameraModel  ( CyString& aInfo );
    CY_JAI_LIB_API virtual CyResult GetProductID    ( CyString& aInfo );
    CY_JAI_LIB_API virtual CyResult GetSerialNumber ( CyString& aInfo );
    CY_JAI_LIB_API virtual CyResult ResetCamera     ( );

    // Extra parameter
    CY_JAI_LIB_API virtual CyResult SetParameter     ( const CyString& aName,
                                                       unsigned char      aValue );
    CY_JAI_LIB_API virtual CyResult SetParameter     ( const CyString& aName,
                                                       unsigned short     aValue );
    CY_JAI_LIB_API virtual CyResult SetParameter     ( const CyString& aName,
                                                       bool               aValue );
    CY_JAI_LIB_API virtual CyResult GetParameter     ( const CyString& aName,
                                                       unsigned char&     aValue ) const;
    CY_JAI_LIB_API virtual CyResult GetParameter     ( const CyString& aName,
                                                       unsigned short &   aValue ) const;
    CY_JAI_LIB_API virtual CyResult GetParameter     ( const CyString& aName,
                                                       bool&              aValue ) const;


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
    bool            mAutoTriggerMode;
    unsigned short  mAutoTriggerValue;
    TriggerInput    mTriggerInput;
    Polarity        mTriggerPolarity;
    ShutterMode     mShutterMode;
    ShutterSpeed    mShutterSpeed;

    // Property page
    void*           mPropertyPage;
};


#endif // __CY_JAICVM7CL_H__

