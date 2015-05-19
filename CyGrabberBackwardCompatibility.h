// *****************************************************************************
//
// $Id$
//
// cy1h03b1
//
// *****************************************************************************
//
//     Copyright (c) 2002-2003, Pleora Technologies Inc., All rights reserved.
//
// *****************************************************************************
//
// File Name....: CyGrabberBackwardCompatibility.h
//
// Description..: The present file contains symbol that are defined for 
//                backward-compatibility with a previous version of the SDK
//
// *****************************************************************************
//
// $Log$
//
// *****************************************************************************

#ifndef _CY_GRABBER_BACKWARD_COMPATIBILITY_H_
#define _CY_GRABBER_BACKWARD_COMPATIBILITY_H_

public:

    // ===== Flags =====
    CY_CAM_LIB_API static const unsigned long FLAG_NO_WAIT;
    CY_CAM_LIB_API static const unsigned long FLAG_NO_FLUSH;
    CY_CAM_LIB_API static const unsigned long FLAG_REUSE_SETTINGS;
    CY_CAM_LIB_API static const unsigned long FLAG_GRAB_RECORDING;

    // Windowing Limits
	CY_CAM_LIB_API static const unsigned long  SIZE_X_MAX;
	CY_CAM_LIB_API static const unsigned long  SIZE_X_MIN;
    CY_CAM_LIB_API static const unsigned long  SIZE_Y_MAX;
	CY_CAM_LIB_API static const unsigned long  SIZE_Y_MIN;
    CY_CAM_LIB_API static const unsigned long  OFFSET_X_MAX;
	CY_CAM_LIB_API static const unsigned long  OFFSET_X_MIN;
	CY_CAM_LIB_API static const unsigned long  OFFSET_Y_MAX;
	CY_CAM_LIB_API static const unsigned long  OFFSET_Y_MIN;
	CY_CAM_LIB_API static const unsigned short DECIMATION_X_MAX;
	CY_CAM_LIB_API static const unsigned short DECIMATION_X_MIN;
	CY_CAM_LIB_API static const unsigned short DECIMATION_Y_MAX;
	CY_CAM_LIB_API static const unsigned short DECIMATION_Y_MIN;
	CY_CAM_LIB_API static const unsigned short DECIMATION_BLOCK_X_MAX;
	CY_CAM_LIB_API static const unsigned short DECIMATION_BLOCK_X_MIN;
	CY_CAM_LIB_API static const unsigned short DECIMATION_BLOCK_Y_MAX;
	CY_CAM_LIB_API static const unsigned short DECIMATION_BLOCK_Y_MIN;

    // Pixel Information Limits
	CY_CAM_LIB_API static const unsigned short PIXEL_WIDTH_MAX;
	CY_CAM_LIB_API static const unsigned short PIXEL_WIDTH_MIN;
	CY_CAM_LIB_API static const unsigned short TAP_QTY_MAX;
	CY_CAM_LIB_API static const unsigned short TAP_QTY_MIN;

    // Data Generation Limits
    CY_CAM_LIB_API static const unsigned short FRAME_SKIP_MAX;
    CY_CAM_LIB_API static const unsigned short FRAME_SKIP_MIN;

    // These functions are not un the new grabber, but defined here
    // for backward compatibility
	bool IsConnected( void ) const
    {
        return GetDevice().IsConnected();
    }
    bool IsMulticastSlave( void) const
    {
        return ( ( GetDevice().GetParameterInt( CY_DEVICE_PARAM_DATA_SENDING_MODE ) == CY_DEVICE_DSM_MULTICAST ) &&
                 !GetDevice().GetParameterBool( CY_DEVICE_PARAM_DATA_SENDING_MODE_MASTER ) );
    }
    bool IsStarted( const CyChannel& aChannel ) const
    {
        return IsGrabbing( aChannel );
    }
    bool IsStopped( const CyChannel& aChannel ) const
    {
        return !IsGrabbing( aChannel );
    }

    enum
    {
        PC_CONTINUOUS = CY_GRABBER_PC_CONTINUOUS,
        PC_ONE        = CY_GRABBER_PC_ONE,
        PC_TWO        = CY_GRABBER_PC_TWO
    };
    typedef unsigned long PipeCount;

