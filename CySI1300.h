// *****************************************************************************
//
// $Id$
//
// cy1h22b1
//
// *****************************************************************************
//
//     Copyright (c) 2003, Pleora Technologies Inc., All rights reserved.
//
// *****************************************************************************
//
// File Name....: CySI1300.h
//
// Description..: Defines the interface of a CameraLink camera.
//
// *****************************************************************************
//
// $Log$
//
// *****************************************************************************

#ifndef __CY_SI1300_H__
#define __CY_SI1300_H__

// Headers
/////////////////////////////////////////////////////////////////////////////

// ===== This Project =====
#include "CySiliconImagingLib.h"
#include "CyCameraLink.h"


// Forward-Declaration
/////////////////////////////////////////////////////////////////////////////


// Class
/////////////////////////////////////////////////////////////////////////////

class CySI1300 : public CyCameraLink
{
// Constants
public:
    CY_SI_LIB_API static const unsigned short sRedGainIndex;
    CY_SI_LIB_API static const unsigned short sBlueGainIndex;
    CY_SI_LIB_API static const unsigned short sGreen1GainIndex;
    CY_SI_LIB_API static const unsigned short sGreen2GainIndex;


// Construction / Destruction
public:
    CY_SI_LIB_API            CySI1300( CyGrabber*            aGrabber,
                                       const CyCameraLimits& aLimits,
                                       bool                  aColour,
                                       bool                  a3300 );
    CY_SI_LIB_API virtual    ~CySI1300();


// Update Camera
protected:
    CY_SI_LIB_API virtual CyResult InternalUpdate( bool aDeviceReset ) const;
    CY_SI_LIB_API virtual CyResult LocalUpdate( bool aDeviceReset ) const;


// Show Configuration Dialog
protected:
    CY_SI_LIB_API virtual CyResult AddPropertyPage  ( void* aPropertySheet );
    CY_SI_LIB_API virtual CyResult OnApply          ( void* aPropertyPage );


// Save/load settings from XML
public:
    CY_SI_LIB_API virtual CyResult InternalSave ( CyXMLDocument& aDocument ) const;
    CY_SI_LIB_API virtual CyResult InternalLoad ( CyXMLDocument& aDocument );


public:
    // Override the Offset, because we will set it on the camera and
    // not use in on the module
    CY_SI_LIB_API virtual CyResult SetOffsetX( unsigned short  aOffset );
    CY_SI_LIB_API virtual CyResult GetOffsetX( unsigned short& aOffset ) const;
    CY_SI_LIB_API virtual CyResult SetOffsetY( unsigned short  aOffset );
    CY_SI_LIB_API virtual CyResult GetOffsetY( unsigned short& aOffset ) const;

    // Clock rate of the camera.
    CY_SI_LIB_API virtual CyResult SetClockRate( float  aRate );
    CY_SI_LIB_API virtual CyResult GetClockRate( float& aRate ) const;

    // Support of extra parameters
    CY_SI_LIB_API virtual CyResult SetParameter( const CyString& aName,
                                                 float              aValue );
    CY_SI_LIB_API virtual CyResult GetParameter( const CyString& aName,
                                                 float&             aValue ) const;

private:
    // Camera commands
    CY_SI_LIB_API virtual CyResult SendCommand( const char * aCommand, unsigned long aCommandSize ) const;


private:
    bool            mColour;
    bool            m3300;
    unsigned short  mOffsetX;
    unsigned short  mOffsetY;
    float           mClockRate;

    // Property page
    void*           mPropertyPage;
};


#endif // __CY_CySI1300_H__
