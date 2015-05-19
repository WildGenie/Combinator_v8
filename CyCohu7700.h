// *****************************************************************************
//
// $Id$
//
// cy1h12b1
//
// *****************************************************************************
//
//     Copyright (c) 2003, Pleora Technologies Inc., All rights reserved.
//
// *****************************************************************************
//
// File Name....: CyCohu7700.h
//
// Description..: Defines the interface of a CameraLink camera.
//
// *****************************************************************************
//
// $Log$
//
// *****************************************************************************

#ifndef __CY_COHU_7700_H__
#define __CY_COHU_7700_H__

// Headers
/////////////////////////////////////////////////////////////////////////////

// ===== This Project =====
#include "CyCohuLib.h"
#include "CyCameraLink.h"


// Forward-Declaration
/////////////////////////////////////////////////////////////////////////////

class CohuCam;


// Class
/////////////////////////////////////////////////////////////////////////////

class CyCohu7700 : public CyCameraLink
{
// Construction / Destruction
public:
    CY_COHU_LIB_API            CyCohu7700( CyGrabber* aGrabber );
    CY_COHU_LIB_API virtual    ~CyCohu7700();

// Update Camera
protected:
    CY_COHU_LIB_API virtual CyResult InternalUpdate( bool aDeviceReset ) const;
    CY_COHU_LIB_API virtual CyResult LocalUpdate( bool aDeviceReset ) const;


// Show Configuration Dialog
protected:
    CY_COHU_LIB_API virtual CyResult AddPropertyPage  ( void* aPropertySheet );
    CY_COHU_LIB_API virtual CyResult OnApply          ( void* aPropertyPage );


// Save/load settings from XML
public:
    CY_COHU_LIB_API virtual CyResult InternalSave ( CyXMLDocument& aDocument ) const;
    CY_COHU_LIB_API virtual CyResult InternalLoad ( CyXMLDocument& aDocument );

public:
    // Override the Y Offset, because we will set it on the camera and
    // not use in on the module
    CY_COHU_LIB_API virtual CyResult SetOffsetY( unsigned short  aOffset );
    CY_COHU_LIB_API virtual CyResult GetOffsetY( unsigned short& aOffset ) const;

    // Camera Information
    CY_COHU_LIB_API virtual CyResult GetProductID    ( CyString& aInfo );
    CY_COHU_LIB_API virtual CyResult ResetCamera     ( );

private:
    CohuCam* mCamera;
    unsigned short  mOffsetY;

    // Property page
    void*           mPropertyPage;
};


#endif // __CY_COHU_7700_H__
