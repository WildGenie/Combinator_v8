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
// File Name....: CyVideoDecoder.h
//
// Description..: Defines the interface of a CameraLink camera.
//
// *****************************************************************************
//
// $Log$
//
// *****************************************************************************

#ifndef __CY_VIDEO_DECODER_H__
#define __CY_VIDEO_DECODER_H__

// Headers
/////////////////////////////////////////////////////////////////////////////

// ===== This Project =====
#include "CyVideoDecoderLib.h"
#include "CyCameraInterface.h"
#include "CyVideoDecoderInputList.h"


// Forward-Declaration
/////////////////////////////////////////////////////////////////////////////

#ifdef __cplusplus
class VideoDecoderInterface;
#endif // __cplusplus


// Class
/////////////////////////////////////////////////////////////////////////////

#ifdef __cplusplus
class CyVideoDecoder : public CyCameraInterface
{
// Types
public:
    // List of allowed video sources
    typedef CyVideoDecoderInputList InputList;

// Construction / Destruction
public:
    CY_VIDEO_LIB_API            CyVideoDecoder( CyGrabber* aGrabber );
    CY_VIDEO_LIB_API virtual    ~CyVideoDecoder();

// Constructor for derived classes
    CY_VIDEO_LIB_API            CyVideoDecoder( CyGrabber*            aGrabber,
                                                const CyCameraLimits& aLimits,
                                                const InputList&      aInputs,
                                                bool                  aShowSerialPage = false );

// Update Camera
    CY_VIDEO_LIB_API virtual CyResult InternalUpdate( bool aDeviceReset ) const;


// Show Configuration Dialog
    CY_VIDEO_LIB_API virtual CyResult AddPropertyPage  ( void* aPropertySheet );
    CY_VIDEO_LIB_API virtual CyResult OnApply          ( void* aPropertyPage );


// Save/load settings from XML
public:
    CY_VIDEO_LIB_API virtual CyResult InternalSave ( CyXMLDocument& aDocument ) const;
    CY_VIDEO_LIB_API virtual CyResult InternalLoad ( CyXMLDocument& aDocument );

    // Source of the video decoder
    //
    // 0 : Composite 1A
    // 1 : Composite 1B
    // 2 : Composite 2A
    // 3 : Composite 2B
    // 4 : Composite 3A
    // 5 : Composite 3B
    // 6 : S-Video 1A Luma 2A chroma
    // 7 : S-Video 1A Luma 2B chroma
    // 8 : S-Video 1A Luma 3A chroma
    // 9 : S-Video 1A Luma 3B chroma
    // 10: S-Video 1B Luma 2A chroma
    // 11: S-Video 1B Luma 2B chroma
    // 12: S-Video 1B Luma 3A chroma
    // 13: S-Video 1B Luma 3B chroma
    // 14: S-Video 2A Luma 1A chroma
    // 15: S-Video 2A Luma 1B chroma
    // 16: S-Video 2B Luma 1A chroma
    // 17: S-Video 2B Luma 1B chroma
    // 18: S-Video 3A Luma 1A chroma
    // 19: S-Video 3A Luma 1B chroma
    // 20: S-Video 3B Luma 1A chroma
    // 21: S-Video 3B Luma 1B chroma
    // 22: Component 1
    // 23: Component 2

    CY_VIDEO_LIB_API virtual CyResult SetVideoSource   ( unsigned char  aSource, bool aRuntimeChange = false );
    CY_VIDEO_LIB_API virtual CyResult GetVideoSource   ( unsigned char& aSource ) const;


    // Video mode
    //
    //  0 : Autoswitch
    //  1 : (J, M) NTSC Square Pixel
    //  2 : (J, M) NTSC ITU-R BT.601
    //  3 : (B, G, H, I, N) PAL Square Pixel
    //  4 : (B, G, H, I, N) PAL  ITU-R BT.601
    //  5 : (M) PAL Square Pixel
    //  6 : (M) PAL ITU-R BT.601
    //  7 : (Combination-N) PAL Square Pixel
    //  8 : (Combination-N) ITU-R BT.601
    //  9 : NTSC 4.43 Square Pixel
    // 10 : NTSC 4.43 ITU-R BT.601
    // 11 : SECAM Square Pixel
    // 12 : SECAM ITU-R BT.601

    CY_VIDEO_LIB_API virtual CyResult SetVideoMode     ( unsigned char  aMode );
    CY_VIDEO_LIB_API virtual CyResult GetVideoMode     ( unsigned char& aMode ) const;


    // Operating mode
    //
    // 0 : Automatic, mode determined by the internal detection circuit
    // 1 : reserved, do not use
    // 2 : VCR (nonstandard video)
    // 3 : TV (standard video)

