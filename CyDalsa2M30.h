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
// File Name....: CyDalsa2M30.h
//
// Description..: Defines the interface of a CameraLink camera.
//
// *****************************************************************************
//
// $Log$
//
// *****************************************************************************

#ifndef __CY_DALSA_2M30_H__
#define __CY_DALSA_2M30_H__

// Headers
/////////////////////////////////////////////////////////////////////////////

// ===== This Project =====
#include "CyDalsaLib.h"
#include "CyDalsaCamera.h"


// Class
/////////////////////////////////////////////////////////////////////////////

class CyDalsa2M30 : public CyDalsaCamera
{
// Construction / Destruction
public:
    CY_DALSA_LIB_API            CyDalsa2M30( CyGrabber* aGrabber );
    CY_DALSA_LIB_API virtual    ~CyDalsa2M30();


// Update Camera
protected:
    CY_DALSA_LIB_API virtual CyResult LocalUpdate( bool aDeviceReset ) const;


// Show Configuration Dialog
protected:
    CY_DALSA_LIB_API virtual CyResult AddPropertyPage  ( void* aPropertySheet );
    CY_DALSA_LIB_API virtual CyResult OnApply          ( void* aPropertyPage );

   
private:
    void*           mPropertyPage; // Property page
    bool            mPhase1_75; // Phase 1.75 and above?
};


#endif // __CY_DALSA_2M30_H__

