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
// File Name....: CyDalsaSpyder.h
//
// Description..: Defines the interface of a Dalsa Spyder camera.
//
// *****************************************************************************
//
// $Log$
//
// *****************************************************************************

#ifndef __CY_DALSA_SPYDER_H__
#define __CY_DALSA_SPYDER_H__

// Headers
/////////////////////////////////////////////////////////////////////////////

// ===== This Project =====
#include "CyDalsaLib.h"
#include "CyCameraLVDS.h"


// Class
/////////////////////////////////////////////////////////////////////////////

class CyDalsaSpyder : public CyCameraLVDS
{
// Construction / Destruction
public:
    CY_DALSA_LIB_API            CyDalsaSpyder( CyGrabber* aGrabber );
    CY_DALSA_LIB_API virtual    ~CyDalsaSpyder();


// Update Camera
protected:
    CY_DALSA_LIB_API virtual CyResult InternalUpdate( bool aDeviceReset ) const;
    CY_DALSA_LIB_API virtual CyResult LocalUpdate( bool aDeviceReset ) const;

// Show Configuration Dialog
protected:
    CY_DALSA_LIB_API virtual CyResult AddPropertyPage  ( void* aPropertySheet );
    CY_DALSA_LIB_API virtual CyResult OnApply          ( void* aPropertyPage );

private:
    // Property Page
    void*   mPropertyPage;
};

#endif // __CY_DALSA_SPYDER_H__
