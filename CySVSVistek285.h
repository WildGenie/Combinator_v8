// *****************************************************************************
//
// $Id$
//
// cy1h07b1
//
// *****************************************************************************
//
//     Copyright (c) 2003, Pleora Technologies Inc., All rights reserved.
//
// *****************************************************************************
//
// File Name....: CySVSVistek285.h
//
// Description..: Defines the interface of a CameraLink camera.
//
// *****************************************************************************
//
// $Log$
//
// *****************************************************************************

#ifndef __CY_SVS_VISTEK_285_H__
#define __CY_SVS_VISTEK_285_H__

// Headers
/////////////////////////////////////////////////////////////////////////////

// ===== This Project =====
#include "CySVSVistekLib.h"
#include "CyCameraLink.h"


// Class
/////////////////////////////////////////////////////////////////////////////

class CySVSVistek285 : public CyCameraLink
{
public:
	    // Gains indexes
    CY_SVS_VISTEK_LIB_API static const unsigned short sGain;
    CY_SVS_VISTEK_LIB_API static const unsigned short sOffset;

// Construction / Destruction
public:
    CY_SVS_VISTEK_LIB_API            CySVSVistek285( CyGrabber*            aGrabber,
                                                     const CyCameraLimits& aLimits,
                                                     const CyString&       aName );
    CY_SVS_VISTEK_LIB_API virtual    ~CySVSVistek285();
 

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
    CY_SVS_VISTEK_LIB_API virtual CyResult InternalUpdate( bool aDeviceReset ) const;
#else
    CY_SVS_VISTEK_LIB_API virtual CyResult InternalUpdate( ) const;
#endif
    CY_SVS_VISTEK_LIB_API virtual CyResult LocalUpdate   ( bool aDeviceReset ) const;


//
// Overridden Parameters
//
    // Camera Information, implement only if camera supports it
    CY_SVS_VISTEK_LIB_API virtual CyResult GetVendor       ( CyString& aInfo );
    CY_SVS_VISTEK_LIB_API virtual CyResult GetCameraModel  ( CyString& aInfo );
    CY_SVS_VISTEK_LIB_API virtual CyResult GetProductID    ( CyString& aInfo );
    CY_SVS_VISTEK_LIB_API virtual CyResult GetSerialNumber ( CyString& aInfo );
    CY_SVS_VISTEK_LIB_API virtual CyResult ResetCamera     ( );

private:
    // Members
    CyString    mSerialNumber;
	CyString    mCameraName;
};


#endif // __CY_SVS_VISTEK_285_H__