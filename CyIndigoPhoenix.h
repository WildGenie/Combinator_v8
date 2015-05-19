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
// File Name....: CyIndigoPhoenix.h
//
// *****************************************************************************
//
// $Log$
//
// *****************************************************************************

#ifndef __CY_CAMERA_INDIGO_PHOENIX_H__
#define __CY_CAMERA_INDIGO_PHOENIX_H__

// Headers
/////////////////////////////////////////////////////////////////////////////

// ===== CyCamLib =====
#include "CyIndigoCamera.h"

// Class
/////////////////////////////////////////////////////////////////////////////

class CyIndigoPhoenix : public CyIndigoCamera
{
public:
    CY_INDIGO_LIB_API            CyIndigoPhoenix( CyGrabber* aGrabber );
    CY_INDIGO_LIB_API virtual    ~CyIndigoPhoenix();
};


#endif // __CY_CAMERA_INDIGO_PHOENIX_H__

