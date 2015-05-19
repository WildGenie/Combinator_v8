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
// File Name....: CyAdimec1600m.h
//
// Description..: Defines the basic of a camera implementation based on CameraLink
//
// *****************************************************************************
//
// $Log$
//
// *****************************************************************************

#ifndef __CY_CAMERA_ADIMEC_1600M_H__
#define __CY_CAMERA_ADIMEC_1600M_H__

// Headers
/////////////////////////////////////////////////////////////////////////////

// ===== This Project =====
#include "CyAdimecCamera.h"


// Class
/////////////////////////////////////////////////////////////////////////////

class CyAdimec1600m : public CyAdimecCamera
{
//
// Types
//
public:
    // Gains indexes
    CY_ADIMEC_LIB_API static const unsigned short sAnalogGain;
    CY_ADIMEC_LIB_API static const unsigned short sDigitalGain;

    // Since there are two black level, we store the values in the
    // gains storage of CyCameraInterface
    CY_ADIMEC_LIB_API static const unsigned short sLeftBlackLevel;
    CY_ADIMEC_LIB_API static const unsigned short sRightBlackLevel;


//
// Construction / Destruction
//
public:
    CY_ADIMEC_LIB_API            CyAdimec1600m( CyGrabber* aGrabber,
                                                bool       aDualOutput );
    CY_ADIMEC_LIB_API virtual    ~CyAdimec1600m();
 

//
// Camera Update Methods
//
protected:
    CY_ADIMEC_LIB_API virtual CyResult InternalUpdate( bool aDeviceReset ) const;
    CY_ADIMEC_LIB_API virtual CyResult LocalUpdate   ( bool aDeviceReset ) const;


//
// Configuration Dialog Methods.
//
protected:
    CY_ADIMEC_LIB_API virtual CyResult AddPropertyPage  ( void* aPropertySheet );
    CY_ADIMEC_LIB_API virtual CyResult OnApply          ( void* aPropertyPage );



//
// XML Storage methods.
//
protected:
    CY_ADIMEC_LIB_API virtual CyResult InternalSave ( CyXMLDocument& aDocument ) const;
    CY_ADIMEC_LIB_API virtual CyResult InternalLoad ( CyXMLDocument& aDocument );




//
// Overridden Parameters
//
    // Offset overrides
    CY_ADIMEC_LIB_API virtual CyResult SetOffsetY( unsigned short  aOffset );
    CY_ADIMEC_LIB_API virtual CyResult GetOffsetY( unsigned short& aOffset ) const;

    // Overridde SetGain in order to verify value based on gain index
    CY_ADIMEC_LIB_API virtual CyResult SetGain  ( unsigned short  aIndex,
                                                  short           aGain );



    // Camera Information Overrides
    CY_ADIMEC_LIB_API virtual CyResult GetVendor       ( CyString& aInfo );
    CY_ADIMEC_LIB_API virtual CyResult GetCameraModel  ( CyString& aInfo );
    CY_ADIMEC_LIB_API virtual CyResult GetSerialNumber ( CyString& aInfo );
    CY_ADIMEC_LIB_API virtual CyResult ResetCamera     ( );


//
// Extra parameters.
//

    // Enable/Disabled Defect Pixel Correction

    CY_ADIMEC_LIB_API virtual CyResult SetDefectPixelCorrection( bool  aEnabled );
    CY_ADIMEC_LIB_API virtual CyResult GetDefectPixelCorrection( bool& aEnabled ) const;


    // Returns Defect pixel information
    //
    //  GetDefectPixelCount returns the number of defect pixel
    //  GetDefectPixelCoord returns the coordinate of a defect based on index (< count)

    CY_ADIMEC_LIB_API virtual CyResult GetDefectPixelCount( unsigned long&  aCount ) const;
    CY_ADIMEC_LIB_API virtual CyResult GetDefectPixelCoord( unsigned long   aIndex,
                                                            unsigned short& aPosX,
                                                            unsigned short& aPosY ) const;


    // CC1 Polarity
    //
    // true = starts on rising edge
    // false = starts on faling edge
    
    CY_ADIMEC_LIB_API virtual CyResult SetCC1Polarity( bool  aOnRisingEdge );
    CY_ADIMEC_LIB_API virtual CyResult GetCC1Polarity( bool& aOnRisingEdge ) const;



    // Overridde Set/GetParameter for all types that we added above.
    CY_ADIMEC_LIB_API virtual CyResult SetParameter     ( const CyString& aName,
                                                          bool               aValue );
    CY_ADIMEC_LIB_API virtual CyResult GetParameter     ( const CyString& aName,
                                                          bool&              aValue ) const;
    CY_ADIMEC_LIB_API virtual CyResult GetParameter     ( const CyString& aName,
                                                          unsigned long&     aValue ) const;


//
// Members
//

private:
    // Offset override
    unsigned short  mOffsetY;

    // Extra parameters
    bool            mDefectPixelCorrection;
    bool            mCC1Polarity;

    // Camera info
    CyString     mCameraModel;
    CyString     mSerialNumber;

    // Property page pointers
    void*           mPropertyPage;

    // Camera mode
    bool            mDualOutput;
    const unsigned long mUnit;
};


#endif // __CY_CAMERA_ADIMEC_1600M_H__
