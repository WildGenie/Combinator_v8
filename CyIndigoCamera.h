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
// File Name....: CyIndigoCamera.h
//
// *****************************************************************************
//
// $Log$
//
// *****************************************************************************

#ifndef __CY_CAMERA_INDIGO_H__
#define __CY_CAMERA_INDIGO_H__

// Headers
/////////////////////////////////////////////////////////////////////////////

// ===== CyCamLib =====
#include <CyCameraLVDS.h>

// ===== This Project =====
#include "CyIndigoLib.h"


// Class
/////////////////////////////////////////////////////////////////////////////

class CyIndigoCamera : public CyCameraLVDS
{
//
// Construction / Destruction
//
public:
    CY_INDIGO_LIB_API            CyIndigoCamera( CyGrabber*            aGrabber,
                                                 const CyCameraLimits& aLimits );
    CY_INDIGO_LIB_API virtual    ~CyIndigoCamera();
 

//
// Accessors
//
    typedef enum
    {
        INDIGO_UNKNOWN              = 0,
        INDIGO_PHOENIX              = 1,    // deprecated
        INDIGO_OMEGA                = 2,    // deprecated
        INDIGO_MERLIN_II            = 3,   // deprecated

        INDIGO_PARALLEL_CAMERA      = 1,
        INDIGO_SERIAL_CAMERA_SINGLE = 2,
        INDIGO_SERIAL_CAMERA_DUAL   = 3
    } CameraType;

    CY_INDIGO_LIB_API CameraType GetCameraType() const;
    CY_INDIGO_LIB_API CameraType GetCameraType( const CyChannel& aChannel ) const;



//
// Configuration Dialog Methods.
//
protected:
    CY_INDIGO_LIB_API virtual CyResult AddPropertyPage  ( void* aPropertySheet );
};

#endif // __CY_CAMERA_INDIGO_H__