#define GRABBER_BACKWARD_COMPATIBILITY_SET( aName, aID, aType ) \
    CyResult Set##aName( aType  aValue ) \
    { \
        return SetParameter( aID, aValue ); \
    }

#define GRABBER_BACKWARD_COMPATIBILITY_GET( aName, aID, aType ) \
    aType Get##aName() const \
    { \
        aType lTemp( 0 ); \
        GetParameter( aID, lTemp ); \
        return lTemp; \
    }

#define GRABBER_BACKWARD_COMPATIBILITY( aName, aID, aType ) \
    GRABBER_BACKWARD_COMPATIBILITY_SET( aName, aID, aType ) \
    GRABBER_BACKWARD_COMPATIBILITY_GET( aName, aID, aType )

#define GRABBER_BACKWARD_COMPATIBILITY_SET_CHANNEL( aName, aID, aType ) \
    CyResult Set##aName( aType aValue, const CyChannel& aChannel = CyChannel( 0 ) ) \
        { \
            return SetParameter( aID + aChannel.GetID(), aValue ); \
        }

#define GRABBER_BACKWARD_COMPATIBILITY_GET_CHANNEL( aName, aID, aType ) \
    aType Get##aName( const CyChannel& aChannel = CyChannel( 0 ) ) const \
    { \
        aType lTemp( 0 ); \
        GetParameter( aID + aChannel.GetID(), lTemp ); \
        return lTemp; \
    }

