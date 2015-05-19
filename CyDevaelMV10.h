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
// File Name....: CyDevaelCamera.h
//
// Description..: Defines the implementation of the Devael Cameras
//
// *****************************************************************************
//
// $Log$
//
// *****************************************************************************

#ifndef __CY_DEVAEL_CAMERA_H__
#define __CY_DEVAEL_CAMERA_H__

// Headers
/////////////////////////////////////////////////////////////////////////////

// ===== CyCamLib =====
#include <CyCameraLink.h>

// ===== This Project =====
#include "CyDevaelLib.h"


// Class
/////////////////////////////////////////////////////////////////////////////

class CyDevaelMV10 : public CyCameraLink
{
//
// Types
public:
    // Gains indexes
    CY_DEVAEL_LIB_API static const unsigned short sPixelGain;


//
// Construction / Destruction
//
public:
    CY_DEVAEL_LIB_API            CyDevaelMV10( CyGrabber* aGrabber );
    CY_DEVAEL_LIB_API virtual    ~CyDevaelMV10();
 

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
    CY_DEVAEL_LIB_API virtual CyResult InternalUpdate( bool aDeviceReset ) const;
    CY_DEVAEL_LIB_API virtual CyResult LocalUpdate   ( bool aDeviceReset ) const;


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
    CY_DEVAEL_LIB_API virtual CyResult AddPropertyPage  ( void* aPropertySheet );
    CY_DEVAEL_LIB_API virtual CyResult OnApply          ( void* aPropertyPage );



//
// XML Storage methods.
//
//  InternalSave:  Overridden if this camera must save its own settings in the XML document.
//                 Invoked by SaveToXML
//  InternalLoad:  Overridden if this camera must load its own settings from the XML document
//                 Invoked by LoadFromXML
//
protected:
    CY_DEVAEL_LIB_API virtual CyResult InternalSave ( CyXMLDocument& aDocument ) const;
    CY_DEVAEL_LIB_API virtual CyResult InternalLoad ( CyXMLDocument& aDocument );



//
// Overridden Parameters
//
//  Some parameters can be stored on the camera and can be ignored by the iPORT.
//  One such example is the windowing offset, which can be applied only on the camera.
//
//  In this case, we will save the offset on the camera and force 0 on the iPORT.
//
//  We need to have local attributes (variables) because the base class will always be 0.
//
    // Camera Information Overrides
    CY_DEVAEL_LIB_API virtual CyResult GetVendor       ( CyString& aInfo );
    CY_DEVAEL_LIB_API virtual CyResult GetCameraModel  ( CyString& aInfo );
    CY_DEVAEL_LIB_API virtual CyResult GetProductID    ( CyString& aInfo );
    CY_DEVAEL_LIB_API virtual CyResult ResetCamera     ( );


//
// Extra parameters.
//
//  The following are parameters that are not defined in the CyCameraLink or CyCameraInterface
//  classes, but are need to be available for this new camera implementation.
//
//  The parameters will need to be available through these methods as well as through the
//  Get/SetParameter function of the base class.
//

    CY_DEVAEL_LIB_API virtual CyResult SetShutterTime( unsigned short aShutterTime );
    CY_DEVAEL_LIB_API virtual CyResult GetShutterTime( unsigned short& aShutterTime ) const;

	CY_DEVAEL_LIB_API virtual CyResult SetShutterOn( bool aValue );
    CY_DEVAEL_LIB_API virtual CyResult GetShutterOn( bool& aValue ) const;

	CY_DEVAEL_LIB_API virtual CyResult SetLightTime( unsigned short aLightTime );
    CY_DEVAEL_LIB_API virtual CyResult GetLightTime( unsigned short& aLightTime ) const;

	CY_DEVAEL_LIB_API virtual CyResult SetLightOn( bool aValue );
    CY_DEVAEL_LIB_API virtual CyResult GetLightOn( bool& aValue ) const;

	CY_DEVAEL_LIB_API virtual CyResult SetTriggerTime( unsigned long aTriggerTime );
    CY_DEVAEL_LIB_API virtual CyResult GetTriggerTime( unsigned long& aTriggerTime ) const;

