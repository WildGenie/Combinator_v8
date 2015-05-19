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
// File Name....: VideoSettingsSAA.h
//
// Description..: Defines the interface of a CameraLink camera.
//
// *****************************************************************************
//
// $Log$
//
// *****************************************************************************

#ifndef __CY_VIDEO_SETTINGS_SAA_H__
#define __CY_VIDEO_SETTINGS_SAA_H__

// Headers
/////////////////////////////////////////////////////////////////////////////

// ===== CyUtilsLib =====
#include <CyErrorInterface.h>
#include <CyXMLDocument.h>

// ===== CyCamLib =====
#include <CyGrabber.h>

// ===== This Project =====
#include "CyVideoDecoderLib.h"
#include "CyVideoDecoderSAA.h"

#include <math.h>


// Macros
/////////////////////////////////////////////////////////////////////////////

#define IMPLEMENT_PARAMETER( aName, aExtension, aParamID, aType ) \
    CyResult Set##aName( aType aValue ) \
    { \
        if ( !mGrabber.HasExtension( aExtension + mID ) ) \
            return CY_RESULT_NOT_FOUND; \
        CyGrabberExtension& lExtension = mGrabber.GetExtension( aExtension + mID ); \
        if ( lExtension.SetParameter( aParamID, aValue ) != CY_RESULT_OK ) \
            return lExtension.GetErrorInfo(); \
        if ( GetImmediateModification() ) \
            return lExtension.SaveToGrabber(); \
        return CY_RESULT_OK; \
    } \
    CyResult Get##aName( aType& aValue ) const \
    { \
        if ( !mGrabber.HasExtension( aExtension + mID ) ) \
            return CY_RESULT_NOT_FOUND; \
        CyGrabberExtension& lExtension = mGrabber.GetExtension( aExtension + mID ); \
        return lExtension.GetParameter( aParamID, aValue ); \
    }



// Class
/////////////////////////////////////////////////////////////////////////////

#ifdef __cplusplus
struct CyVideoSettingsSAAInternal;
class CyVideoSettingsSAA : public CyErrorInterface
{
// Construction / Destruction
protected:
    CyVideoSettingsSAA( unsigned short                      aID,
                        unsigned char                       aAddress,
                        CyGrabber&                          aGrabber,
                        const CyVideoDecoderSAA::InputList& aInputs,
                        bool                                a7115 );

public:
    virtual ~CyVideoSettingsSAA();


// Settings upload and download to video decoder
public:
    // When immediate modification is true, a call to a "Set" will modify the
    // register immediately.  Otherwise, the local cache will be updated and
    // Apply must be invoked
    void SetImmediateModification( bool aEnabled )
    {
        mImmediateModification = aEnabled;
    }
    bool GetImmediateModification() const
    {
        return mImmediateModification;
    }

    bool IsBWProgressive() const
    {
        if ( !mGrabber.HasExtension( CY_GRABBER_EXT_ANALOG_SOURCE + mID ) )
            return false;
        CyGrabberExtension& lExtension = mGrabber.GetExtension( CY_GRABBER_EXT_ANALOG_SOURCE + mID );

        return ( lExtension.HasParameter( CY_GRABBER_ANALOG_VS_PROGRESSIVE ) &&
                 lExtension.GetParameterBool( CY_GRABBER_ANALOG_VS_PROGRESSIVE ) );
    }




// accessors
public:
    CY_VIDEO_LIB_API unsigned char GetAddress() const;
    CY_VIDEO_LIB_API const CyVideoDecoderSAA::InputList& GetInputs() const;

