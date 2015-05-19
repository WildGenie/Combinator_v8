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
// File Name....: CySI640.h
//
// Description..: Defines the interface of a CameraLink camera.
//
// *****************************************************************************
//
// $Log$
//
// *****************************************************************************

#ifndef __CY_SI640_H__
#define __CY_SI640_H__

// Headers
/////////////////////////////////////////////////////////////////////////////

// ===== This Project =====
#include "CySiliconImagingLib.h"
#include "CyCameraLink.h"


// Forward-Declaration
/////////////////////////////////////////////////////////////////////////////


// Class
/////////////////////////////////////////////////////////////////////////////

class CySI640 : public CyCameraLink
{
// Constants
public:
    // Common gains
    CY_SI_LIB_API static const unsigned short sGlobalGain;  // Gain 1
    // Monochrome gains 
    CY_SI_LIB_API static const unsigned short sMonoGain;    // Gain 2

    // Colour gains
    CY_SI_LIB_API static const unsigned short sRedGain;     // Gain 2
    CY_SI_LIB_API static const unsigned short sGreen1Gain;  // Gain 3
    CY_SI_LIB_API static const unsigned short sGreen2Gain;  // Gain 4
    CY_SI_LIB_API static const unsigned short sBlueGain;    // Gain 5



// Construction / Destruction
public:
    CY_SI_LIB_API            CySI640( CyGrabber* aGrabber, bool aColor );
    CY_SI_LIB_API virtual    ~CySI640();


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
    //      40
    //      45
    //      50
    //      55
    //      60
    //      65
    //      70
    //      75
    //      80
private:
    const bool mColor;
};


#endif // __CY_CySI640_H__
