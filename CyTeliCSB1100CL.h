// *****************************************************************************
//
// $Id$
//
//
// *****************************************************************************
//
//     Copyright (c) 2003, Pleora Technologies Inc., All rights reserved.
//
// *****************************************************************************
//
// File Name....: CyTeliCSB1100CL.h
//
// Description..: Defines the interface of a CameraLink camera.
//
// *****************************************************************************
//
// $Log$
//
// *****************************************************************************

#ifndef __CY_TELI_CSB_1100_CL_H__
#define __CY_TELI_CSB_1100_CL_H__

// Headers
/////////////////////////////////////////////////////////////////////////////

// ===== This Project =====
#include "CyTeliLib.h"
#include "CyCameraLink.h"


// Class
/////////////////////////////////////////////////////////////////////////////

class CyTeliCSB1100CL : public CyCameraLink
{
// Construction / Destruction
public:
    CY_TELI_LIB_API            CyTeliCSB1100CL( CyGrabber* aGrabber,
                                                const CyCameraLimits& aLimits,
                                                const CyString& aCameraName );
    CY_TELI_LIB_API virtual    ~CyTeliCSB1100CL();
 

// Update Camera
protected:
    CY_TELI_LIB_API virtual CyResult InternalUpdate( bool aDeviceReset ) const;
    CY_TELI_LIB_API virtual CyResult LocalUpdate   ( bool aDeviceReset ) const;


// Show Configuration Dialog
protected:
    CY_TELI_LIB_API virtual CyResult AddPropertyPage  ( void* aPropertySheet );
    CY_TELI_LIB_API virtual CyResult OnApply          ( void* aPropertyPage );

// Camera Specific parameters
public:
    CY_TELI_LIB_API virtual CyResult SetRollingShutter( bool  aEnabled );
    CY_TELI_LIB_API virtual CyResult GetRollingShutter( bool& aEnabled ) const;

    CY_TELI_LIB_API virtual CyResult SetPixelCorrection( bool  aEnabled );
    CY_TELI_LIB_API virtual CyResult GetPixelCorrection( bool& aEnabled ) const;

    CY_TELI_LIB_API virtual CyResult SetTriggerPolarity( bool  aPositive );
    CY_TELI_LIB_API virtual CyResult GetTriggerPolarity( bool& aPositive ) const;

    CY_TELI_LIB_API virtual CyResult SetGammaCorrection( bool  aGamma );
    CY_TELI_LIB_API virtual CyResult GetGammaCorrection( bool& aGamma ) const;

    // Windowing
    // Windows 0 is ALWAYS active and uses the values in the CyCameraInterface class.

    // Changes the current window. index => 0..15
    CY_TELI_LIB_API virtual CyResult SetCurrentWindow( unsigned char  aIndex );
    CY_TELI_LIB_API virtual CyResult GetCurrentWindow( unsigned char& aIndex ) const;

    // Enables or disables the current window
    CY_TELI_LIB_API virtual CyResult SetWindowEnabled( bool  aEnabled );
    CY_TELI_LIB_API virtual CyResult GetWindowEnabled( bool& aEnabled ) const;

    // Changes the attributes of the current windows
    CY_TELI_LIB_API virtual CyResult SetWindowOffsetX( unsigned short  aOffset );
    CY_TELI_LIB_API virtual CyResult GetWindowOffsetX( unsigned short& aOffset ) const;
    CY_TELI_LIB_API virtual CyResult SetWindowOffsetY( unsigned short  aOffset );
    CY_TELI_LIB_API virtual CyResult GetWindowOffsetY( unsigned short& aOffset ) const;
    CY_TELI_LIB_API virtual CyResult SetWindowSizeX  ( unsigned short  aSize );
    CY_TELI_LIB_API virtual CyResult GetWindowSizeX  ( unsigned short& aSize ) const;
    CY_TELI_LIB_API virtual CyResult SetWindowSizeY  ( unsigned short  aSize );
    CY_TELI_LIB_API virtual CyResult GetWindowSizeY  ( unsigned short& aSize ) const;


    CY_TELI_LIB_API virtual CyResult SetParameter     ( const CyString& aName,
                                                        unsigned char      aValue );
    CY_TELI_LIB_API virtual CyResult SetParameter     ( const CyString& aName,
                                                        bool               aValue );
    CY_TELI_LIB_API virtual CyResult SetParameter     ( const CyString& aName,
                                                        unsigned short     aValue );
    CY_TELI_LIB_API virtual CyResult GetParameter     ( const CyString& aName,
                                                        unsigned char&     aValue ) const;
    CY_TELI_LIB_API virtual CyResult GetParameter     ( const CyString& aName,
                                                        bool&              aValue ) const;
    CY_TELI_LIB_API virtual CyResult GetParameter     ( const CyString& aName,
                                                        unsigned short&    aValue ) const;


// Save/load settings from XML
public:
    CY_TELI_LIB_API virtual CyResult InternalSave ( CyXMLDocument& aDocument ) const;
    CY_TELI_LIB_API virtual CyResult InternalLoad ( CyXMLDocument& aDocument );


private:
    // Members
    bool            mRollingShutter;
    bool            mPixelCorrection;
    bool            mTriggerPolarity;
    bool            mGammaCorrection;
    unsigned char   mCurrentWindow;
    bool            mWindowEnabled[ 16 ];
    unsigned short  mWindowOffsetX[ 16 ];
    unsigned short  mWindowOffsetY[ 16 ];
    unsigned short  mWindowSizeX  [ 16 ];
    unsigned short  mWindowSizeY  [ 16 ];
    const CyString mName;

    // Property pages
    void*           mPropertyPage1;
    void*           mPropertyPage2;
};


#endif // __CY_TELI_CSB_1100_CL_H__