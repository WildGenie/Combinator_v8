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
// File Name....: CyDalsa1M28.h
//
// Description..: Defines the interface of a CameraLink camera.
//
// *****************************************************************************
//
// $Log$
//
// *****************************************************************************

#ifndef __CY_DALSA_1M28_H__
#define __CY_DALSA_1M28_H__

// Headers
/////////////////////////////////////////////////////////////////////////////

// ===== This Project =====
#include "CyDalsaLib.h"
#include "..\..\cy1c23b1\Includes\CyPhotonFocusCamera.h"


// Class
/////////////////////////////////////////////////////////////////////////////

class CyDalsa1M28 : public CyPhotonFocusCamera
{
// Construction / Destruction
public:
    CY_DALSA_LIB_API            CyDalsa1M28( CyGrabber*            aGrabber,
                                             const CyCameraLimits& aLimits,
                                             const CyString&       aName,
                                             bool                  aEvenParity = false );
    CY_DALSA_LIB_API virtual    ~CyDalsa1M28();
};


#endif // __CY_DALSA_1M28_H__