	CY_DEVAEL_LIB_API virtual CyResult SetTriggerCfgD0( bool aValue );
    CY_DEVAEL_LIB_API virtual CyResult GetTriggerCfgD0( bool& aValue ) const;
	CY_DEVAEL_LIB_API virtual CyResult SetTriggerCfgD1( bool aValue );
    CY_DEVAEL_LIB_API virtual CyResult GetTriggerCfgD1( bool& aValue ) const;
	CY_DEVAEL_LIB_API virtual CyResult SetTriggerCfgD2( bool aValue );
    CY_DEVAEL_LIB_API virtual CyResult GetTriggerCfgD2( bool& aValue ) const;
	CY_DEVAEL_LIB_API virtual CyResult SetTriggerCfgD3( bool aValue );
    CY_DEVAEL_LIB_API virtual CyResult GetTriggerCfgD3( bool& aValue ) const;
	CY_DEVAEL_LIB_API virtual CyResult SetTriggerCfgD4( bool aValue );
    CY_DEVAEL_LIB_API virtual CyResult GetTriggerCfgD4( bool& aValue ) const;
	CY_DEVAEL_LIB_API virtual CyResult SetTriggerCfgD5( bool aValue );
    CY_DEVAEL_LIB_API virtual CyResult GetTriggerCfgD5( bool& aValue ) const;
	CY_DEVAEL_LIB_API virtual CyResult SetTriggerCfgD6( bool aValue );
    CY_DEVAEL_LIB_API virtual CyResult GetTriggerCfgD6( bool& aValue ) const;

	CY_DEVAEL_LIB_API virtual CyResult SetGeneratorPattern( unsigned short aValue );
    CY_DEVAEL_LIB_API virtual CyResult GetGeneratorPattern( unsigned short& aValue ) const;

    // Overridde Set/GetParameter for all types that we added above.
    CY_DEVAEL_LIB_API virtual CyResult SetParameter     ( const CyString& aName,
                                                            unsigned long  aValue );
    CY_DEVAEL_LIB_API virtual CyResult GetParameter     ( const CyString& aName,
                                                            unsigned long& aValue ) const;

    CY_DEVAEL_LIB_API virtual CyResult SetParameter     ( const CyString& aName,
                                                            unsigned short  aValue );
    CY_DEVAEL_LIB_API virtual CyResult GetParameter     ( const CyString& aName,
                                                            unsigned short& aValue ) const;

    CY_DEVAEL_LIB_API virtual CyResult SetParameter     ( const CyString& aName,
                                                            bool  aValue );
    CY_DEVAEL_LIB_API virtual CyResult GetParameter     ( const CyString& aName,
                                                            bool& aValue ) const;

//
// Camera Communication utilities.
//
//  For example a camera can be configured through registers, which must following
//  a clearly defined register access protocol.
private:
    virtual CyResult WriteRegister( unsigned char  aAddress,
                                    unsigned char  aValue ) const;
    virtual CyResult ReadRegister ( unsigned char  aAddress,
                                    unsigned char& aValue ) const;


//
// Members
//

private:
	unsigned long   mTriggerTime;
	unsigned short  mShutterTime;
	unsigned short  mLightTime;

	unsigned char   mSystemCfg;  // D0 => CMD0, doesn't matter
	                             // D1 => CMD1, doesn't matter
	                             // D2 => TST0, doesn't matter
	                             // D3 => TST1, doesn't matter
	                             // D4 => 1 = stop frame readout, doesn't matter
	                             // D5 => 0 = LED OFF, 1 = LED ON
	                             // D6 => 0 = SHUTTER OFF, 1 = SHUTTER ON
	                             // D7 => 1 = reset system, doesn't matter

	unsigned char   mTriggerCfg; // D0 => Long-term integration
	                             // D1 => 0 = low/falling, 1 = high/rising
	                             // D2 => 0 = level, 1 = slope
	                             // D3 => 0 = internal, 1 = external
	                             // D4 => 0 = fast triggering OFF, 1 = fast trigerring ON
	                             // D5 => 0 = double shutter OFF, 1 = double shutter ON
	                             // D6 => 0 = External Trigger, 1 = CC1
	                             // D7 => Not used

    // Property page pointers.  We keep the pointers to the property pages
    // created by this class in order to handle them in OnApply.
    void*           mPropertyPage1;
};


#endif // __CY_CAMERA_DEVAEL_H__
