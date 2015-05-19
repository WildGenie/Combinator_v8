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
// File Name....: CyPulnixTM4000.h
//
// Description..: Defines the interface of a CameraLink camera.
//
// *****************************************************************************
//
// $Log$
//
// *****************************************************************************

#ifndef __CY_PULNIX_TM4000_H__
#define __CY_PULNIX_TM4000_H__

// Headers
/////////////////////////////////////////////////////////////////////////////

// ===== CyCamLib =====
#include <CyCameraLink.h>

// ===== This Project =====
#include "CyPulnixLib.h"


// Class
/////////////////////////////////////////////////////////////////////////////

class CyPulnixTM4000 : public CyCameraLink
{
// types and constants
public:
    // Gain indexes
    CY_PULNIX_LIB_API static const unsigned short sGainChannelAIndex;
    CY_PULNIX_LIB_API static const unsigned short sGainChannelBIndex;

    // Offset indexes
    CY_PULNIX_LIB_API static const unsigned short sOffsetChannelAIndex;
    CY_PULNIX_LIB_API static const unsigned short sOffsetChannelBIndex;


// Construction / Destruction
public:
    CY_PULNIX_LIB_API            CyPulnixTM4000( CyGrabber*            aGrabber,
                                                 const CyString&       aName,
                                                 const CyCameraLimits& aLimits );
    CY_PULNIX_LIB_API virtual    ~CyPulnixTM4000();

// Update Camera
protected:
    CY_PULNIX_LIB_API virtual CyResult InternalUpdate( bool aDeviceReset ) const;
    CY_PULNIX_LIB_API virtual CyResult LocalUpdate( bool aDeviceReset ) const;


// Show Configuration Dialog
protected:
    CY_PULNIX_LIB_API virtual CyResult AddPropertyPage  ( void* aPropertySheet );
    CY_PULNIX_LIB_API virtual CyResult OnApply          ( void* aPropertyPage );


// Save/load settings from XML
public:
    CY_PULNIX_LIB_API virtual CyResult InternalSave ( CyXMLDocument& aDocument ) const;
    CY_PULNIX_LIB_API virtual CyResult InternalLoad ( CyXMLDocument& aDocument );


// Camera specific parameters
public:
    // Automatic Gain Channel Balancing
    CY_PULNIX_LIB_API virtual CyResult SetAutoGainChannelBalance( bool  aEnabled );
    CY_PULNIX_LIB_API virtual CyResult GetAutoGainChannelBalance( bool& aEnabled ) const;

    // Automatic Calibration
    CY_PULNIX_LIB_API virtual CyResult SetAutoCalibration( bool  aEnabled );
    CY_PULNIX_LIB_API virtual CyResult GetAutoCalibration( bool& aEnabled ) const;

    // Shutter mode:
    //  manual (false): uses shutter value
    //  direct (true): uses value stored with Get/SetExposureTime
    CY_PULNIX_LIB_API virtual CyResult SetDirectShutterMode( bool  aDirect );
    CY_PULNIX_LIB_API virtual CyResult GetDirectShutterMode( bool& aDirect ) const;

    // Shutter value
    CY_PULNIX_LIB_API virtual CyResult SetShutterValue( unsigned char  aValue );
    CY_PULNIX_LIB_API virtual CyResult GetShutterValue( unsigned char& aValue ) const;

    // Scan Mode
    //
    // Warning: make sure that the windowing is smaller than the camera output size.
    typedef enum
    {
        SM_FULL     = 'A',
        SM_HALF     = 'B',
        SM_QUARTER  = 'C',
        SM_EIGHT    = 'D',
    } ScanMode;

    CY_PULNIX_LIB_API virtual CyResult SetScanMode( ScanMode  aMode );
    CY_PULNIX_LIB_API virtual CyResult GetScanMode( ScanMode& aMode ) const;


    // Set the Look-Up Table Mode
    typedef enum
    {
        LUT_LINEAR,
        LUT_GM45,
        LUT_KNEE
    } LookUpTableMode;
    CY_PULNIX_LIB_API virtual CyResult SetLookUpTableMode( LookUpTableMode  aMode );
    CY_PULNIX_LIB_API virtual CyResult GetLookUpTableMode( LookUpTableMode& aMode ) const;

    // Set a negative or positive LUT
    CY_PULNIX_LIB_API virtual CyResult SetNegativeLUT( bool  aNegative );
    CY_PULNIX_LIB_API virtual CyResult GetNegativeLUT( bool& aNegative ) const;

    // Set the Knee values
    CY_PULNIX_LIB_API virtual CyResult SetKneeX1( unsigned char  aValue );
    CY_PULNIX_LIB_API virtual CyResult GetKneeX1( unsigned char& aValue ) const;
    CY_PULNIX_LIB_API virtual CyResult SetKneeY1( unsigned char  aValue );
    CY_PULNIX_LIB_API virtual CyResult GetKneeY1( unsigned char& aValue ) const;
    CY_PULNIX_LIB_API virtual CyResult SetKneeX2( unsigned char  aValue );
    CY_PULNIX_LIB_API virtual CyResult GetKneeX2( unsigned char& aValue ) const;
    CY_PULNIX_LIB_API virtual CyResult SetKneeY2( unsigned char  aValue );
    CY_PULNIX_LIB_API virtual CyResult GetKneeY2( unsigned char& aValue ) const;


    // Extra parameter
    CY_PULNIX_LIB_API virtual CyResult SetParameter     ( const CyString& aName,
                                                          unsigned char      aValue );
    CY_PULNIX_LIB_API virtual CyResult SetParameter     ( const CyString& aName,
                                                          bool               aValue );
    CY_PULNIX_LIB_API virtual CyResult GetParameter     ( const CyString& aName,
                                                          unsigned char&     aValue ) const;
    CY_PULNIX_LIB_API virtual CyResult GetParameter     ( const CyString& aName,
                                                          bool&              aValue ) const;


// Camera communication
private:
    CyResult WriteCommand( const char *  aCommand,
                           unsigned long aCommandSize ) const;
    CyResult ReadCommand( const char*    aCommand,
                          unsigned long  aCommandSize,
                          CyString&   aValue ) const; 

private:
    const CyString  mName;

    // Members
    bool            mAutoGainChannelBalance;
    bool            mAutoCalibration;
    bool            mDirectShutterMode;
    unsigned char   mShutterValue;
    ScanMode        mScanMode;

    bool            mNegativeLUT;
    LookUpTableMode mLUTMode;
    unsigned char   mKneeX1;
    unsigned char   mKneeY1;
    unsigned char   mKneeX2;
    unsigned char   mKneeY2;

    // Property page
    void*           mPropertyPage;
};


#endif // __CY_PULNIX_TM4000_H__