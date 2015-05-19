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
// File Name....: CyBaslerA501K.h
//
// Description..: Defines the interface of a CameraLink camera.
//
// *****************************************************************************
//
// $Log$
//
// *****************************************************************************

#ifndef __CY_BASLER_A501K_H__
#define __CY_BASLER_A501K_H__

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

class CyBaslerA501K : public CyCameraLink
{
// Construction / Destruction
public:
    CY_BASLER_LIB_API            CyBaslerA501K( CyGrabber*            aGrabber,
                                                const CyCameraLimits& aLimits );
    CY_BASLER_LIB_API virtual    ~CyBaslerA501K();


// Update Camera
protected:
    CY_BASLER_LIB_API virtual CyResult InternalUpdate( bool aDeviceReset ) const;
    CY_BASLER_LIB_API virtual CyResult LocalUpdate   ( bool aDeviceReset ) const;


public:
    // Camera Information
    CY_BASLER_LIB_API virtual CyResult GetVendor       ( CyString& aInfo );
    CY_BASLER_LIB_API virtual CyResult GetCameraModel  ( CyString& aInfo );
    CY_BASLER_LIB_API virtual CyResult GetProductID    ( CyString& aInfo );
    CY_BASLER_LIB_API virtual CyResult GetSerialNumber ( CyString& aInfo );
    CY_BASLER_LIB_API virtual CyResult ResetCamera     ( );


private:
    const CyString mName;
    BaslerCam*     mCamera;
};


#endif // __CY_BASLER_A501K_H__
