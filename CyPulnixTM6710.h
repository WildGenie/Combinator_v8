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
// File Name....: CyPulnixTM6710.h
//
// Description..: Defines the interface of a CameraLink camera.
//
// *****************************************************************************
//
// $Log$
//
// *****************************************************************************

#ifndef __CY_PULNIX_TM6710CL_H__
#define __CY_PULNIX_TM6710CL_H__

// Headers
/////////////////////////////////////////////////////////////////////////////

// ===== This Project =====
#include "CyPulnixLib.h"
#include "CyCameraLink.h"


// Forward-Declaration
/////////////////////////////////////////////////////////////////////////////

class CyPulnixProtocol;


// Class
/////////////////////////////////////////////////////////////////////////////

class CyPulnixTM6710 : public CyCameraLink
{
// types and constants
public:
    // Special pixel type for this camera
    // Converts are available to Grayscale 8, RGB14, RGB24 and BGR32
#if COYOTE_SDK_VERSION < 0220
    enum
    { 
        PULNIX_TM6700 = 0x10000000,
    } Flags;
    CY_PULNIX_LIB_API static const CyPixelTypeID  sGrayscale8;
#endif

    // Gain indexes
    CY_PULNIX_LIB_API static const unsigned short sMainGain;
    CY_PULNIX_LIB_API static const unsigned short sChannelAGain;
    CY_PULNIX_LIB_API static const unsigned short sChannelBGain;

    // Offset Indexes
    CY_PULNIX_LIB_API static const unsigned short sChannelAOffset;
    CY_PULNIX_LIB_API static const unsigned short sChannelBOffset;
    CY_PULNIX_LIB_API static const unsigned short sVTopOffset;



// Construction / Destruction
public:
    CY_PULNIX_LIB_API            CyPulnixTM6710( CyGrabber*            aGrabber,
                                                  const CyCameraLimits& aLimits );
    CY_PULNIX_LIB_API virtual    ~CyPulnixTM6710();
 

// Update Camera
protected:
    CY_PULNIX_LIB_API virtual CyResult InternalUpdate( bool aDeviceReset ) const;
    CY_PULNIX_LIB_API virtual CyResult LocalUpdate( bool aDeviceReset ) const;


// Show Configuration Dialog
protected:
    CY_PULNIX_LIB_API virtual CyResult AddPropertyPage  ( void* aPropertySheet );


// Save/load settings from XML
public:
    CY_PULNIX_LIB_API virtual CyResult InternalSave ( CyXMLDocument& aDocument ) const;
    CY_PULNIX_LIB_API virtual CyResult InternalLoad ( CyXMLDocument& aDocument );


// Camera specific parameters
public:
    // Override SetGain and SetOffset in order to apply real time
    CY_PULNIX_LIB_API virtual CyResult SetGain  ( unsigned short  aIndex,
                                                  short           aGain );
    CY_PULNIX_LIB_API virtual CyResult SetOffset( unsigned short  aIndex,
                                                  short           aOffset );

    // Shutter Mode
    CY_PULNIX_LIB_API virtual CyResult SetAsyncShutterMode( bool  aEnabled );
    CY_PULNIX_LIB_API virtual CyResult GetAsyncShutterMode( bool& aEnabled ) const;


    // Shutter value
    //      Manual      Async
    //
    // 0:   Normal      Normal
    // 1:   1/125       1/32000
    // 2:   1/250       1/16000
    // 3:   1/500       1/8000
    // 4:   1/1000      1/4000
    // 5:   1/2000      1/2000
    // 6:   1/4000      1/1000
    // 7:   1/8000      1/500
    // 8:   1/16000     1/250
    // 9:   1/32000     Pulse Width Control
    CY_PULNIX_LIB_API virtual CyResult SetShutterValue( unsigned char  aValue );
    CY_PULNIX_LIB_API virtual CyResult GetShutterValue( unsigned char& aValue ) const;


    // Clock divider
    CY_PULNIX_LIB_API virtual CyResult SetHalfClock( bool  aEnabled );
    CY_PULNIX_LIB_API virtual CyResult GetHalfClock( bool& aEnabled ) const;


    // Scan Mode
    //
    // Warning: make sure that the windowing is smaller than the camera output size.
    typedef enum
    {
        SCAN_NORMAL           = 0,
        SCAN_200              = 1,
        SCAN_100              = 2,
        SCAN_TWO_ROW_BINNING  = 3,
    } ScanMode;
    CY_PULNIX_LIB_API virtual CyResult SetScanMode( ScanMode  aMode );
    CY_PULNIX_LIB_API virtual CyResult GetScanMode( ScanMode& aMode ) const;

    
    // Async Sync Out
    // 
    // true:    The camera outputs continuous data in async mode while the trigger input is high.
    // false:   The camera outputs one frame at each rising edge
    CY_PULNIX_LIB_API virtual CyResult SetAsyncSyncOut( bool  aOneShot );
    CY_PULNIX_LIB_API virtual CyResult GetAsyncSyncOut( bool  aOneShot ) const;


    // Extra parameter
    CY_PULNIX_LIB_API virtual CyResult SetParameter     ( const CyString& aName,
                                                          unsigned char   aValue );
    CY_PULNIX_LIB_API virtual CyResult SetParameter     ( const CyString& aName,
                                                          bool            aValue );
    CY_PULNIX_LIB_API virtual CyResult GetParameter     ( const CyString& aName,
                                                          unsigned char&  aValue ) const;
    CY_PULNIX_LIB_API virtual CyResult GetParameter     ( const CyString& aName,
                                                          bool&           aValue ) const;

private:
    CyResult    SendCommand( const char *   aCommand,
                             unsigned long  aCommandSize,
                             const char*    aOperation );
    CyResult    ReadConfig ( unsigned char* aResponse,
                             unsigned long* aResponseSize );

private:
    // Members
    bool            mAsyncShutterMode;
    unsigned char   mShutterValue;
    bool            mHalfClock;
    ScanMode        mScanMode;
    bool            mAsyncSyncOut;
};


#endif // __CY_PULNIX_TM6710CL_H__