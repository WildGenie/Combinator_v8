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
// File Name....: CyNeuricamCLinkCam.h
//
// Description..: Defines the basic of a camera implementation based on CameraLink
//
// *****************************************************************************
//
// $Log$
//
// *****************************************************************************

#ifndef __CY_NEURICAM_CLINKCAM_H__
#define __CY_NEURICAM_CLINKCAM_H__

// Headers
/////////////////////////////////////////////////////////////////////////////

// ===== CyCamLib =====
#include <CyCameraLink.h>

// ===== This Project =====
#include "CyNeuricamLib.h"


// Class
/////////////////////////////////////////////////////////////////////////////

class CyNeuricamCLinkCam: public CyCameraLink
{
//
// Types and constants
//
    // VRef, Vprec, Vcm and Vbg are saved as gains, with the following indexes:

    CY_NEURICAM_LIB_API static const unsigned short sVREFGainIndex;
    CY_NEURICAM_LIB_API static const unsigned short sVPRECGainIndex;
    CY_NEURICAM_LIB_API static const unsigned short sVCMGainIndex;
    CY_NEURICAM_LIB_API static const unsigned short sVBGGainIndex;

//
// Construction / Destruction
//
public:
    CY_NEURICAM_LIB_API            CyNeuricamCLinkCam( CyGrabber* aGrabber );
    CY_NEURICAM_LIB_API virtual    ~CyNeuricamCLinkCam();
 

//
// Camera Update Methods
//
protected:
#if defined (COYOTE_SDK_VERSION) & ( COYOTE_SDK_VERSION >= 0210 )
    CY_NEURICAM_LIB_API virtual CyResult InternalUpdate( bool aDeviceReset ) const;
#else
    CY_NEURICAM_LIB_API virtual CyResult InternalUpdate( ) const;
#endif
    CY_NEURICAM_LIB_API virtual CyResult LocalUpdate   ( bool aDeviceReset ) const;


//
// Configuration Dialog Methods.
//
protected:
    CY_NEURICAM_LIB_API virtual CyResult AddPropertyPage  ( void* aPropertySheet );
    CY_NEURICAM_LIB_API virtual CyResult OnApply          ( void* aPropertyPage );



//
// XML Storage methods.
//
protected:
    CY_NEURICAM_LIB_API virtual CyResult InternalSave ( CyXMLDocument& aDocument ) const;
    CY_NEURICAM_LIB_API virtual CyResult InternalLoad ( CyXMLDocument& aDocument );



//
// Camera specific settings
//
public:
    // When in single shot, the camera need to be triggered by sending
    // 0x16 on the serial port
    CY_NEURICAM_LIB_API virtual CyResult SetSingleShot( bool  aEnable );
    CY_NEURICAM_LIB_API virtual CyResult GetSingleShot( bool& aEnable ) const;

    // Send a frame in single shot mode
    CY_NEURICAM_LIB_API virtual CyResult TriggerSingleShot() const;

    // Extra parameter
    CY_NEURICAM_LIB_API virtual CyResult SetParameter     ( const CyString& aName,
                                                            bool               aValue );
    CY_NEURICAM_LIB_API virtual CyResult GetParameter     ( const CyString& aName,
                                                            bool&              aValue ) const;

    // camera information
    CY_NEURICAM_LIB_API virtual CyResult GetProductID    ( CyString& aInfo );
    CY_NEURICAM_LIB_API virtual CyResult ResetCamera     ( );

//
// Members
//

private:
    bool    mSingleShot;

    // Property page pointer.
    void*   mPropertyPage;
};


#endif // __CY_NEURICAM_CLINKCAM_H__
