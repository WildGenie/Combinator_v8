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
// File Name....: CyIndigoOmega.h
//
// *****************************************************************************
//
// $Log$
//
// *****************************************************************************

#ifndef __CY_CAMERA_INDIGO_OMEGA_H__
#define __CY_CAMERA_INDIGO_OMEGA_H__

// Headers
/////////////////////////////////////////////////////////////////////////////

// ===== CyCamLib =====
#include "CyIndigoCamera.h"

// Class
/////////////////////////////////////////////////////////////////////////////

class CyIndigoOmega : public CyIndigoCamera
{
public:
    CY_INDIGO_LIB_API            CyIndigoOmega( CyGrabber* aGrabber );
    CY_INDIGO_LIB_API virtual    ~CyIndigoOmega();
};


#endif // __CY_CAMERA_INDIGO_OMEGA_H__