    CyResult Reset()
    {
        CyGrabberExtension* lExtension;

        if ( mGrabber.HasExtension( CY_GRABBER_EXT_ANALOG_SOURCE + mID ) )
        {
            lExtension = & mGrabber.GetExtension( CY_GRABBER_EXT_ANALOG_SOURCE + mID );
            if ( lExtension->Reset() != CY_RESULT_OK )
                return SetErrorInfo( *lExtension );
        }

        if ( mGrabber.HasExtension( CY_GRABBER_EXT_ANALOG_IMAGE_SETTINGS + mID ) )
        {
            lExtension = & mGrabber.GetExtension( CY_GRABBER_EXT_ANALOG_IMAGE_SETTINGS + mID );
            if ( lExtension->Reset() != CY_RESULT_OK )
                return SetErrorInfo( *lExtension );
        }

        if ( mGrabber.HasExtension( CY_GRABBER_EXT_ANALOG_GAIN + mID ) )
        {
            lExtension = & mGrabber.GetExtension( CY_GRABBER_EXT_ANALOG_GAIN + mID );
            if ( lExtension->Reset() != CY_RESULT_OK )
                return SetErrorInfo( *lExtension );
        }

        if ( mGrabber.HasExtension( CY_GRABBER_EXT_ANALOG_FILTERING_7115 + mID ) )
        {
            lExtension = & mGrabber.GetExtension( CY_GRABBER_EXT_ANALOG_FILTERING_7115 + mID );
            if ( lExtension->Reset() != CY_RESULT_OK )
                return SetErrorInfo( *lExtension );
        }

        if ( mGrabber.HasExtension( CY_GRABBER_EXT_ANALOG_FILTERING_7113 + mID ) )
        {
            lExtension = & mGrabber.GetExtension( CY_GRABBER_EXT_ANALOG_FILTERING_7113 + mID );
            if ( lExtension->Reset() != CY_RESULT_OK )
                return SetErrorInfo( *lExtension );
        }

        if ( mGrabber.HasExtension( CY_GRABBER_EXT_ANALOG_WINDOWING + mID ) )
        {
            lExtension = & mGrabber.GetExtension( CY_GRABBER_EXT_ANALOG_WINDOWING + mID );
            if ( lExtension->Reset() != CY_RESULT_OK )
                return SetErrorInfo( *lExtension );
        }

        if ( mGrabber.HasExtension( CY_GRABBER_EXT_ANALOG_STATUS + mID ) )
        {
            lExtension = & mGrabber.GetExtension( CY_GRABBER_EXT_ANALOG_STATUS + mID );
            if ( lExtension->Reset() != CY_RESULT_OK )
                return SetErrorInfo( *lExtension );
        }

        return CY_RESULT_OK;
    }


// Parameters
public:

    static bool IsBWProgressiveAvailable( CyGrabber& aGrabber )
    {
        return aGrabber.HasExtension( CY_GRABBER_EXT_ANALOG_SOURCE ) &&
               aGrabber.HasParameter( CY_GRABBER_ANALOG_VS_PROGRESSIVE );
    }


    CyResult SetBWProgressiveMode( bool  aOutputLevel,
                                   bool  aBlackLevelIRE )
    {
        if ( !mGrabber.HasExtension( CY_GRABBER_EXT_ANALOG_SOURCE + mID ) )
            return CY_RESULT_NOT_FOUND;
        CyGrabberExtension& lExtension = mGrabber.GetExtension( CY_GRABBER_EXT_ANALOG_SOURCE + mID );

        if ( lExtension.SetParameter( CY_GRABBER_ANALOG_VS_PROG_OUTPUT_LEVEL, aOutputLevel ) != CY_RESULT_OK )
            return SetErrorInfo( lExtension );

        if ( lExtension.SetParameter( CY_GRABBER_ANALOG_VS_PROG_BLACK_LEVEL, aBlackLevelIRE ) != CY_RESULT_OK )
            return SetErrorInfo( lExtension );

        if ( GetImmediateModification() )
            return lExtension.SaveToGrabber();

        return CY_RESULT_OK;

    }
    CyResult GetBWProgressiveMode( bool& aOutputLevel,
                                   bool& aBlackLevelIRE ) const
    {
        if ( !mGrabber.HasExtension( CY_GRABBER_EXT_ANALOG_SOURCE + mID ) )
            return CY_RESULT_NOT_FOUND;
        CyGrabberExtension& lExtension = mGrabber.GetExtension( CY_GRABBER_EXT_ANALOG_SOURCE + mID );

        if ( lExtension.GetParameter( CY_GRABBER_ANALOG_VS_PROG_OUTPUT_LEVEL, aOutputLevel ) != CY_RESULT_OK )
            return SetErrorInfo( lExtension );

        if ( lExtension.GetParameter( CY_GRABBER_ANALOG_VS_PROG_BLACK_LEVEL, aBlackLevelIRE ) != CY_RESULT_OK )
            return SetErrorInfo( lExtension );

        return CY_RESULT_OK;
    }

