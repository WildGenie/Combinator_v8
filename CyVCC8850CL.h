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
// File Name....: CyVCC8850CL.h
//
// Description..: Defines the basic of a camera implementation based on CameraLink
//
// *****************************************************************************
//
// $Log$
//
// *****************************************************************************

#ifndef __CY_VCC8850CL_H__
#define __CY_VCC8850CL_H__

// Headers
/////////////////////////////////////////////////////////////////////////////

// ===== CyCamLib =====
#include <CyCameraLink.h>

// ===== This Project =====
#include "CyCISCorporationLib.h"


// Class
/////////////////////////////////////////////////////////////////////////////

class CyVCC8850CL : public CyCameraLink
{
//
// Types
//
public:
	const static unsigned short CyVCC8850CL::sManualGain;
	const static unsigned short CyVCC8850CL::sManualRGain;
	const static unsigned short CyVCC8850CL::sManualBGain;

//
// Construction / Destruction
//
public:
    CY_CIS_CORPORATION_LIB_API            CyVCC8850CL( CyGrabber* aGrabber );
    CY_CIS_CORPORATION_LIB_API virtual    ~CyVCC8850CL();
 

//
// Camera Update Methods
//
protected:
#if defined (COYOTE_SDK_VERSION) & ( COYOTE_SDK_VERSION >= 0210 )
    CY_CIS_CORPORATION_LIB_API virtual CyResult InternalUpdate( bool aDeviceReset ) const;
#else
    CY_CIS_CORPORATION_LIB_API virtual CyResult InternalUpdate( ) const;
#endif
    CY_CIS_CORPORATION_LIB_API virtual CyResult LocalUpdate   ( bool aDeviceReset ) const;


//
// Configuration Dialog Methods.
//
protected:
    CY_CIS_CORPORATION_LIB_API virtual CyResult AddPropertyPage  ( void* aPropertySheet );
    CY_CIS_CORPORATION_LIB_API virtual CyResult OnApply          ( void* aPropertyPage );



//
// XML Storage methods.
//
protected:
    CY_CIS_CORPORATION_LIB_API virtual CyResult InternalSave ( CyXMLDocument& aDocument ) const;
    CY_CIS_CORPORATION_LIB_API virtual CyResult InternalLoad ( CyXMLDocument& aDocument );

//
// Camera parameters.
//
	typedef enum
	{
		GAIN_0_DB,  // 0 -   0 dB
		GAIN_6_DB,  // 1 -  +6 dB
		GAIN_12_DB, // 2 - +12 dB
		GAIN_MANUAL // 3 - Manual
	} GainMode;

	CY_CIS_CORPORATION_LIB_API virtual CyResult SetGainMode(GainMode aMode);
	CY_CIS_CORPORATION_LIB_API virtual CyResult GetGainMode(GainMode &aMode) const;

	typedef enum
	{
		ESHUTTER_MODE_1_12,   //  0 - 1/12s (OFF)
		ESHUTTER_MODE_1_30,   //  1 - 1/30s
		ESHUTTER_MODE_1_60,   //  2 - 1/60s
		ESHUTTER_MODE_1_100,  //  3 - 1/100s
		ESHUTTER_MODE_1_120,  //  4 - 1/120s
		ESHUTTER_MODE_1_250,  //  5 - 1/250s
		ESHUTTER_MODE_1_500,  //  6 - 1/500s
		ESHUTTER_MODE_1_1000, //  7 - 1/1000s
		ESHUTTER_MODE_1_2000, //  8 - 1/2000s
		ESHUTTER_MODE_1_4000, //  9 - 1/4000s
		ESHUTTER_MODE_1_6000, // 10 - 1/6000s
		ESHUTTER_MODE_OFF_1,  // 11 - 1/12s (OFF)
		ESHUTTER_MODE_OFF_2,  // 12 - 1/12s (OFF)
		ESHUTTER_MODE_OFF_3,  // 13 - 1/12s (OFF)
		ESHUTTER_MODE_OFF_4,  // 14 - 1/12s (OFF)
		ESHUTTER_MODE_OFF_5,  // 15 - 1/12s (OFF)
		ESHUTTER_MODE_MANUAL  // 16 - Manual
	} EShutterMode;

	CY_CIS_CORPORATION_LIB_API virtual CyResult SetEShutterMode(EShutterMode aMode);
	CY_CIS_CORPORATION_LIB_API virtual CyResult GetEShutterMode(EShutterMode &aMode) const;

	typedef enum
	{
		WB_2600_K, // 0 - 2600 K
		WB_3600_K, // 1 - 3600 K
		WB_5600_K, // 2 - 5600 K
		WB_9000_K, // 3 - 9000 K
		WB_MANUAL, // 4 - MANUAL
	} WhiteBalanceMode;

	CY_CIS_CORPORATION_LIB_API virtual CyResult SetWhiteBalanceMode(WhiteBalanceMode aMode);
	CY_CIS_CORPORATION_LIB_API virtual CyResult GetWhiteBalanceMode(WhiteBalanceMode &aMode) const;

	typedef enum
	{
		IT_NEGATIVE, // 0 - NEGATIVE
		IT_POSITIVE  // 1 - POSITIVE
	} InputTriggerMode;

	CY_CIS_CORPORATION_LIB_API virtual CyResult SetInputTriggerMode(InputTriggerMode aMode);
	CY_CIS_CORPORATION_LIB_API virtual CyResult GetInputTriggerMode(InputTriggerMode &aMode) const;

	CY_CIS_CORPORATION_LIB_API virtual CyResult SetManualShutterHigh(unsigned short aValue);
	CY_CIS_CORPORATION_LIB_API virtual CyResult GetManualShutterHigh(unsigned short &aValue) const;

	CY_CIS_CORPORATION_LIB_API virtual CyResult SetManualShutterLow(unsigned short aValue);
	CY_CIS_CORPORATION_LIB_API virtual CyResult GetManualShutterLow(unsigned short &aValue) const;

	CY_CIS_CORPORATION_LIB_API virtual CyResult SetParameter( const CyString& aName, unsigned short aValue);
	CY_CIS_CORPORATION_LIB_API virtual CyResult GetParameter( const CyString& aName, unsigned short &aValue) const;

//
// Camera Communication utilities.
//
private:
    CyResult WriteRegister( unsigned short  aAddress,
                            unsigned short  aValue ) const;
    CyResult ReadRegister ( unsigned short  aAddress,
                            unsigned short& aValue ) const;


//
// Members
//

private:
	GainMode           mGainMode;
	EShutterMode       mEShutterMode;
	WhiteBalanceMode   mWhiteBalanceMode;
	InputTriggerMode   mInputTriggerMode;

	unsigned short     mManualShutterHigh;
	unsigned short     mManualShutterLow;

    void*              mPropertyPage;
};


#endif // __CY_VCC8850CL_H__
