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
// File Name....: CySI1280.h
//
// Description..: Defines the interface of a CameraLink camera.
//
// *****************************************************************************
//
// $Log$
//
// *****************************************************************************

#ifndef __CY_SI1280_H__
#define __CY_SI1280_H__

// Headers
/////////////////////////////////////////////////////////////////////////////

// ===== This Project =====
#include "CySiliconImagingLib.h"
#include "CyCameraLink.h"


// Forward-Declaration
/////////////////////////////////////////////////////////////////////////////


// Class
/////////////////////////////////////////////////////////////////////////////

class CySI1280 : public CyCameraLink
{
// Construction / Destruction
public:
    CY_SI_LIB_API            CySI1280( CyGrabber*            aGrabber,
                                       bool                  aColour );
    CY_SI_LIB_API virtual    ~CySI1280();


// Update Camera
protected:
    CY_SI_LIB_API virtual CyResult InternalUpdate( bool aDeviceReset ) const;
    CY_SI_LIB_API virtual CyResult LocalUpdate( bool aDeviceReset ) const;


// Show Configuration Dialog
protected:
    CY_SI_LIB_API virtual CyResult AddPropertyPage  ( void* aPropertySheet );
    CY_SI_LIB_API virtual CyResult OnApply          ( void* aPropertyPage );


// Save/load settings from XML
public:
    CY_SI_LIB_API virtual CyResult InternalSave ( CyXMLDocument& aDocument ) const;
    CY_SI_LIB_API virtual CyResult InternalLoad ( CyXMLDocument& aDocument );


public:
    // Fine Black Level
    CY_SI_LIB_API virtual CyResult SetBlackLevelFine( unsigned short  aLevel );
    CY_SI_LIB_API virtual CyResult GetBlackLevelFine( unsigned short& aLevel ) const;


    // Dual Slope mode.  Used in free running mode
    
    CY_SI_LIB_API virtual CyResult SetDualSlope( bool  aEnabled );
    CY_SI_LIB_API virtual CyResult GetDualSlope( bool& aEnabled ) const;

    CY_SI_LIB_API virtual CyResult SetDualSlopeKneePoint( unsigned char  aValue );
    CY_SI_LIB_API virtual CyResult GetDualSlopeKneePoint( unsigned char& aValue ) const;


    // Trigger Shutter timebase

    CY_SI_LIB_API virtual CyResult SetTriggeredShutterTimeBase( unsigned char  aValue );
    CY_SI_LIB_API virtual CyResult GetTriggeredShutterTimeBase( unsigned char& aValue ) const;


    // Clock rate of the camera.
    CY_SI_LIB_API virtual CyResult SetClockRate( float  aRate );
    CY_SI_LIB_API virtual CyResult GetClockRate( float& aRate ) const;

    // Support of extra parameters
    CY_SI_LIB_API virtual CyResult SetParameter     ( const CyString& aName,
                                                      bool               aValue );
    CY_SI_LIB_API virtual CyResult SetParameter     ( const CyString& aName,
                                                      unsigned short     aValue );
    CY_SI_LIB_API virtual CyResult SetParameter     ( const CyString& aName,
                                                      unsigned char      aValue );
    CY_SI_LIB_API virtual CyResult SetParameter     ( const CyString& aName,
                                                      float              aValue );
    CY_SI_LIB_API virtual CyResult GetParameter     ( const CyString& aName,
                                                      bool&              aValue ) const;
    CY_SI_LIB_API virtual CyResult GetParameter     ( const CyString& aName,
                                                      unsigned short&    aValue ) const;
    CY_SI_LIB_API virtual CyResult GetParameter     ( const CyString& aName,
                                                      unsigned char&     aValue ) const;
    CY_SI_LIB_API virtual CyResult GetParameter     ( const CyString& aName,
                                                      float&             aValue ) const;

private:
    // Camera commands
    CY_SI_LIB_API virtual CyResult SendCommand( const char * aCommand, unsigned long aCommandSize ) const;


private:
    bool            mColour;
    bool            mDualSlope;
    unsigned char   mDualSlopeKneePoint;
    unsigned char   mTriggeredShutterTimeBase;
    float           mClockRate;
    unsigned short  mBlackLevelFine;

    // Property page
    void*           mPropertyPage;
};


#endif // __CY_CySI1280_H__
