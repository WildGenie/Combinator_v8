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
// File Name....: CyCameraTexasInstruments.h
//
// Description..: Defines the basic of a camera implementation based on CameraLink
//
// Implementation Notes: Replace TEXAS_INSTRUMENTS with the real name
//
//                       This template derives from CameraLink but can be derived
//                       from other camera types, such as CyVideoDecoder or CyCameraLVDS
//
// *****************************************************************************
//
// $Log$
//
// *****************************************************************************

#ifndef __CY_CAMERA_TEXAS_INSTRUMENTS_H__
#define __CY_CAMERA_TEXAS_INSTRUMENTS_H__

// Headers
/////////////////////////////////////////////////////////////////////////////

// ===== CyCamLib =====
#include <CyCameraLVDS.h>

// ===== This Project =====
#include "CyTexasInstrumentsLib.h"


// Class
/////////////////////////////////////////////////////////////////////////////

class CyTIMP285 : public CyCameraLVDS
{
// Types
public:
	const static unsigned short sGain; // The one and only gain
//
// Construction / Destruction
//
public:
    CY_TEXAS_INSTRUMENTS_LIB_API            CyTIMP285( CyGrabber* aGrabber );
    CY_TEXAS_INSTRUMENTS_LIB_API virtual    ~CyTIMP285();

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
    CY_TEXAS_INSTRUMENTS_LIB_API virtual CyResult InternalUpdate( bool aDeviceReset ) const;
#else
    CY_TEXAS_INSTRUMENTS_LIB_API virtual CyResult InternalUpdate( ) const;
#endif
    CY_TEXAS_INSTRUMENTS_LIB_API virtual CyResult LocalUpdate   ( bool aDeviceReset ) const;


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
    CY_TEXAS_INSTRUMENTS_LIB_API virtual CyResult AddPropertyPage  ( void* aPropertySheet );
    CY_TEXAS_INSTRUMENTS_LIB_API virtual CyResult OnApply          ( void* aPropertyPage );



//
// XML Storage methods.
//
//  InternalSave:  Overridden if this camera must save its own settings in the XML document.
//                 Invoked by SaveToXML
//  InternalLoad:  Overridden if this camera must load its own settings from the XML document
//                 Invoked by LoadFromXML
//
protected:
    CY_TEXAS_INSTRUMENTS_LIB_API virtual CyResult InternalSave ( CyXMLDocument& aDocument ) const;
    CY_TEXAS_INSTRUMENTS_LIB_API virtual CyResult InternalLoad ( CyXMLDocument& aDocument );

//
// Overridden Parameters
//
protected:

//
// Extra parameters.
//
//  The following are parameters that are not defined in the CyCameraLink or CyCameraInterface
//  classes, but are need to be available for this new camera implementation.
//
//  The parameters will need to be available through these methods as well as through the
//  Get/SetParameter function of the base class.
//

    // Overridde Set/GetParameter for all types that we added above.
    CY_TEXAS_INSTRUMENTS_LIB_API virtual CyResult SetParameter     ( const CyString& aName,
                                                                     unsigned short     aValue );
    CY_TEXAS_INSTRUMENTS_LIB_API virtual CyResult GetParameter     ( const CyString& aName,
                                                                     unsigned short&    aValue ) const;

	typedef enum
	{
		SS_0,
		SS_1
	} ShutterSelection;
	CY_TEXAS_INSTRUMENTS_LIB_API virtual CyResult SetShutterSelection(ShutterSelection aSS);
	CY_TEXAS_INSTRUMENTS_LIB_API virtual CyResult GetShutterSelection(ShutterSelection &aSS) const;

	CY_TEXAS_INSTRUMENTS_LIB_API virtual CyResult SetShutterSpeedControl(unsigned short aUShort);
	CY_TEXAS_INSTRUMENTS_LIB_API virtual CyResult GetShutterSpeedControl(unsigned short &aUShort) const;

	typedef enum
	{
		BN_0_NONE,
		BN_1_2x2,
		BN_2_4x4,
		BN_3_NONE
	} BinningMode;
	CY_TEXAS_INSTRUMENTS_LIB_API virtual CyResult SetBinningMode(BinningMode aBN);
	CY_TEXAS_INSTRUMENTS_LIB_API virtual CyResult GetBinningMode(BinningMode &aBN) const;

	typedef enum
	{
		AV_0_NONE,
		AV_1_TWICE,
		AV_2_FOUR_TIME,
		AV_3_EIGHT_TIME,
	} AveragingMode;
	CY_TEXAS_INSTRUMENTS_LIB_API virtual CyResult SetAveragingMode(AveragingMode aAV);
	CY_TEXAS_INSTRUMENTS_LIB_API virtual CyResult GetAveragingMode(AveragingMode &aAV) const;

	typedef enum
	{
		FA_0_HIGH_ROTATION,
		FA_1_LOW_ROTATION,
		FA_2_OFF,
		FA_3_OFF
	} FanControlMode;
	CY_TEXAS_INSTRUMENTS_LIB_API virtual CyResult SetFanControlMode(FanControlMode aFA);
	CY_TEXAS_INSTRUMENTS_LIB_API virtual CyResult GetFanControlMode(FanControlMode &aFA) const;

//
// Camera Communication utilities.
//
private:
	CY_TEXAS_INSTRUMENTS_LIB_API virtual CyResult WriteRegister(const char *aAddress, unsigned short aValue) const;
	CY_TEXAS_INSTRUMENTS_LIB_API virtual CyResult ReadMode();


//
// Members
//

private:
	unsigned short   mSH;
	AveragingMode    mAV;
	BinningMode      mBN;
	FanControlMode   mFA;
	ShutterSelection mSS;

	// The Camera Property page
    void*           mPropertyPage;
};


#endif // __CY_CAMERA_TEXAS_INSTRUMENTS_H__
