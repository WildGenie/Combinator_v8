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
// File Name....: CyImperXVGA210.h
//
// Description..: Defines the basic of a camera implementation based on CameraLink
//
//
// *****************************************************************************
//
// $Log$
//
// *****************************************************************************

#ifndef __CY_CAMERA_IMPERX_H__
#define __CY_CAMERA_IMPERX_H__

// Headers
/////////////////////////////////////////////////////////////////////////////

// ===== CyCamLib =====
#include <CyCameraLink.h>

// ===== This Project =====
#include "CyImperXLib.h"


// Class
/////////////////////////////////////////////////////////////////////////////

class CyImperXVGA210 : public CyCameraLink
{
//
// Types
//
//  Here we can define types and constants that are important to this camera.
//  One example is the gains for the camera.  The base CyCameraInterface can
//  save gains associated with an index, here we can force a meaning to an index.
//
public:

//
// Construction / Destruction
//
public:
    CY_IMPERX_LIB_API            CyImperXVGA210( CyGrabber* aGrabber );
    CY_IMPERX_LIB_API virtual    ~CyImperXVGA210();
 

//
// Camera Update Methods
//
//  InternalUpdate: Override if settings must be sent to camera using its protocol,
//                  when UpdateToCamera is invoked.
//
//  LocalUpdate (optional): All camera communications can be implemented in this
//                          method, which can be used by OnApply to send camera 
//                          settings while in the configuration dialog.
protected:
#if defined (COYOTE_SDK_VERSION) & ( COYOTE_SDK_VERSION >= 0210 )
    CY_IMPERX_LIB_API virtual CyResult InternalUpdate( bool aDeviceReset ) const;
#else
    CY_IMPERX_LIB_API virtual CyResult InternalUpdate( ) const;
#endif
    CY_IMPERX_LIB_API virtual CyResult LocalUpdate   ( bool aDeviceReset ) const;


//
// Extra parameters.
//


//
// Camera Communication utilities.
//
//  For example a camera can be configured through registers, which must following
//  a clearly defined register access protocol.
private:
    virtual CyResult WriteRegister( unsigned char   aAddressLow,
		                            unsigned char   aAddressHigh,
		                            unsigned char   aRegLen,
                                    unsigned short  aValue ) const;

    virtual CyResult ReadRegister ( unsigned char   aAddressLow,
		                            unsigned char   aAddressHigh,
		                            unsigned char   aRegLen,
                                    unsigned short& aValue ) const;
};


#endif // __CY_CAMERA_IMPERX_H__
