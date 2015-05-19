// *****************************************************************************
//
// $Id$
//
// cy1h11b1
//
// *****************************************************************************
//
//     Copyright (c) 2003, Pleora Technologies Inc., All rights reserved.
//
// *****************************************************************************
//
// File Name....: VideoSettingsSAA7113.h
//
// Description..: Defines the interface of a CameraLink camera.
//
// *****************************************************************************
//
// $Log$
//
// *****************************************************************************

#ifndef __CY_VIDEO_SETTINGS_SAA7113_H__
#define __CY_VIDEO_SETTINGS_SAA7113_H__

// Headers
/////////////////////////////////////////////////////////////////////////////

// ===== This Project =====
#include "CyVideoDecoderLib.h"
#include "CyVideoSettingsSAA.h"
#include "CyVideoDecoderSAA.h"


// Class
/////////////////////////////////////////////////////////////////////////////

#ifdef __cplusplus
class CyVideoSettingsSAA7113 : public CyVideoSettingsSAA
{
protected:
    CyVideoSettingsSAA7113( unsigned short                      aID,
                            unsigned char                       aAddress,
                            CyGrabber&                          aGrabber,
                            const CyVideoDecoderSAA::InputList& aInputs )
        : CyVideoSettingsSAA( aID, aAddress, aGrabber, aInputs, false )
    {
    }

    virtual ~CyVideoSettingsSAA7113()
    {
    }


// Settings
public:
    IMPLEMENT_PARAMETER( ApertureFactor,
                         CY_GRABBER_EXT_ANALOG_FILTERING_7113,
                         CY_GRABBER_EXT_ANALOG_FILTER_7113_APERTURE_FACTOR,
                         unsigned char );

    IMPLEMENT_PARAMETER( ApertureBandpass,
                         CY_GRABBER_EXT_ANALOG_FILTERING_7113,
                         CY_GRABBER_EXT_ANALOG_FILTER_7113_APERTURE_BAND_PASS,
                         unsigned char );

    IMPLEMENT_PARAMETER( PrefilterActive,
                         CY_GRABBER_EXT_ANALOG_FILTERING_7113,
                         CY_GRABBER_EXT_ANALOG_FILTER_7113_PREFILTER_ACTIVE,
                         bool );

    IMPLEMENT_PARAMETER( ChromaTrapBypass,
                         CY_GRABBER_EXT_ANALOG_FILTERING_7113,
                         CY_GRABBER_EXT_ANALOG_FILTER_7113_CHROMA_TRAP_BYPASS,
                         bool );

    IMPLEMENT_PARAMETER( ChrominanceBandwidth,
                         CY_GRABBER_EXT_ANALOG_FILTERING_7113,
                         CY_GRABBER_EXT_ANALOG_FILTER_7113_CHROMA_BANDWIDTH,
                         unsigned char );

    IMPLEMENT_PARAMETER( AutomaticColorKiller,
                         CY_GRABBER_EXT_ANALOG_FILTERING_7113,
                         CY_GRABBER_EXT_ANALOG_FILTER_7113_AUTO_COLOR_KILLER,
                         bool );

    friend class CyVideoDecoderSAA;
};
#endif // __cplusplus

#endif // __CY_VIDEO_SETTINGS_SAA7115_H__

