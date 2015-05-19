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
// File Name....: CyNEDN3CL2048DCL.h
//
// Description..: Implementation of the NED N3CL2048DCL camera
//
//
// *****************************************************************************
//
// $Log$
//
// *****************************************************************************

#ifndef __CY_CAMERA_TEMPLATE_H__
#define __CY_CAMERA_TEMPLATE_H__

// Headers
/////////////////////////////////////////////////////////////////////////////

// ===== CyCamLib =====
#include <CyCameraLink.h>

// ===== This Project =====
#include "CyNedLib.h"


// Class
/////////////////////////////////////////////////////////////////////////////

class CyNEDN3CL2048DCL : public CyCameraLink
{
//
// Types
//
public:
    // Gains indexes
    CY_NED_LIB_API static const unsigned short sRedGain;
    CY_NED_LIB_API static const unsigned short sGreenGain;
    CY_NED_LIB_API static const unsigned short sBlueGain;

    // Offsets indexes
    CY_NED_LIB_API static const unsigned short sRedOffset;
    CY_NED_LIB_API static const unsigned short sGreenOffset;
    CY_NED_LIB_API static const unsigned short sBlueOffset;


//
// Construction / Destruction
//
public:
    CY_NED_LIB_API            CyNEDN3CL2048DCL( CyGrabber* aGrabber );
    CY_NED_LIB_API virtual    ~CyNEDN3CL2048DCL();
 

//
// Camera Update Methods
//
protected:
    CY_NED_LIB_API virtual CyResult InternalUpdate( bool aDeviceReset ) const;
    CY_NED_LIB_API virtual CyResult LocalUpdate   ( bool aDeviceReset ) const;


//
// Configuration Dialog Methods.
//
protected:
    CY_NED_LIB_API virtual CyResult AddPropertyPage  ( void* aPropertySheet );
    CY_NED_LIB_API virtual CyResult OnApply          ( void* aPropertyPage );


//
// CyCameraInterface overrides
//
    CY_NED_LIB_API virtual CyResult ResetCamera( );



//
// Members
//

private:
    // Property page pointers.
    void*           mPropertyPage;
};


#endif // __CY_CAMERA_TEMPLATE_H__
