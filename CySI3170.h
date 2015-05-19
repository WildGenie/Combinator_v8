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
// File Name....: CySI3170.h
//
// Description..: Defines the interface of a CameraLink camera.
//
// *****************************************************************************
//
// $Log$
//
// *****************************************************************************

#ifndef __CY_SI3170_H__
#define __CY_SI3170_H__

// Headers
/////////////////////////////////////////////////////////////////////////////

// ===== This Project =====
#include "CySiliconImagingLib.h"
#include "CyCameraLink.h"


// Forward-Declaration
/////////////////////////////////////////////////////////////////////////////


// Class
/////////////////////////////////////////////////////////////////////////////

class CySI3170 : public CyCameraLink
{
// Constants
public:
    CY_SI_LIB_API static const unsigned short sGlobalGainIndex;
    CY_SI_LIB_API static const unsigned short sRedGainIndex;
    CY_SI_LIB_API static const unsigned short sBlueGainIndex;
    CY_SI_LIB_API static const unsigned short sGreenGainIndex;


// Construction / Destruction
public:
    CY_SI_LIB_API            CySI3170( CyGrabber* aGrabber );
    CY_SI_LIB_API virtual    ~CySI3170();


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
    // Clock rate of the camera.
    CY_SI_LIB_API virtual CyResult SetClockRate( float  aRate );
    CY_SI_LIB_API virtual CyResult GetClockRate( float& aRate ) const;

    // Support of extra parameters
    CY_SI_LIB_API virtual CyResult SetParameter     ( const CyString& aName,
                                                      float              aValue );
    CY_SI_LIB_API virtual CyResult GetParameter     ( const CyString& aName,
                                                      float&             aValue ) const;


private:
    float           mClockRate;

    // Property page
    void*           mPropertyPage;
};


#endif // __CY_CySI3170_H__
