// *****************************************************************************
//
// $Id$
//
// cy1h08b1
//
// *****************************************************************************
//
//     Copyright (c) 2003, Pleora Technologies Inc., All rights reserved.
//
// *****************************************************************************
//
// File Name....: CyDalsaCamera.h
//
// Description..: Defines the interface of a basic dalsa camera CameraLink camera.
//
// *****************************************************************************
//
// $Log$
//
// *****************************************************************************

#ifndef __CY_DALSA_CAMERA_H__
#define __CY_DALSA_CAMERA_H__

// Headers
/////////////////////////////////////////////////////////////////////////////

// ===== This Project =====
#include "CyDalsaLib.h"
#include "CyCameraLink.h"


// Class
/////////////////////////////////////////////////////////////////////////////

class CyDalsaCamera : public CyCameraLink
{
// Construction / Destruction
protected:
    CY_DALSA_LIB_API            CyDalsaCamera( CyGrabber* aGrabber, const CyCameraLimits& aLimits );
    CY_DALSA_LIB_API virtual    ~CyDalsaCamera();


// Update Camera
protected:
    CY_DALSA_LIB_API virtual CyResult InternalUpdate( bool aDeviceReset ) const;
    CY_DALSA_LIB_API virtual CyResult LocalUpdate( bool aDeviceReset ) const = 0;


// Save/load settings to a file
protected:
    CY_DALSA_LIB_API virtual CyResult InternalSave ( CyXMLDocument& aDocument ) const; 
    CY_DALSA_LIB_API virtual CyResult InternalLoad ( CyXMLDocument& aDocument );


// Camera Settings
public:
    CY_DALSA_LIB_API virtual CyResult GetVendor       ( CyString& aInfo );
    CY_DALSA_LIB_API virtual CyResult GetCameraModel  ( CyString& aInfo );
    CY_DALSA_LIB_API virtual CyResult GetSerialNumber ( CyString& aInfo );
    CY_DALSA_LIB_API virtual CyResult ResetCamera     ( );

    // When in free run and external sync mode, it is possible to force the 
    // exposure time to the maximum time possible.
    CY_DALSA_LIB_API virtual CyResult SetMaximumExposureTime( bool  aEnabled );
    CY_DALSA_LIB_API virtual CyResult GetMaximumExposureTime( bool& aEnabled ) const;

    // Set the exposure time decimal.
    // The CyCameraInterface::SetExposureTime unit is microseconds and that
    // the Dalsa camera's support decimals for microseconds.
    // The Get/SetExposureTimeDecimal methods are use to set the decimal value
    // of the exposure time.
    CY_DALSA_LIB_API virtual CyResult SetExposureTimeDecimal( unsigned long  aValue );
    CY_DALSA_LIB_API virtual CyResult GetExposureTimeDecimal( unsigned long& aValue ) const;


    // Read the temperature from the camera
    CY_DALSA_LIB_API virtual CyResult GetTemperature( float& aTemp ) const;


    // Calibrate gain and offset, gains and offsets will be computed when the
    // value is set to true.  When it is true, the SetGain and SetOffset will
    // have no effect on theses values.

    CY_DALSA_LIB_API virtual CyResult SetAutomaticGainCalibration( bool           aEnabled, 
                                                                   unsigned short aTap,
                                                                   unsigned short aValue,
                                                                   unsigned long  aTimeOut );
    CY_DALSA_LIB_API virtual CyResult GetAutomaticGainCalibration( bool& aEnabled ) const;

    CY_DALSA_LIB_API virtual CyResult SetAutomaticOffsetCalibration( bool           aEnabled, 
                                                                     unsigned short aTap,
                                                                     unsigned short aValue,
                                                                     unsigned long  aTimeOut );
    CY_DALSA_LIB_API virtual CyResult GetAutomaticOffsetCalibration( bool& aEnabled ) const;

    CY_DALSA_LIB_API virtual CyResult GetCameraGains( double& aGain1,
                                                      double& aGain2 ) const;
    CY_DALSA_LIB_API virtual CyResult GetCameraOffsets( unsigned short& aOffset1,
                                                        unsigned short& aOffset2 ) const;


// Support of extra parameters
    CY_DALSA_LIB_API virtual CyResult SetParameter     ( const CyString& aName,
                                                         bool               aValue );
    CY_DALSA_LIB_API virtual CyResult SetParameter     ( const CyString& aName,
                                                         unsigned long      aValue );
    CY_DALSA_LIB_API virtual CyResult GetParameter     ( const CyString& aName,
                                                         bool&              aValue ) const;
    CY_DALSA_LIB_API virtual CyResult GetParameter     ( const CyString& aName,
                                                         unsigned long&     aValue ) const;
    CY_DALSA_LIB_API virtual CyResult GetParameter     ( const CyString& aName,
                                                         float&             aValue ) const;

    
// Utilities
protected:
    static void GetDataFromString( const CyString& aString,
                                   CyString&       aData );
    static void GetDataFromString( const CyString&  aString,
                                   unsigned char& aData );
    static void GetDataFromString( const CyString&   aString,
                                   unsigned short& aData );
    static CyResult ExtractInformation( const CyString& aData,
                                        const CyString& aTag,
                                        CyString&       aResult );

    CyResult ReadResponse( CyString& aResponse, unsigned int aTimeout, bool aIgnoreResponse = false ) const;

    
private:
    // Members
    bool mMaximumExposureTime;
    bool mAutomaticGainCalibration;
    bool mAutomaticOffsetCalibration;
    unsigned long mExposureTimeDecimal;
};


#endif // __CY_DALSA_CAMERA_H__

