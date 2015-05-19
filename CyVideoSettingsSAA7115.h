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
// File Name....: VideoSettingsSAA7115.h
//
// Description..: Defines the interface of a CameraLink camera.
//
// *****************************************************************************
//
// $Log$
//
// *****************************************************************************

#ifndef __CY_VIDEO_SETTINGS_SAA7115_H__
#define __CY_VIDEO_SETTINGS_SAA7115_H__

// Headers
/////////////////////////////////////////////////////////////////////////////

// ===== This Project =====
#include "CyVideoDecoderLib.h"
#include "CyVideoSettingsSAA.h"
#include "CyVideoDecoderSAA.h"


// Class
/////////////////////////////////////////////////////////////////////////////

#ifdef __cplusplus
class CyVideoSettingsSAA7115 : public CyVideoSettingsSAA
{
protected:
    CyVideoSettingsSAA7115( unsigned short                      aID,
                            unsigned char                       aAddress,
                            CyGrabber&                          aGrabber,
                            const CyVideoDecoderSAA::InputList& aInputs )
        : CyVideoSettingsSAA( aID, aAddress, aGrabber, aInputs, true )
    {
    }

    virtual ~CyVideoSettingsSAA7115()
    {
    }


// Settings
public:
    IMPLEMENT_PARAMETER( LuminanceFilter,
                         CY_GRABBER_EXT_ANALOG_FILTERING_7115,
                         CY_GRABBER_EXT_ANALOG_FILTER_7115_LUMINANCE_FILTER,
                         unsigned char );

    IMPLEMENT_PARAMETER( ChromaCombBypass,
                         CY_GRABBER_EXT_ANALOG_FILTERING_7115,
                         CY_GRABBER_EXT_ANALOG_FILTER_7115_CHROMA_COMB_BYPASS,
                         bool );

    IMPLEMENT_PARAMETER( LuminanceCombFilter,
                         CY_GRABBER_EXT_ANALOG_FILTERING_7115,
                         CY_GRABBER_EXT_ANALOG_FILTER_7115_LUMA_COMB_FILTER,
                         bool );

    IMPLEMENT_PARAMETER( ChrominanceCombFilter,
                         CY_GRABBER_EXT_ANALOG_FILTERING_7115,
                         CY_GRABBER_EXT_ANALOG_FILTER_7115_CHROMA_COMB_FILTER,
                         bool );

    IMPLEMENT_PARAMETER( AutoChromaDetection,
                         CY_GRABBER_EXT_ANALOG_SOURCE,
                         CY_GRABBER_ANALOG_VS_AUTO_CHROMA_DETECTION,
                         unsigned char );

    IMPLEMENT_PARAMETER( LargeChromaLumaBandwidth,
                         CY_GRABBER_EXT_ANALOG_FILTERING_7115,
                         CY_GRABBER_EXT_ANALOG_FILTER_7115_LARGE_BANDWIDTH,
                         bool );

    IMPLEMENT_PARAMETER( ChromaLumaBandwidthAdj,
                         CY_GRABBER_EXT_ANALOG_FILTERING_7115,
                         CY_GRABBER_EXT_ANALOG_FILTER_7115_BANDWIDTH_ADJUST,
                         unsigned char );

    IMPLEMENT_PARAMETER( SECAMColorKillerLevel,
                         CY_GRABBER_EXT_ANALOG_FILTERING_7115,
                         CY_GRABBER_EXT_ANALOG_FILTER_7115_SECAM_COLOR_KILLER,
                         unsigned char );

    IMPLEMENT_PARAMETER( PALNTSCColorKillerLevel,
                         CY_GRABBER_EXT_ANALOG_FILTERING_7115,
                         CY_GRABBER_EXT_ANALOG_FILTER_7115_PAL_NTSC_COLOR_KILLER,
                         unsigned char );

    friend class CyVideoDecoderSAA;
};
#endif //__cplusplus

#endif // __CY_VIDEO_SETTINGS_SAA7115_H__

