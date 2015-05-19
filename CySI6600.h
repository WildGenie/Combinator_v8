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
// File Name....: CySI6600.h
//
// Description..: Defines the interface of a CameraLink camera.
//
// *****************************************************************************
//
// $Log$
//
// *****************************************************************************

#ifndef __CY_SI6600_H__
#define __CY_SI6600_H__

// Headers
/////////////////////////////////////////////////////////////////////////////

// ===== This Project =====
#include "CySiliconImagingLib.h"
#include "CyCameraLink.h"


// Forward-Declaration
/////////////////////////////////////////////////////////////////////////////


// Class
/////////////////////////////////////////////////////////////////////////////

class CySI6600 : public CyCameraLink
{
// Construction / Destruction
public:
    CY_SI_LIB_API            CySI6600( CyGrabber* aGrabber );
    CY_SI_LIB_API virtual    ~CySI6600();


// Update Camera
protected:
    CY_SI_LIB_API virtual CyResult InternalUpdate( bool aDeviceReset ) const;
    CY_SI_LIB_API virtual CyResult LocalUpdate   ( bool aDeviceReset ) const;
};


#endif // __CY_CySI6600_H__
