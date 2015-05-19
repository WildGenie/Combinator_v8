// *****************************************************************************
//
// $Id$
//
// cy1h08b1
//
// *****************************************************************************
//
//     Copyright (c) 2003, Pleora Technologies Inc., All rights reserved.
//
// *****************************************************************************
//
// File Name....: CyDalsa6M03.h
//
// Description..: Defines the interface of a basic dalsa camera CameraLink camera.
//
// *****************************************************************************
//
// $Log$
//
// *****************************************************************************

#ifndef __CY_DALSA_6M03_H__
#define __CY_DALSA_6M03_H__

// Headers
/////////////////////////////////////////////////////////////////////////////

// ===== This Project =====
#include "CyDalsaLib.h"


// ===== CyCamLib =====
#include <CyCameraLVDS.h>


// Forward-Declaration
/////////////////////////////////////////////////////////////////////////////

struct CyDalsa6M03Internal;


// Class
/////////////////////////////////////////////////////////////////////////////

class CyDalsa6M03 : public CyCameraLVDS
{
// Construction / Destruction
public:
    CY_DALSA_LIB_API          CyDalsa6M03( CyGrabber* aGrabber );
    CY_DALSA_LIB_API virtual ~CyDalsa6M03();

// Update Camera
protected:
    CY_DALSA_LIB_API virtual CyResult InternalUpdate( bool aDeviceReset ) const;
    CY_DALSA_LIB_API virtual CyResult LocalUpdate( bool aDeviceReset ) const;


// Show Configuration Dialog
protected:
    CY_DALSA_LIB_API virtual CyResult AddPropertyPage  ( void* aPropertySheet );
    CY_DALSA_LIB_API virtual CyResult OnApply          ( void* aPropertyPage );

    // Camera Information
public:
    CY_DALSA_LIB_API virtual CyResult ResetCamera     ( );

    // If the camera is set in external sync, it is possible to use the serial port
    // to trigger the camera.  This function will set the serial trigger.
    // If the camera in in ExSync Programmable mode, the given exposure time, in
    // MS wil be used.
    CY_DALSA_LIB_API virtual CyResult SetSerialTrigger( unsigned long aExposureTime );


private:
    CyResult    ReadRegister ( unsigned char aAddress, unsigned char& aData ) const;
    CyResult    WriteRegister( unsigned char aAddress, unsigned char* aData, unsigned long aDataSize ) const;

    struct CyDalsa6M03Internal * mInternal;
};


#endif // __CY_DALSA_6M03_H__


