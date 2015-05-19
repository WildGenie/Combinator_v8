// *****************************************************************************
//
// $Id$
//
// cy1h22b1
//
// *****************************************************************************
//
//     Copyright (c) 2003, Pleora Technologies Inc., All rights reserved.
//
// *****************************************************************************
//
// File Name....: CySI1920.h
//
// Description..: Defines the interface of a CameraLink camera.
//
// *****************************************************************************
//
// $Log$
//
// *****************************************************************************

#ifndef __CY_SI1920_H__
#define __CY_SI1920_H__

// Headers
/////////////////////////////////////////////////////////////////////////////

// ===== This Project =====
#include "CySiliconImagingLib.h"
#include "CyCameraLink.h"


// Forward-Declaration
/////////////////////////////////////////////////////////////////////////////


// Class
/////////////////////////////////////////////////////////////////////////////

class CySI1920 : public CyCameraLink
{
// Constants
public:
    // Common gains
    CY_SI_LIB_API static const unsigned short sPGAGain;             // Gain 1
    CY_SI_LIB_API static const unsigned short sDigitalGainCoarse;   // Gain 2
    CY_SI_LIB_API static const unsigned short sDigitalGainFine;     // Gain 3

    // Monochrome gains 
    CY_SI_LIB_API static const unsigned short sMonoGain;            // Gain 4

    // Colour gains
    CY_SI_LIB_API static const unsigned short sRedGain;             // Gain 4
    CY_SI_LIB_API static const unsigned short sGreen1Gain;          // Gain 5
    CY_SI_LIB_API static const unsigned short sGreen2Gain;          // Gain 6
    CY_SI_LIB_API static const unsigned short sBlueGain;            // Gain 7


// Construction / Destruction
public:
    CY_SI_LIB_API            CySI1920( CyGrabber* aGrabber, bool aColour );
    CY_SI_LIB_API virtual    ~CySI1920();


// Update Camera
protected:
    CY_SI_LIB_API virtual CyResult InternalUpdate( bool aDeviceReset ) const;
    CY_SI_LIB_API virtual CyResult LocalUpdate   ( bool aDeviceReset ) const;


    // Camera Parameters (use with Set/GetParameter)
    //
    // "Clock Rate"
    //      20
    //      25
    //      30
    //      35
    //      37.5
    //      40
    //      45
    //      48
    //      50
    //      55
    //      60
    //      65
    //      70
    //      73
    //      75
    //      80
    //      85
    //      90


    // Horizontal Blank
    // "Horizontal Blank"
    // unsigned short   5- 1023

    // Horizontal Blank
    // "Horizontal Blank"
    // unsigned short    28 - 255


    // Gamma correction.
    // "Gamma Correction"
    // Boolean

    // FPN Correction
    // "FPN Correction"
    // Boolean

    // FPN Calibration
    // "FPN Calibration"
    // true: perform calibration, lens must be covered.
    //        reverts to false after calibration

    // Deviant Pixel Correction
    // "Deviant Pixel Correction"
    // Boolean

    // Deviant Pixel Level
    // "Deviant Pixel Level"
    // value 0-255


private:
    const bool      mColour;
};


#endif // __CY_CySI1920_H__