    // Add or remove inputs in the hardware acquisition loop.
    // When there is one or more inputs in the loop the hardware, if supported, will
    // switch inputs after a succesful acuqisition from the current input.
    // Refer to the inputs from the CyVideoSettingsSAA object.

    CyResult AddAutoSwitchInput( unsigned char aInput )
    {
        if ( !mGrabber.HasExtension( CY_GRABBER_EXT_ANALOG_SOURCE + mID ) )
            return CY_RESULT_NOT_FOUND;
        CyGrabberExtension& lExtension = mGrabber.GetExtension( CY_GRABBER_EXT_ANALOG_SOURCE + mID );

        unsigned long lValue = lExtension.GetParameterInt( CY_GRABBER_ANALOG_VS_AUTO_INPUT_SWITCHING_MASK );
        lValue |= (unsigned long)pow( 2.0, aInput );
        if ( lExtension.SetParameter( CY_GRABBER_ANALOG_VS_AUTO_INPUT_SWITCHING_MASK, lValue ) != CY_RESULT_OK )
            return lExtension.GetErrorInfo();

        if ( GetImmediateModification() )
            return lExtension.SaveToGrabber();

        return CY_RESULT_OK;
    }
    CyResult RemoveAutoSwitchInput( unsigned char aInput )
    {
        if ( !mGrabber.HasExtension( CY_GRABBER_EXT_ANALOG_SOURCE + mID ) )
            return CY_RESULT_NOT_FOUND;
        CyGrabberExtension& lExtension = mGrabber.GetExtension( CY_GRABBER_EXT_ANALOG_SOURCE + mID );

        unsigned long lValue = lExtension.GetParameterInt( CY_GRABBER_ANALOG_VS_AUTO_INPUT_SWITCHING_MASK );
        lValue &= ~(unsigned long)pow( 2.0, aInput );
        if ( lExtension.SetParameter( CY_GRABBER_ANALOG_VS_AUTO_INPUT_SWITCHING_MASK, lValue ) != CY_RESULT_OK )
            return lExtension.GetErrorInfo();

        if ( GetImmediateModification() )
            return lExtension.SaveToGrabber();

        return CY_RESULT_OK;
    }
    CyResult ClearAutoSwitchInputs( unsigned char aInput )
    {
        if ( !mGrabber.HasExtension( CY_GRABBER_EXT_ANALOG_SOURCE + mID ) )
            return CY_RESULT_NOT_FOUND;
        CyGrabberExtension& lExtension = mGrabber.GetExtension( CY_GRABBER_EXT_ANALOG_SOURCE + mID );

        if ( lExtension.SetParameter( CY_GRABBER_ANALOG_VS_AUTO_INPUT_SWITCHING_MASK, 0 ) != CY_RESULT_OK )
            return lExtension.GetErrorInfo();

        if ( GetImmediateModification() )
            return lExtension.SaveToGrabber();

        return CY_RESULT_OK;
    }
    CyResult IsAutoSwitchInput( unsigned char aInput, bool& aEnabled ) const
    {
        if ( !mGrabber.HasExtension( CY_GRABBER_EXT_ANALOG_SOURCE + mID ) )
            return CY_RESULT_NOT_FOUND;
        CyGrabberExtension& lExtension = mGrabber.GetExtension( CY_GRABBER_EXT_ANALOG_SOURCE + mID );

        unsigned long lValue;
        if ( lExtension.GetParameter( CY_GRABBER_ANALOG_VS_AUTO_INPUT_SWITCHING_MASK, lValue ) != CY_RESULT_OK )
            return SetErrorInfo( lExtension );

        aEnabled = ( ( (unsigned long)pow( 2.0, aInput ) ) & lValue ) != 0;
        return CY_RESULT_OK;
    }
    