#define GRABBER_BACKWARD_COMPATIBILITY_CHANNEL( aName, aID, aType ) \
    GRABBER_BACKWARD_COMPATIBILITY_SET_CHANNEL( aName, aID, aType ) \
    GRABBER_BACKWARD_COMPATIBILITY_GET_CHANNEL( aName, aID, aType )



    // These parameters are not part of the camera interface any more, but can
    // be obtain throurh the parameter repository instead.
    //
    // Instead we define inline functions for the old functions that automatically search
    // in the repository.
    /////////////////////////////////////////////////////////////////////////////

    GRABBER_BACKWARD_COMPATIBILITY( SizeX, CY_GRABBER_PARAM_SIZE_X, unsigned long );
    GRABBER_BACKWARD_COMPATIBILITY( SizeY, CY_GRABBER_PARAM_SIZE_Y, unsigned long );
    GRABBER_BACKWARD_COMPATIBILITY( OffsetX, CY_GRABBER_PARAM_OFFSET_X, unsigned long );
    GRABBER_BACKWARD_COMPATIBILITY( OffsetY, CY_GRABBER_PARAM_OFFSET_Y, unsigned long );
    GRABBER_BACKWARD_COMPATIBILITY( UndefinedSizeX, CY_GRABBER_PARAM_UNDEFINED_SIZE_X, bool );
    GRABBER_BACKWARD_COMPATIBILITY( UndefinedSizeY, CY_GRABBER_PARAM_UNDEFINED_SIZE_Y, bool );
    GRABBER_BACKWARD_COMPATIBILITY( DecimationX, CY_GRABBER_PARAM_DECIMATION_X, unsigned short );
    GRABBER_BACKWARD_COMPATIBILITY( DecimationY, CY_GRABBER_PARAM_DECIMATION_Y, unsigned short );
    GRABBER_BACKWARD_COMPATIBILITY( DecimationBlockX, CY_GRABBER_PARAM_DECIMATION_BLOCK_X, unsigned short );
    GRABBER_BACKWARD_COMPATIBILITY( DecimationBlockY, CY_GRABBER_PARAM_DECIMATION_BLOCK_Y, unsigned short );

    GRABBER_BACKWARD_COMPATIBILITY( PixelDepth, CY_GRABBER_PARAM_PIXEL_DEPTH, unsigned short );
    GRABBER_BACKWARD_COMPATIBILITY( TapQuantity, CY_GRABBER_PARAM_TAP_QUANTITY, unsigned short );
    GRABBER_BACKWARD_COMPATIBILITY( RGBEnabled, CY_GRABBER_PARAM_RGB_ENABLED, bool );
    GRABBER_BACKWARD_COMPATIBILITY( Interlaced, CY_GRABBER_PARAM_INTERLACED, bool );
    GRABBER_BACKWARD_COMPATIBILITY( Normalized, CY_GRABBER_PARAM_NORMALIZED, bool );
    GRABBER_BACKWARD_COMPATIBILITY( Packed, CY_GRABBER_PARAM_PACKED, bool );

    GRABBER_BACKWARD_COMPATIBILITY( InterlacedFieldMode, CY_GRABBER_PARAM_INTERLACED_FIELD_MODE, unsigned char );
    GRABBER_BACKWARD_COMPATIBILITY( ImageSequenceInData, CY_GRABBER_PARAM_IMAGE_SEQUENCE_IN_DATA, bool );
    GRABBER_BACKWARD_COMPATIBILITY( WaterLevel, CY_GRABBER_PARAM_WATER_LEVEL, unsigned char );
    GRABBER_BACKWARD_COMPATIBILITY( PixelShifting, CY_GRABBER_PARAM_PIXEL_SHIFTING, unsigned char );
    GRABBER_BACKWARD_COMPATIBILITY( PixelInversion, CY_GRABBER_PARAM_PIXEL_INVERSION, bool );
    GRABBER_BACKWARD_COMPATIBILITY( PortMapping, CY_GRABBER_PARAM_PORT_MAPPING, unsigned char );
    GRABBER_BACKWARD_COMPATIBILITY( ImageSize, CY_GRABBER_PARAM_IMAGE_SIZE, unsigned long );
    CyResult GetImageSize( unsigned long *aVal ) const
    {
        *aVal = GetImageSize();
        return CY_RESULT_OK;
    }

    GRABBER_BACKWARD_COMPATIBILITY_CHANNEL( ForceSingleShot, CY_GRABBER_PARAM_FORCE_SINGLE_SHOT, bool );
    GRABBER_BACKWARD_COMPATIBILITY_CHANNEL( LineScan, CY_GRABBER_PARAM_LINE_SCAN, bool );
    GRABBER_BACKWARD_COMPATIBILITY_CHANNEL( FrameSkip, CY_GRABBER_PARAM_FRAME_SKIP, unsigned short );
    GRABBER_BACKWARD_COMPATIBILITY_CHANNEL( GPIOTrigger, CY_GRABBER_PARAM_GPIO_TRIGGER, bool );
    GRABBER_BACKWARD_COMPATIBILITY_CHANNEL( AutoInternalRetrigger, CY_GRABBER_PARAM_AUTO_INTERNAL_RETRIGGER, bool );
    GRABBER_BACKWARD_COMPATIBILITY_CHANNEL( PipeCount, CY_GRABBER_PARAM_PIPE_COUNT, unsigned long );


    void EnableBadImagePassthrough( bool aEnabled )
    {
        SetParameter( CY_GRABBER_PARAM_BAD_IMAGE_PASSTHROUGH, aEnabled );
    }
    bool IsBadImagePassthroughEnabled() const
    {
        return GetParameterBool( CY_GRABBER_PARAM_BAD_IMAGE_PASSTHROUGH );
    }
    void IgnoreMissingPackets( bool aEnabled )
    {
        SetParameter( CY_GRABBER_PARAM_IGNORE_MISSING_PACKETS, aEnabled );
    }
    bool IgnoringMissingPackets() const
    {
        return GetParameterBool( CY_GRABBER_PARAM_IGNORE_MISSING_PACKETS );
    }

    CyResult SetImageGenerator( bool aEnabled )
    {
        return GetDevice().SetParameter( CY_DEVICE_PARAM_DATA_GENERATOR, aEnabled );
    }

    bool GetImageGenerator() const
    {
        return GetDevice().GetParameterBool( CY_DEVICE_PARAM_DATA_GENERATOR );
    }


#undef GRABBER_BACKWARD_COMPATIBILITY_SET
#undef GRABBER_BACKWARD_COMPATIBILITY_GET
#undef GRABBER_BACKWARD_COMPATIBILITY
#undef GRABBER_BACKWARD_COMPATIBILITY_SET_CHANNEL
#undef GRABBER_BACKWARD_COMPATIBILITY_GET_CHANNEL
#undef GRABBER_BACKWARD_COMPATIBILITY_CHANNEL

#endif // _CY_GRABBER_BACKWARD_COMPATIBILITY_H_
