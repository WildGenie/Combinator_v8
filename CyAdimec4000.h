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
// File Name....: CyAdimec4000.h
//
// Description..: Defines the basic of a camera implementation based on CameraLink
//
// *****************************************************************************
//
// $Log$
//
// *****************************************************************************

#ifndef __CY_CAMERA_ADIMEC_4000_H__
#define __CY_CAMERA_ADIMEC_4000_H__

// Headers
/////////////////////////////////////////////////////////////////////////////

// ===== This Project =====
#include "CyAdimecCamera.h"


// Class
/////////////////////////////////////////////////////////////////////////////

class CyAdimec4000 : public CyAdimecCamera
{
//
// Types
//
public:
    // Gains indexes
    CY_ADIMEC_LIB_API static const unsigned short sDigitalGain;
    CY_ADIMEC_LIB_API static const unsigned short sAnalogGain;

    // Since there are two black level, we store the values in the
    // offset storage of CyCameraInterface
    CY_ADIMEC_LIB_API static const unsigned short sBlackLevelLeft;  // Only available with dual output model
    CY_ADIMEC_LIB_API static const unsigned short sBlackLevelRight; // Only available with dual output model


//
// Construction / Destruction
//
public:
    CY_ADIMEC_LIB_API            CyAdimec4000( CyGrabber* aGrabber, const CyCameraLimits& aLimits );
    CY_ADIMEC_LIB_API virtual    ~CyAdimec4000();
 

//
// Camera Update Methods
//
protected:
#if defined (COYOTE_SDK_VERSION) & ( COYOTE_SDK_VERSION >= 0210 )
    CY_ADIMEC_LIB_API virtual CyResult InternalUpdate( bool aDeviceReset ) const;
#else
    CY_ADIMEC_LIB_API virtual CyResult InternalUpdate() const;
#endif
    CY_ADIMEC_LIB_API virtual CyResult LocalUpdate   ( bool aDeviceReset ) const;


//
// Extra parameters.
//

    // CC1 Polarity
    //
    // true = starts on rising edge
    // false = starts on faling edge
    //
    // Access with Set/GetParameter( "CC1 Polarity", bool );
    
    // Pixel Correction
    //
    // true = enabled
    // false = disabled
    //
    // Access with Set/GetParameter( "Pixel Correction", bool );


};


#endif // __CY_CAMERA_ADIMEC_4000_H__
