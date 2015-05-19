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
// File Name....: CySVSVistek4020.h
//
// Description..: Defines the interface of a CameraLink camera.
//
// *****************************************************************************
//
// $Log$
//
// *****************************************************************************

#ifndef __CY_SVS_VISTEK_4020_H__
#define __CY_SVS_VISTEK_4020_H__

// Headers
/////////////////////////////////////////////////////////////////////////////

// ===== This Project =====
#include "CySVSVistekLib.h"
#include "CyCameraLink.h"


// Class
/////////////////////////////////////////////////////////////////////////////

class CySVSVistek4020 : public CyCameraLink
{
// Construction / Destruction
public:
    CY_SVS_VISTEK_LIB_API            CySVSVistek4020( CyGrabber*            aGrabber,
                                                     const CyCameraLimits& aLimits );
    CY_SVS_VISTEK_LIB_API virtual    ~CySVSVistek4020();
 

// Update Camera
protected:
    CY_SVS_VISTEK_LIB_API virtual CyResult InternalUpdate( bool aDeviceReset ) const;
    CY_SVS_VISTEK_LIB_API virtual CyResult LocalUpdate   ( bool aDeviceReset ) const;


// Show Configuration Dialog
protected:
    CY_SVS_VISTEK_LIB_API virtual CyResult AddPropertyPage  ( void* aPropertySheet );
    CY_SVS_VISTEK_LIB_API virtual CyResult OnApply          ( void* aPropertyPage );


// Save/load settings from XML
public:
    CY_SVS_VISTEK_LIB_API virtual CyResult InternalSave ( CyXMLDocument& aDocument ) const;
    CY_SVS_VISTEK_LIB_API virtual CyResult InternalLoad ( CyXMLDocument& aDocument );

    // Camera Information
    CY_SVS_VISTEK_LIB_API virtual CyResult GetVendor       ( CyString& aInfo );
    CY_SVS_VISTEK_LIB_API virtual CyResult GetSerialNumber ( CyString& aInfo );
    CY_SVS_VISTEK_LIB_API virtual CyResult ResetCamera     ( );

private:
    // Members
    CyString     mSerialNumber;

    // Property page
    void*           mPropertyPage;
};


#endif // __CY_SVS_VISTEK_4020_H__