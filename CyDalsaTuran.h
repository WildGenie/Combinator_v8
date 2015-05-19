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
// File Name....: CyDalsaTuran.h
//
// Description..: Defines the interface of a CameraLink camera.
//
// *****************************************************************************
//
// $Log$
//
// *****************************************************************************

#ifndef __CY_DALSA_TURAN_H__
#define __CY_DALSA_TURAN_H__

// Headers
/////////////////////////////////////////////////////////////////////////////

// ===== This Project =====
#include "CyDalsaLib.h"
#include "CyDalsaCamera.h"


// Class
/////////////////////////////////////////////////////////////////////////////

class CyDalsaTuran : public CyDalsaCamera
{
// Constants
public:
    CY_DALSA_LIB_API static const unsigned short sAnalogGain1Index;
    CY_DALSA_LIB_API static const unsigned short sAnalogGain2Index;
    CY_DALSA_LIB_API static const unsigned short sAnalogOffset1Index;
    CY_DALSA_LIB_API static const unsigned short sAnalogOffset2Index;


// Construction / Destruction
public:
    CY_DALSA_LIB_API            CyDalsaTuran( CyGrabber* aGrabber );
    CY_DALSA_LIB_API virtual    ~CyDalsaTuran();


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
    // Turan settings

    // FVAL Pre-trigger
    //      Values: 0-1
    CY_DALSA_LIB_API virtual CyResult SetFVALPreTrigger( unsigned char  aValue );
    CY_DALSA_LIB_API virtual CyResult GetFVALPreTrigger( unsigned char& aValue ) const;

    // FVAL Post-trigger
    //      Values: 0-2
    CY_DALSA_LIB_API virtual CyResult SetFVALPostTrigger( unsigned char  aValue );
    CY_DALSA_LIB_API virtual CyResult GetFVALPostTrigger( unsigned char& aValue ) const;

    // LVAL Pre-trigger
    //      Values: 0-12
    CY_DALSA_LIB_API virtual CyResult SetLVALPreTrigger( unsigned char  aValue );
    CY_DALSA_LIB_API virtual CyResult GetLVALPreTrigger( unsigned char& aValue ) const;

    // LVAL Post-trigger
    //      Values: 0-2
    CY_DALSA_LIB_API virtual CyResult SetLVALPostTrigger( unsigned char  aValue );
    CY_DALSA_LIB_API virtual CyResult GetLVALPostTrigger( unsigned char& aValue ) const;

    // Set processor Configuration
    //  0: Single Processor
    //  1: Dual Processor
    CY_DALSA_LIB_API virtual CyResult SetProcessorConfiguration( unsigned char  aMode );
    CY_DALSA_LIB_API virtual CyResult GetProcessorConfiguration( unsigned char& aMode ) const;

    // Smear Mode
    //  0 - CCD dump
    //  1 - Image dump
    CY_DALSA_LIB_API virtual CyResult SetSmearMode( unsigned char  aMode );
    CY_DALSA_LIB_API virtual CyResult GetSmearMode( unsigned char& aMode ) const;

    // Pixel Reset mode
    // 0: Rising  Edge
    // 1: Falling Edge
    CY_DALSA_LIB_API virtual CyResult SetPixelResetEdge( unsigned char  aEdge );
    CY_DALSA_LIB_API virtual CyResult GetPixelResetEdge( unsigned char& aEdge ) const;

    // Sync  mode
    // 0: Falling Edge  (contrary to pixel reset)
    // 1: Rising  Edge
    CY_DALSA_LIB_API virtual CyResult SetSyncEdge( unsigned char  aEdge );
    CY_DALSA_LIB_API virtual CyResult GetSyncEdge( unsigned char& aEdge ) const;


// Support of extra parameters
    CY_DALSA_LIB_API virtual CyResult SetParameter     ( const CyString& aName,
                                                         unsigned char      aValue );
    CY_DALSA_LIB_API virtual CyResult GetParameter     ( const CyString& aName,
                                                         unsigned char&     aValue ) const;
    
private:
    // Members
    unsigned char mFVALPreTrigger;
    unsigned char mFVALPostTrigger;
    unsigned char mLVALPreTrigger;
    unsigned char mLVALPostTrigger;
    unsigned char mProcessorConfiguration;
    unsigned char mSmearMode;
    unsigned char mPixelResetEdge;
    unsigned char mSyncEdge;

    // Property page
    void*           mPropertyPage;
};


#endif // __CY_DALSA_TURAN_H__

