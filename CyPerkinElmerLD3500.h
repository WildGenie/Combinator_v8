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
// File Name....: CyCameraPerkinElmer.h
//
// Description..: Defines the basic of a camera implementation based on CameraLink
//
// Implementation Notes: Replace PerkinElmer with the real name
//
//                       This PerkinElmer derives from CameraLink but can be derived
//                       from other camera types, such as CyVideoDecoder or CyCameraLVDS
//
// *****************************************************************************
//
// $Log$
//
// *****************************************************************************

#ifndef __CY_CAMERA_PERKINELMER_H__
#define __CY_CAMERA_PERKINELMER_H__

// Headers
/////////////////////////////////////////////////////////////////////////////

// ===== CyCamLib =====
#include <CyCameraLink.h>

// ===== This Project =====
#include "CyPerkinElmerLib.h"


// Class
/////////////////////////////////////////////////////////////////////////////

class CyPerkinElmerLD3500 : public CyCameraLink
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
    CY_PERKINELMER_LIB_API            CyPerkinElmerLD3500( CyGrabber* aGrabber, bool l8Bit, bool l10Bit );
    CY_PERKINELMER_LIB_API virtual    ~CyPerkinElmerLD3500();
 

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
    CY_PERKINELMER_LIB_API virtual CyResult InternalUpdate( bool aDeviceReset ) const;
    CY_PERKINELMER_LIB_API virtual CyResult LocalUpdate   ( bool aDeviceReset ) const;


//
// Configuration Dialog Methods.
//
//  Parameters are void* that are actually pointers to MFC object.
//      aPropertySheet => CPropertySheet*
//      aPropertyPage  => CPropertyPage* (or a derivation)
//
//  AddPropertyPage:    Overridde to add camera specific controls that are not implemented
//                      in the basic dialog panels (image, etc).
//
//  OnApply:            Override to handle the Apply and/or OK button of the configuration
//                      dialog.  Will be called by all panel, so the class should keep the
//                      pointer of all its panel to handle only the required one.
//
protected:
    CY_PERKINELMER_LIB_API virtual CyResult AddPropertyPage  ( void* aPropertySheet );
    CY_PERKINELMER_LIB_API virtual CyResult OnApply          ( void* aPropertyPage );


    // Camera Information Overrides
    CY_PERKINELMER_LIB_API virtual CyResult GetVendor       ( CyString& aInfo );
    CY_PERKINELMER_LIB_API virtual CyResult GetCameraModel  ( CyString& aInfo );
    CY_PERKINELMER_LIB_API virtual CyResult GetProductID    ( CyString& aInfo );
    CY_PERKINELMER_LIB_API virtual CyResult GetSerialNumber ( CyString& aInfo );
    CY_PERKINELMER_LIB_API virtual CyResult ResetCamera     ( );


//
// Camera Communication utilities.
//
//  For example a camera can be configured through registers, which must following
//  a clearly defined register access protocol.
private:
    virtual CyResult WriteRegister( const char *aAddress,
                                    unsigned char  aValue,
									bool aNumValue = false) const;
    virtual CyResult ReadRegister ( const char *aAddress,
                                    unsigned char& aValue,
									bool aNumValue = false) const;


//
// Members
//

private:
    // Offset override
    unsigned short  mOffsetX;
    unsigned short  mOffsetY;

    // Extra parameters
    float           mGammaCorrection;

    // Property page pointers.  We keep the pointers to the property pages
    // created by this class in order to handle them in OnApply.
    void*           mPropertyPage1;
};


#endif // __CY_CAMERA_PERKINELMER_H__
