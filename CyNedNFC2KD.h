// *****************************************************************************
//
// $Id$
//
//
// *****************************************************************************
//
//     Copyright (c) 2003, Pleora Technologies Inc., All rights reserved.
//
// *****************************************************************************
//
// File Name....: CyNedNFC2KD.h
//
// Description..: Defines the interface of a CameraLink camera.
//
// *****************************************************************************
//
// $Log$
//
// *****************************************************************************

#ifndef __CY_NED_NFC2KD_CL_H__
#define __CY_NED_NFC2KD_CL_H__

// Headers
/////////////////////////////////////////////////////////////////////////////

// ===== This Project =====
#include "CyNedLib.h"
#include "CyCameraLink.h"


// Class
/////////////////////////////////////////////////////////////////////////////

class CyNedNFC2KD: public CyCameraLink
{
// Construction / Destruction
public:
    CY_NED_LIB_API            CyNedNFC2KD( CyGrabber* aGrabber );
    CY_NED_LIB_API virtual    ~CyNedNFC2KD();
 

// Update Camera
protected:
    CY_NED_LIB_API virtual CyResult InternalUpdate( bool aDeviceReset ) const;
    CY_NED_LIB_API virtual CyResult LocalUpdate   ( bool aDeviceReset ) const;


// Show Configuration Dialog
protected:
    CY_NED_LIB_API virtual CyResult AddPropertyPage  ( void* aPropertySheet );
    CY_NED_LIB_API virtual CyResult OnApply          ( void* aPropertyPage );

private:
    // Property page
    void*           mPropertyPage;
};


#endif // __CY_NED_NFC2KD_CL_H__
