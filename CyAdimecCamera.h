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
// File Name....: CyAdimecCamera.h
//
// Description..: Defines the basic of a camera implementation based on CameraLink
//
// *****************************************************************************
//
// $Log$
//
// *****************************************************************************

#ifndef __CY_CAMERA_ADIMEC_H__
#define __CY_CAMERA_ADIMEC_H__

// Headers
/////////////////////////////////////////////////////////////////////////////

// ===== CyCamLib =====
#include <CyCameraLink.h>

// ===== This Project =====
#include "CyAdimecLib.h"


// Class
/////////////////////////////////////////////////////////////////////////////

class CyAdimecCamera : public CyCameraLink
{
//
// Construction / Destruction
//
public:
    CY_ADIMEC_LIB_API            CyAdimecCamera( CyGrabber* aGrabber, const CyCameraLimits& aLimits );
    CY_ADIMEC_LIB_API virtual    ~CyAdimecCamera();
 

//
// Camera Communication utilities
//
protected:
    CyResult WriteCommand( const char*  aCommand, const char* aUser ) const;
    CyResult ReadCommand ( const char*  aCommand,
                           int&         aValue,
                           const char*  aUser ) const;
    CyResult ReadCommand ( const char*  aCommand,
                           int&         aValue1,
                           int&         aValue2,
                           const char*  aUser ) const;
    CyResult ReadCommand ( const char*  aCommand,
                           int&         aValue1,
                           int&         aValue2,
                           int&         aValue3,
                           const char*  aUser ) const;
    CyResult ReadCommand ( const char*  aCommand,
                           CyString& aValue,
                           const char*  aUser ) const;
};


#endif // __CY_CAMERA_ADIMEC_H__
