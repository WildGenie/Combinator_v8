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
// File Name....: CyDalsaPiranhaHS4x.h
//
// Description..: Defines the interface of a CameraLink camera.
//
// *****************************************************************************
//
// $Log$
//
// *****************************************************************************

#ifndef __CY_DALSA_PiranhaHS4x_H__
#define __CY_DALSA_PiranhaHS4x_H__

// Headers
/////////////////////////////////////////////////////////////////////////////

// ===== This Project =====
#include "CyDalsaLib.h"
#include <CyCameraLink.h>


// Class
/////////////////////////////////////////////////////////////////////////////

class CyDalsaPiranhaHS4x : public CyCameraLink
{
// Types and constants
public:
    // Gain and offset indexes
    CY_DALSA_LIB_API static const unsigned short sAnalogGain1;
    CY_DALSA_LIB_API static const unsigned short sAnalogGain2;
    CY_DALSA_LIB_API static const unsigned short sAnalogGain3;
    CY_DALSA_LIB_API static const unsigned short sAnalogGain4;
    CY_DALSA_LIB_API static const unsigned short sDigitalGain1;
    CY_DALSA_LIB_API static const unsigned short sDigitalGain2;
    CY_DALSA_LIB_API static const unsigned short sDigitalGain3;
    CY_DALSA_LIB_API static const unsigned short sDigitalGain4;
    CY_DALSA_LIB_API static const unsigned short sAnalogOffset1;
    CY_DALSA_LIB_API static const unsigned short sAnalogOffset2;
    CY_DALSA_LIB_API static const unsigned short sAnalogOffset3;
    CY_DALSA_LIB_API static const unsigned short sAnalogOffset4;
    CY_DALSA_LIB_API static const unsigned short sDigitalOffset1;
    CY_DALSA_LIB_API static const unsigned short sDigitalOffset2;
    CY_DALSA_LIB_API static const unsigned short sDigitalOffset3;
    CY_DALSA_LIB_API static const unsigned short sDigitalOffset4;

// Construction / Destruction
public:
    CY_DALSA_LIB_API            CyDalsaPiranhaHS4x( CyGrabber* aGrabber );
    CY_DALSA_LIB_API virtual    ~CyDalsaPiranhaHS4x();


// Update Camera
protected:
    CY_DALSA_LIB_API virtual CyResult InternalUpdate( bool aDeviceReset ) const;
    CY_DALSA_LIB_API virtual CyResult LocalUpdate( bool aDeviceReset ) const;


// Show Configuration Dialog
protected:
    CY_DALSA_LIB_API virtual CyResult AddPropertyPage  ( void* aPropertySheet );
    CY_DALSA_LIB_API virtual CyResult OnApply          ( void* aPropertyPage );


// Save/load settings to a file
protected:
    CY_DALSA_LIB_API virtual CyResult InternalSave ( CyXMLDocument& aDocument ) const; 
    CY_DALSA_LIB_API virtual CyResult InternalLoad ( CyXMLDocument& aDocument );


// Camera Parameter
public:
    // Number of TDI stages
    //
    //  16, 24, 32, 48, 64

    CY_DALSA_LIB_API virtual CyResult SetTDIStages( unsigned char  aStages );
    CY_DALSA_LIB_API virtual CyResult GetTDIStages( unsigned char& aStages ) const;


// Camera Settings
public:
    CY_DALSA_LIB_API virtual CyResult GetVendor       ( CyString& aInfo );
    CY_DALSA_LIB_API virtual CyResult GetCameraModel  ( CyString& aInfo );
    CY_DALSA_LIB_API virtual CyResult GetSerialNumber ( CyString& aInfo );
    CY_DALSA_LIB_API virtual CyResult ResetCamera     ( );

    CY_DALSA_LIB_API virtual CyResult GetTemperature  ( float& aTemp ) const;



// Support of extra parameters
    CY_DALSA_LIB_API virtual CyResult SetParameter     ( const CyString& aName,
                                                         unsigned char   aValue );
    CY_DALSA_LIB_API virtual CyResult GetParameter     ( const CyString& aName,
                                                         unsigned char&  aValue ) const;
    CY_DALSA_LIB_API virtual CyResult GetParameter     ( const CyString& aName,
                                                         float&          aValue ) const;

   
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
    unsigned char   mTDIStages;

    void*           mPropertyPage; // Property page
};


#endif // __CY_DALSA_PiranhaHS4x_H__

