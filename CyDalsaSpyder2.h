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
// File Name....: CyDalsaSpyder2.h
//
// Description..: Defines the interface of a CameraLink camera.
//
// *****************************************************************************
//
// $Log$
//
// *****************************************************************************

#ifndef __CY_DALSA_SPYDER2_H__
#define __CY_DALSA_SPYDER2_H__

// Headers
/////////////////////////////////////////////////////////////////////////////

// ===== This Project =====
#include "CyDalsaLib.h"
#include "CyDalsaCamera.h"


// Class
/////////////////////////////////////////////////////////////////////////////

class CyDalsaSpyder2 : public CyDalsaCamera
{
// Constants
public:
    CY_DALSA_LIB_API static const unsigned short sAnalogGainIndex;
    CY_DALSA_LIB_API static const unsigned short sDigitalGainIndex;
    CY_DALSA_LIB_API static const unsigned short sAnalogOffsetIndex;


// Construction / Destruction
public:
    CY_DALSA_LIB_API            CyDalsaSpyder2( CyGrabber* aGrabber );
    CY_DALSA_LIB_API virtual    ~CyDalsaSpyder2();


// Update Camera
protected:
    CY_DALSA_LIB_API virtual CyResult LocalUpdate( bool aDeviceReset ) const;


// Show Configuration Dialog
protected:
    CY_DALSA_LIB_API virtual CyResult AddPropertyPage  ( void* aPropertySheet );
    CY_DALSA_LIB_API virtual CyResult OnApply          ( void* aPropertyPage );


// Save/load settings to a file
protected:
    CY_DALSA_LIB_API virtual CyResult InternalSave ( CyXMLDocument& aDocument ) const; 
    CY_DALSA_LIB_API virtual CyResult InternalLoad ( CyXMLDocument& aDocument ); 


    // Camera Information
public:
    // Spyder2 settings

    // When in external sync mode, it is possible to force the use of the pixel reset
    // signal.
    CY_DALSA_LIB_API virtual CyResult SetExternalPixelReset( bool  aEnabled );
    CY_DALSA_LIB_API virtual CyResult GetExternalPixelReset( bool& aEnabled ) const;


// Support of extra parameters
    CY_DALSA_LIB_API virtual CyResult SetParameter     ( const CyString& aName,
                                                         bool               aValue );
    CY_DALSA_LIB_API virtual CyResult GetParameter     ( const CyString& aName,
                                                         bool&              aValue ) const;

    
private:
    // Members
    bool mExternalPixelReset;

    // Property page
    void*           mPropertyPage;
};


#endif // __CY_DALSA_SPYDER2_H__