    IMPLEMENT_PARAMETER( VideoSource,
                         CY_GRABBER_EXT_ANALOG_SOURCE,
                         CY_GRABBER_ANALOG_VS_INPUT,
                         unsigned char );

    IMPLEMENT_PARAMETER( VerticalNoiseReduction,
                         CY_GRABBER_EXT_ANALOG_SOURCE,
                         CY_GRABBER_ANALOG_VS_VERTICAL_NOISE_REDUCTION,
                         unsigned char );

    IMPLEMENT_PARAMETER( AutomaticFieldDetection,
                         CY_GRABBER_EXT_ANALOG_SOURCE,
                         CY_GRABBER_ANALOG_VS_AUTO_FIELD_SELECTION,
                         bool );

    IMPLEMENT_PARAMETER( FieldSelection,
                         CY_GRABBER_EXT_ANALOG_SOURCE,
                         CY_GRABBER_ANALOG_VS_FIELD_SELECTION,
                         unsigned char );

    IMPLEMENT_PARAMETER( HorizontalTimeConstant,
                         CY_GRABBER_EXT_ANALOG_SOURCE,
                         CY_GRABBER_ANALOG_VS_HOR_TIME_CONSTANT,
                         unsigned char );

    IMPLEMENT_PARAMETER( FastColourTimeConstant,
                         CY_GRABBER_EXT_ANALOG_SOURCE,
                         CY_GRABBER_ANALOG_VS_FAST_COLOR_TIME_CONSTANT,
                         bool );

    IMPLEMENT_PARAMETER( ColourDetectionStandard,
                         CY_GRABBER_EXT_ANALOG_SOURCE,
                         CY_GRABBER_ANALOG_VS_CHROMA_DETECTION_STANDARD,
                         unsigned char );

    IMPLEMENT_PARAMETER( Brightness,
                         CY_GRABBER_EXT_ANALOG_IMAGE_SETTINGS,
                         CY_GRABBER_EXT_ANALOG_IS_BRIGHTNESS,
                         unsigned char );

    IMPLEMENT_PARAMETER( Contrast,
                         CY_GRABBER_EXT_ANALOG_IMAGE_SETTINGS,
                         CY_GRABBER_EXT_ANALOG_IS_CONTRAST,
                         unsigned char );

    IMPLEMENT_PARAMETER( Saturatino,
                         CY_GRABBER_EXT_ANALOG_IMAGE_SETTINGS,
                         CY_GRABBER_EXT_ANALOG_IS_SATURATION,
                         unsigned char );

    IMPLEMENT_PARAMETER( Hue,
                         CY_GRABBER_EXT_ANALOG_IMAGE_SETTINGS,
                         CY_GRABBER_EXT_ANALOG_IS_HUE,
                         unsigned char );

    IMPLEMENT_PARAMETER( AGC,
                         CY_GRABBER_EXT_ANALOG_GAIN,
                         CY_GRABBER_EXT_ANALOG_GAIN_AUTO_GAIN_CONTROL,
                         bool );

    IMPLEMENT_PARAMETER( StaticGainControl,
                         CY_GRABBER_EXT_ANALOG_GAIN,
                         CY_GRABBER_EXT_ANALOG_GAIN_PROGRAMMABLE_GAIN,
                         bool );

    IMPLEMENT_PARAMETER( StaticGainControl1,
                         CY_GRABBER_EXT_ANALOG_GAIN,
                         CY_GRABBER_EXT_ANALOG_GAIN_GAIN_CONTROL_1,
                         unsigned short );

    IMPLEMENT_PARAMETER( StaticGainControl2,
                         CY_GRABBER_EXT_ANALOG_GAIN,
                         CY_GRABBER_EXT_ANALOG_GAIN_GAIN_CONTROL_2,
                         unsigned short );

    IMPLEMENT_PARAMETER( ACGC,
                         CY_GRABBER_EXT_ANALOG_GAIN,
                         CY_GRABBER_EXT_ANALOG_GAIN_AUTO_CHROMA_GAIN_CONTROL,
                         bool );