    CY_VIDEO_LIB_API virtual CyResult SetOperatingMode ( unsigned char  aMode );
    CY_VIDEO_LIB_API virtual CyResult GetOperatingMode ( unsigned char& aMode ) const;


    // Color Killer.  Forces chroma samples to zero at the source
    //
    // 0: Automatic
    // 1: reserved, do not use
    // 2: Enabled
    // 3: Disabled

    CY_VIDEO_LIB_API virtual CyResult SetColorKiller    ( unsigned char  aValue );
    CY_VIDEO_LIB_API virtual CyResult GetColorKiller    ( unsigned char& aValue ) const;

    CY_VIDEO_LIB_API virtual CyResult SetColorKillerThreshold( char  aValue );
    CY_VIDEO_LIB_API virtual CyResult GetColorKillerThreshold( char& aValue ) const;



    // Luminance processing
    //
    // For the luminance filter:
    //
    // 0: Luminance comb filter
    // 1: Luminance chroma trap filter

    CY_VIDEO_LIB_API virtual CyResult SetLuminanceFilter( unsigned char  aValue );
    CY_VIDEO_LIB_API virtual CyResult GetLuminanceFilter( unsigned char& aValue ) const;

    // Trap Filter select
    //
    // 0: No Notch
    // 1: Notch 1
    // 2: Notch 2
    // 3: Notch 3

    CY_VIDEO_LIB_API virtual CyResult SetTrapFilterSelect( unsigned char  aValue );
    CY_VIDEO_LIB_API virtual CyResult GetTrapFilterSelect( unsigned char& aValue ) const;



    // Picture Settings

    CY_VIDEO_LIB_API virtual CyResult SetBrightness     ( unsigned char  aValue );
    CY_VIDEO_LIB_API virtual CyResult GetBrightness     ( unsigned char& aValue ) const;
    CY_VIDEO_LIB_API virtual CyResult SetColorSaturation( unsigned char  aValue );
    CY_VIDEO_LIB_API virtual CyResult GetColorSaturation( unsigned char& aValue ) const;
    CY_VIDEO_LIB_API virtual CyResult SetHue            ( char           aValue );
    CY_VIDEO_LIB_API virtual CyResult GetHue            ( char&          aValue ) const;
    CY_VIDEO_LIB_API virtual CyResult SetContrast       ( unsigned char  aValue );
    CY_VIDEO_LIB_API virtual CyResult GetContrast       ( unsigned char& aValue ) const;

    // Video Auto Cropping
    CY_VIDEO_LIB_API virtual CyResult SetAutoCropping   ( bool  aEnabled );
    CY_VIDEO_LIB_API virtual CyResult GetAutoCropping   ( bool& aEnabled ) const;
    

    // Reset of the video decoder
    CY_VIDEO_LIB_API virtual CyResult ResetCamera     ( );

    // Support of extra parameters
    CY_VIDEO_LIB_API virtual CyResult SetParameter     ( const CyString& aName,
                                                         unsigned char      aValue );
    CY_VIDEO_LIB_API virtual CyResult SetParameter     ( const CyString& aName,
                                                         char               aValue );
    CY_VIDEO_LIB_API virtual CyResult SetParameter     ( const CyString& aName,
                                                         unsigned short     aValue );
    CY_VIDEO_LIB_API virtual CyResult SetParameter     ( const CyString& aName,
                                                         bool               aValue );
    CY_VIDEO_LIB_API virtual CyResult GetParameter     ( const CyString& aName,
                                                         unsigned char&     aValue ) const;
    CY_VIDEO_LIB_API virtual CyResult GetParameter     ( const CyString& aName,
                                                         char&              aValue ) const;
    CY_VIDEO_LIB_API virtual CyResult GetParameter     ( const CyString& aName,
                                                         unsigned short&    aValue ) const;
    CY_VIDEO_LIB_API virtual CyResult GetParameter     ( const CyString& aName,
                                                         bool&              aValue );

private:
    unsigned char mVideoSource;
    unsigned char mVideoMode;
    unsigned char mOperatingMode;
    unsigned char mColorKiller;
    char          mColorKillerThreshold;
    unsigned char mLuminanceFilter;
    unsigned char mTrapFilterSelect;
    unsigned char mBrightness;
    unsigned char mColorSaturation;
    char          mHue;
    unsigned char mContrast;
    bool          mAutoCropping;

    friend class CyRS170ImageSettings;
    friend class CyRS170Status;
    VideoDecoderInterface* mInterface;

    CyVideoDecoderInputList mInputList;

    bool          mShowSerialPage;
    void*         mPropertyPage;
    void*         mImagePage;
    mutable unsigned char mVideoSourceReg1;
    mutable unsigned char mVideoSourceReg2;
};
#endif // __cplusplus


#endif // __CY_VIDEO_DECODER_H__
