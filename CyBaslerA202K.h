// *****************************************************************************
//
// $Id$
//
// cy1c01b1
//
// *****************************************************************************
//
//     Copyright (c) 2003, Pleora Technologies Inc., All rights reserved.
//
// *****************************************************************************
//
// File Name....: CyBaslerA202K.h
//
// Description..: Defines the interface of a CameraLink camera.
//
// *****************************************************************************
//
// $Log$
//
// *****************************************************************************

#ifndef __CY_BASLER_A202K_H__
#define __CY_BASLER_A202K_H__

// Headers
/////////////////////////////////////////////////////////////////////////////

// ===== This Project =====
#include "CyBaslerLib.h"
#include "CyCameraLink.h"


// Forward-Declaration
/////////////////////////////////////////////////////////////////////////////

class BaslerCam;


// Class
/////////////////////////////////////////////////////////////////////////////

class CyBaslerA202K : public CyCameraLink
{
// Construction / Destruction
public:
    CY_BASLER_LIB_API            CyBaslerA202K( CyGrabber* aGrabber,
                                                const CyCameraLimits& aLimits,
                                                const CyString&     aName );
    CY_BASLER_LIB_API virtual    ~CyBaslerA202K();


// Update Camera
protected:
    CY_BASLER_LIB_API virtual CyResult InternalUpdate( bool aDeviceReset ) const;
    CY_BASLER_LIB_API virtual CyResult LocalUpdate( bool aDeviceReset ) const;


// Show Configuration Dialog
protected:
    CY_BASLER_LIB_API virtual CyResult AddPropertyPage  ( void* aPropertySheet );
    CY_BASLER_LIB_API virtual CyResult OnApply          ( void* aPropertyPage );


// Save/load settings from XML
public:
    CY_BASLER_LIB_API virtual CyResult InternalSave ( CyXMLDocument& aDocument ) const;
    CY_BASLER_LIB_API virtual CyResult InternalLoad ( CyXMLDocument& aDocument );


public:
    // Override the Offset, because we will set it on the camera and
    // not use in on the module
    CY_BASLER_LIB_API virtual CyResult SetOffsetX( unsigned short  aOffset );
    CY_BASLER_LIB_API virtual CyResult GetOffsetX( unsigned short& aOffset ) const;
    CY_BASLER_LIB_API virtual CyResult SetOffsetY( unsigned short  aOffset );
    CY_BASLER_LIB_API virtual CyResult GetOffsetY( unsigned short& aOffset ) const;

    // Camera Information
    CY_BASLER_LIB_API virtual CyResult GetVendor       ( CyString& aInfo );
    CY_BASLER_LIB_API virtual CyResult GetCameraModel  ( CyString& aInfo );
    CY_BASLER_LIB_API virtual CyResult GetProductID    ( CyString& aInfo );
    CY_BASLER_LIB_API virtual CyResult GetSerialNumber ( CyString& aInfo );
    CY_BASLER_LIB_API virtual CyResult ResetCamera     ( );


private:
    const CyString mName;
    BaslerCam*      mCamera;
    unsigned short  mSizeY;
    unsigned short  mOffsetX;
    unsigned short  mOffsetY;

    // Property page
    void*           mPropertyPage;
};


#endif // __CY_BASLER_A202K_H__