    IMPLEMENT_PARAMETER( ChromaGain,
                         CY_GRABBER_EXT_ANALOG_GAIN,
                         CY_GRABBER_EXT_ANALOG_GAIN_CHROMA_GAIN,
                         unsigned short );


    CyResult   GetStatus( unsigned char& aColourStandard,
                          bool&          aUnlockHorizontalFreq,
                          bool&          aStandardFieldLength,
                          bool&          aReadyForCapture,
                          bool&          aStableTimeBase,
                          bool&          aField60Hz,
                          bool&          aUnlockedHVLoops,
                          bool&          aInterlaced ) const
    {
        if ( !mGrabber.HasExtension( CY_GRABBER_EXT_ANALOG_STATUS + mID ) )
            return CY_RESULT_NOT_FOUND;
        CyGrabberExtension& lExtension = mGrabber.GetExtension( CY_GRABBER_EXT_ANALOG_STATUS + mID );

        aColourStandard       = lExtension.GetParameterInt ( CY_GRABBER_EXT_ANALOG_STATUS_COLOR_STANDARD );
        aUnlockHorizontalFreq = lExtension.GetParameterBool( CY_GRABBER_EXT_ANALOG_STATUS_FREQUENCY );
        aStandardFieldLength  = lExtension.GetParameterBool( CY_GRABBER_EXT_ANALOG_STATUS_STANDARD_FIELD_LENGTH );
        aReadyForCapture      = lExtension.GetParameterBool( CY_GRABBER_EXT_ANALOG_STATUS_READY_FOR_CAPTURE );
        aStableTimeBase       = lExtension.GetParameterBool( CY_GRABBER_EXT_ANALOG_STATUS_STABLE_TIMEBASE );
        aField60Hz            = lExtension.GetParameterBool( CY_GRABBER_EXT_ANALOG_STATUS_HORIZ_FREQ_LOCKED );
        aUnlockedHVLoops      = lExtension.GetParameterBool( CY_GRABBER_EXT_ANALOG_STATUS_HV_UNLOCKED );
        aInterlaced           = lExtension.GetParameterBool( CY_GRABBER_EXT_ANALOG_STATUS_INTERLACED );

        return CY_RESULT_OK;
    }

    IMPLEMENT_PARAMETER( HSync,
                         CY_GRABBER_EXT_ANALOG_WINDOWING,
                         1111, // not implemented
                         bool );

    IMPLEMENT_PARAMETER( HSyncStart,
                         CY_GRABBER_EXT_ANALOG_WINDOWING,
                         1111, // not implemented
                         short );

    IMPLEMENT_PARAMETER( HSyncStop,
                         CY_GRABBER_EXT_ANALOG_WINDOWING,
                         1111, // not implemented
                         short );

    IMPLEMENT_PARAMETER( VSync,
                         CY_GRABBER_EXT_ANALOG_WINDOWING,
                         CY_GRABBER_EXT_ANALOG_WINDOWING_ENABLED,
                         bool );

    IMPLEMENT_PARAMETER( VSyncStart,
                         CY_GRABBER_EXT_ANALOG_WINDOWING,
                         CY_GRABBER_EXT_ANALOG_WINDOWING_VSTART,
                         short );

    IMPLEMENT_PARAMETER( VSyncStop,
                         CY_GRABBER_EXT_ANALOG_WINDOWING,
                         CY_GRABBER_EXT_ANALOG_WINDOWING_VEND,
                         short );

protected:
    CyResult SetParameter( const CyString& aName,
                           __int64         aValue );
    CyResult GetParameter( const CyString& aName,
                           __int64&        aValue ) const;

    void AddParameters( CyVideoDecoderSAA& aCamera );

protected:
    bool                               mImmediateModification;
    unsigned short                     mID;
    CyGrabber&                         mGrabber;   
    struct CyVideoSettingsSAAInternal* mInternal;
    friend class CyVideoDecoderSAA;
};
#endif // __cplusplus

#endif // __CY_VIDEO_SETTINGS_SAA_H__
