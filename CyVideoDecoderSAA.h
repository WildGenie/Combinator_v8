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
// File Name....: CyVideoDecoderSAA.h
//
// Description..: Defines the interface of a CameraLink camera.
//
// *****************************************************************************
//
// $Log$
//
// *****************************************************************************

#ifndef __CY_VIDEO_DECODER_SAA_H__
#define __CY_VIDEO_DECODER_SAA_H__

// Headers
/////////////////////////////////////////////////////////////////////////////

// ===== CyCamLib =====
#include <CyCameraInterface.h>


// ===== This Project =====
#include "CyVideoDecoderLib.h"
#include "CyVideoDecoderInputList.h"


// Forward Declaration
/////////////////////////////////////////////////////////////////////////////

#ifdef __cplusplus
class VideoDecoderInterface;
class CyVideoSettingsSAA;
#endif // __cplusplus


// Class
/////////////////////////////////////////////////////////////////////////////

#ifdef __cplusplus
struct CyVideoDecoderSAAInternal;
class CyVideoDecoderSAA : public CyCameraInterface
{
// Types
public:
    // List of allowed video sources
    typedef CyVideoDecoderInputList InputList;


// Construction / Destruction
public:
    CY_VIDEO_LIB_API            CyVideoDecoderSAA( CyGrabber*                      aGrabber,
                                                   const CyCameraLimits&           aLimits,
                                                   bool                            aShowSerialPage = false,
                                                   bool                            aBWProgressive = false );
    CY_VIDEO_LIB_API virtual    ~CyVideoDecoderSAA();

// Video Decoder settings
public:
    // Indicates if using SAA 7113 or SAA 7115
    CY_VIDEO_LIB_API bool    IsUsingSAA7115() const;
    
    // Indicates if the B/W progressive mode is used
    CY_VIDEO_LIB_API bool    IsBWProgressive() const;

    // Channel access
    // NOTE: Changes to parameters are always applied to the current channel.
    CY_VIDEO_LIB_API virtual unsigned short
                                      GetChannelCount() const;
    CY_VIDEO_LIB_API virtual CyResult SetCurrentChannel( const CyChannel& aChannel );
    CY_VIDEO_LIB_API virtual CyResult GetCurrentChannel( CyChannel& aChannel ) const;

    // Enable or disable the immediate change flag.  When enabled, a call to a Set
    // method will immediately send the value to the video decoder.  Otherwise, it
    // is deferred until the next UpdateToCamera,
    CY_VIDEO_LIB_API virtual CyResult   SetImmediateModification( bool  aEnabled );
    CY_VIDEO_LIB_API virtual CyResult   GetImmediateModification( bool& aEnabled ) const;

    // Returns the video decoder settings object for the current channel
    CY_VIDEO_LIB_API virtual CyVideoSettingsSAA& GetVideoSettings() const;

    // Add or remove inputs in the hardware acquisition loop.
    // When there is one or more inputs in the loop the hardware, if supported, will
    // switch inputs after a succesful acuqisition from the current input.
    // Refer to the inputs from the CyVideoSettingsSAA object.

    // Deprecated, use the version in the video settings class instead
    CY_VIDEO_LIB_API virtual CyResult AddAutoSwitchInput( unsigned char aInput );
    CY_VIDEO_LIB_API virtual CyResult RemoveAutoSwitchInput( unsigned char aInput );
    CY_VIDEO_LIB_API virtual CyResult ClearAutoSwitchInputs( unsigned char aInput );
    CY_VIDEO_LIB_API virtual CyResult IsAutoSwitchInput( unsigned char aInput, bool& aEnabled ) const;

    // Reset of the video decoder
    CY_VIDEO_LIB_API virtual CyResult ResetCamera     ( );

    // Extra parameters
    CY_VIDEO_LIB_API virtual CyResult SetParameter     ( const CyString& aName,
                                                         __int64         aValue,
                                                         bool            aTest = false );
    CY_VIDEO_LIB_API virtual CyResult GetParameter     ( const CyString& aName,
                                                         __int64&        aValue ) const;

private:
    struct CyVideoDecoderSAAInternal* mInternal;

    friend class CyMultiVideoPage;
    friend class CyVideoSettingsSAA;
};
#endif // __cplusplus

#endif // __CY_VIDEO_DECODER_SAA_H__
