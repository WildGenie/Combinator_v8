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
// File Name....: CyAtmelCameliaM1.h
//
// Description..: Defines the interface of a Atmel Camelia.
//
// *****************************************************************************
//
// $Log$
//
// *****************************************************************************

#ifndef __CY_ATMEL_CAMELIA_M1_H__
#define __CY_ATMEL_CAMELIA_M1_H__

// Headers
/////////////////////////////////////////////////////////////////////////////

// ===== This Project =====
#include "CyAtmelLib.h"


// Class
//
// Note:  The Camelia is available as LVDS or Camera Link models.  This class
// is a template class that can derive from either CyCameraLink or CyCameraLVDS.
//
// Both versions are registered in the camera registry.  To use directly, simply
// use CyAtmetCameliaM1<CyCameraLink> or CyAtmetCameliaM1<CyCameraLVDS>.
//
/////////////////////////////////////////////////////////////////////////////

template<class Ancestor>
class CyAtmelCameliaM1: public Ancestor
{
// Construction / Destruction
public:
    CY_ATMEL_LIB_API            CyAtmelCameliaM1( CyGrabber*   aGrabber,
                                                  bool         aSupportsColorMode,
                                                  unsigned int aBaudRate );
    CY_ATMEL_LIB_API virtual    ~CyAtmelCameliaM1();
 

// Update Camera
protected:
    CY_ATMEL_LIB_API virtual CyResult InternalUpdate( bool aDeviceReset ) const;
    CY_ATMEL_LIB_API virtual CyResult LocalUpdate   ( bool aDeviceReset ) const;


// Show Configuration Dialog
protected:
    CY_ATMEL_LIB_API virtual CyResult AddPropertyPage  ( void* aPropertySheet );
    CY_ATMEL_LIB_API virtual CyResult OnApply          ( void* aPropertyPage );


// Save/load settings from XML
public:
    CY_ATMEL_LIB_API virtual CyResult InternalSave ( CyXMLDocument& aDocument ) const;
    CY_ATMEL_LIB_API virtual CyResult InternalLoad ( CyXMLDocument& aDocument );


// Camera Specific parameters
public:
    // Runtime change
    // If enabled, a call to a Set method will apply the change immediately instead of
    // waiting for the next UpdateToCamera.  For valid parameters only.

    CY_ATMEL_LIB_API virtual void SetImmediateChange( bool aEnabled );
    CY_ATMEL_LIB_API virtual bool GetImmediateChange( ) const;


    // Shutter Mode
    //  0: Inactive (always open)
    //  1: Active
    //  2: Inactive (always close)

    CY_ATMEL_LIB_API virtual CyResult SetShutterMode( unsigned char  aMode );
    CY_ATMEL_LIB_API virtual CyResult GetShutterMode( unsigned char& aMode ) const;


    // Shutter Delay
    //  0:  1 ms
    //  1: 10 ms
    //  2: 20 ms
    //  3: 40 ms

    CY_ATMEL_LIB_API virtual CyResult SetShutterDelay( unsigned char  aDelay );
    CY_ATMEL_LIB_API virtual CyResult GetShutterDelay( unsigned char& aDelay ) const;


    // Antiblooming control

    CY_ATMEL_LIB_API virtual CyResult SetAntiBloomingControl( bool  aEnabled );
    CY_ATMEL_LIB_API virtual CyResult GetAntiBloomingControl( bool& aEnabled ) const;


    // Color Mode.
    //
    // For the buffer, we will always have grayscale image, but the camera will send color
    // image as 3 frames, separately.

    CY_ATMEL_LIB_API virtual CyResult SetColorMode( bool  aEnabled );
    CY_ATMEL_LIB_API virtual CyResult GetColorMode( bool& aEnabled ) const;



    // Integration time.
    // B&W Integration is available through the "normal" Set/GetExposureTime
    // For the color channels, we must used the following methods.

    CY_ATMEL_LIB_API virtual CyResult SetExposureTime        ( unsigned long  aTime );

    CY_ATMEL_LIB_API virtual CyResult SetRedIntegrationTime  ( unsigned long  aTime );
    CY_ATMEL_LIB_API virtual CyResult GetRedIntegrationTime  ( unsigned long& aTime ) const;
    CY_ATMEL_LIB_API virtual CyResult SetGreenIntegrationTime( unsigned long  aTime );
    CY_ATMEL_LIB_API virtual CyResult GetGreenIntegrationTime( unsigned long& aTime ) const;
    CY_ATMEL_LIB_API virtual CyResult SetBlueIntegrationTime ( unsigned long  aTime );
    CY_ATMEL_LIB_API virtual CyResult GetBlueIntegrationTime ( unsigned long& aTime ) const;


    // Binning overridde.  IN order to trap the invalid value of 3
    CY_ATMEL_LIB_API virtual CyResult SetBinningX( unsigned short aBinning );
    CY_ATMEL_LIB_API virtual CyResult SetBinningY( unsigned short aBinning );



    // Extra parameter
    CY_ATMEL_LIB_API virtual CyResult SetParameter     ( const CyString& aName,
                                                         unsigned char      aValue );
    CY_ATMEL_LIB_API virtual CyResult SetParameter     ( const CyString& aName,
                                                         unsigned long      aValue );
    CY_ATMEL_LIB_API virtual CyResult SetParameter     ( const CyString& aName,
                                                         bool               aValue );
    CY_ATMEL_LIB_API virtual CyResult GetParameter     ( const CyString& aName,
                                                         unsigned char&     aValue ) const;
    CY_ATMEL_LIB_API virtual CyResult GetParameter     ( const CyString& aName,
                                                         unsigned long&     aValue ) const;
    CY_ATMEL_LIB_API virtual CyResult GetParameter     ( const CyString& aName,
                                                         bool&              aValue ) const;


private:
    // Members
    bool            mImmediateChange;
    unsigned char   mShutterMode;
    unsigned char   mShutterDelay;
    bool            mAntiBlooming;
    bool            mColorMode;
    unsigned long   mRedIntegrationTime;
    unsigned long   mGreenIntegrationTime;
    unsigned long   mBlueIntegrationTime;
    bool            mSupportsColorMode;

    // Property page
    void*           mPropertyPage;
};


#endif // __CY_ATMEL_CAMELIA_M1_H__
