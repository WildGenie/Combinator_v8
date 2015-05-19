// *****************************************************************************
//
// $Id$
//
// cy1h03b1
//
// *****************************************************************************
//
//     Copyright (c) 2003, Pleora Technologies Inc., All rights reserved.
//
// *****************************************************************************
//
// File Name....: CyCameraLinkExtensionBackwardCompatibility.h
//
// Description..: Defines the base of a camera class.
//
// *****************************************************************************
//
// $Log$
//
// *****************************************************************************

// Types
public:
    enum
    {
        SS_UNUSED,
        SS_UART0
    };
    typedef unsigned long SerialSelectFunction;

// Accessors
public:
    CyResult SetSerialSelectFunction ( unsigned long aFunction )
    {
        return SetParameter( CY_CAMERA_LINK_SERIAL_SELECT, aFunction );
    }

    CyResult GetSerialSelectFunction ( unsigned long& aFunction ) const
    {
        return GetParameter( CY_CAMERA_LINK_SERIAL_SELECT, aFunction );
    }


    CyResult SetDataValidEnabled ( bool  aEnable )
    {
        return SetParameter( CY_CAMERA_LINK_DVAL_ENABLED, aEnable );
    }
    CyResult GetDataValidEnabled ( bool& aEnable ) const
    {
        return GetParameter( CY_CAMERA_LINK_DVAL_ENABLED, aEnable );
    }


    CyResult SetDataValidPolarity( bool  aLow )
    {
        return SetParameter( CY_CAMERA_LINK_DVAL_LOW_POLARITY, aLow );
    }
    CyResult GetDataValidPolarity( bool& aLow ) const
    {
        return GetParameter( CY_CAMERA_LINK_DVAL_LOW_POLARITY, aLow );
    }


    CyResult SetLineValidPolarity( bool  aLow )
    {
        return SetParameter( CY_CAMERA_LINK_LVAL_LOW_POLARITY, aLow );
    }

    CyResult GetLineValidPolarity( bool& aLow ) const
    {
        return GetParameter( CY_CAMERA_LINK_LVAL_LOW_POLARITY, aLow );
    }


    CyResult SetFrameValidPolarity( bool  aLow )
    {
        return SetParameter( CY_CAMERA_LINK_FVAL_LOW_POLARITY, aLow );
    }

    CyResult GetFrameValidPolarity( bool& aLow ) const
    {
        return GetParameter( CY_CAMERA_LINK_FVAL_LOW_POLARITY, aLow );
    }


    CyResult SetLineValidEdgeSensitive( bool  aEnabled )
    {
        return SetParameter( CY_CAMERA_LINK_LVAL_EDGE_SENSITIVE, aEnabled );
    }

    CyResult GetLineValidEdgeSensitive( bool& aEnabled ) const
    {
        return GetParameter( CY_CAMERA_LINK_LVAL_EDGE_SENSITIVE, aEnabled );
    }


    CyResult SetFrameValidEdgeSensitive( bool  aEnabled )
    {
        return SetParameter( CY_CAMERA_LINK_FVAL_EDGE_SENSITIVE, aEnabled );
    }

    CyResult GetFrameValidEdgeSensitive( bool& aEnabled ) const
    {
        return GetParameter( CY_CAMERA_LINK_FVAL_EDGE_SENSITIVE, aEnabled );
    }


    CyResult SetFrameValidFunctionSelect( unsigned char  aFunction )
    {
        return SetParameter( CY_CAMERA_LINK_FVAL_FUNCTION_SELECT, aFunction );
    }

    CyResult GetFrameValidFunctionSelect( unsigned char& aFunction ) const
    {
        return GetParameter( CY_CAMERA_LINK_FVAL_FUNCTION_SELECT, aFunction );
    }


    CyResult SetLineValidFunctionSelect( unsigned char  aFunction )
    {
        return SetParameter( CY_CAMERA_LINK_LVAL_FUNCTION_SELECT, aFunction );
    }

    CyResult GetLineValidFunctionSelect( unsigned char& aFunction ) const
    {
        return GetParameter( CY_CAMERA_LINK_LVAL_FUNCTION_SELECT, aFunction );
    }


    CyResult SetGPIOOutputEnabled( bool  aEnabled )
    {
        return SetParameter( CY_CAMERA_LVDS_GPIO_OUTPUT_ENABLED, aEnabled );
    }

    CyResult GetGPIOOutputEnabled( bool& aEnabled ) const
    {
        return GetParameter( CY_CAMERA_LVDS_GPIO_OUTPUT_ENABLED, aEnabled );
    }

    CyResult GetClockPresence( bool & aPresent, CyGrabber* aGrabber = 0 ) const
    {
        return GetParameter( CY_CAMERA_LINK_CAMERA_CLOCK_PRESENT, aPresent );
    }

