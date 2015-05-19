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
// File Name....: CyBaslerL100K.h
//
// Description..: Basler L100K series ( L101K, L103K and L104K )
//
// *****************************************************************************
//
// $Log$
//
// *****************************************************************************

#ifndef __CY_BASLER_L100K_H__
#define __CY_BASLER_L100K_H__

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

class CyBaslerL100K : public CyCameraLink
{
// Construction / Destruction
public:
    CY_BASLER_LIB_API            CyBaslerL100K( CyGrabber*            aGrabber,
                                                const CyCameraLimits& aLimits,
                                                const CyString&    aName );
    CY_BASLER_LIB_API virtual    ~CyBaslerL100K();


// Update Camera
protected:
    CY_BASLER_LIB_API virtual CyResult InternalUpdate( bool aDeviceReset ) const;
    CY_BASLER_LIB_API virtual CyResult LocalUpdate( bool aDeviceReset ) const;


// Show Configuration Dialog
protected:
    CY_BASLER_LIB_API virtual CyResult AddPropertyPage  ( void* aPropertySheet );
    CY_BASLER_LIB_API virtual CyResult OnApply          ( void* aPropertyPage );


public:
    // Camera Information
    CY_BASLER_LIB_API virtual CyResult GetVendor       ( CyString& aInfo );
    CY_BASLER_LIB_API virtual CyResult GetCameraModel  ( CyString& aInfo );
    CY_BASLER_LIB_API virtual CyResult GetProductID    ( CyString& aInfo );
    CY_BASLER_LIB_API virtual CyResult GetSerialNumber ( CyString& aInfo );
    CY_BASLER_LIB_API virtual CyResult ResetCamera     ( );


private:
    const CyString mName;
    BaslerCam*      mCamera;

    // Property page
    void*           mPropertyPage;
};


#endif // __CY_BASLER_L100K_H__
