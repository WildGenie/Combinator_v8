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
// File Name....: CyFairchildOsprey.h
//
// Description..: Defines the basic of a camera implementation based on CameraLink
//
// *****************************************************************************
//
// $Log$
//
// *****************************************************************************

#ifndef _CY_FAIRCHILD_OSPREY_H__
#define _CY_FAIRCHILD_OSPREY_H__

// Headers
/////////////////////////////////////////////////////////////////////////////

// ===== CyCamLib =====
#include <CyCameraLink.h>

// ===== This Project =====
#include "CyFairchildLib.h"


// Class
/////////////////////////////////////////////////////////////////////////////

class CyFairchildOsprey : public CyCameraLink
{

//
// Construction / Destruction
//
public:
    CY_FAIRCHILD_LIB_API            CyFairchildOsprey( CyGrabber&            aGrabber,
                                                       const CyCameraLimits& aLimits );
    CY_FAIRCHILD_LIB_API virtual    ~CyFairchildOsprey();
 

//
// Camera Update Methods
//
//  InternalUpdate: Override if settings must be sent to camera using its protocol,
//                  when UpdateToCamera is invoked.
//
//  LocalUpdate (optional): All camera communications can be implemented in this
//                          method, which can be used by OnApply to send camera 
//                          settings while in the configuration dialog.
protected:
    CY_FAIRCHILD_LIB_API virtual CyResult InternalUpdate( bool aDeviceReset ) const;
    CY_FAIRCHILD_LIB_API virtual CyResult LocalUpdate   ( bool aDeviceReset ) const;


//
// Overridden Parameters
//
    CY_FAIRCHILD_LIB_API virtual CyResult ResetCamera     ( );


//
// Extra parameters.
//
//  The following are parameters that are not defined in the CyCameraLink or CyCameraInterface
//  classes, but are need to be available for this new camera implementation.
//
//  The parameters will need to be available through these methods as well as through the
//  Get/SetParameter function of the base class.
//

    // Parameter 1: "Bit Shifting": shifts the 10-bit data (result is still 10-bits)
    // Use Set/GetParameter( "Bit Shifting", unsigned char );
    // Possible values: 0, 1 and 2

    // Parameter 2: "TDI Stages"
    // Use Set/GetParameter( "Gamma Correction", unsigned char );
    // Possible values:
    //
    //      2K      4K
    //  1   24       4
    //  2   32      16
    //  3   48      32
    //  4   64      64
    //  5   96      96


    // Parameter 3: Change LED Color
    // Use Set/GetParameter( "LED", unsigned char );
    // Possible values
    //
    //  0   Amber
    //  1   Green
    //  2   Red
    //  3   Off


    // Parameter 4: ExSync Mode
    // Use Set/GetParameter( "ExSync Mode", unsigned char );
    // Possible values
    //
    //  0   External Sync
    //  1   External Sync, Frame Mode
    //  2   External Frame Mode


    // Parameter 4: Correction Mode
    // Use Set/GetParameter( "Correction Mode", unsigned char );
    // Possible values
    //
    //  1   M1 ( 1st Memory )
    //  2   M2 ( 2nd Memory )
    //  3   Offset Correction
    //  4   Gain Correction
    //  5   No Correction
    //  6   Full Correction


// Communication helper methods
private:
    CyResult    SendCommand( const char* aCommand ) const;
    CyResult    SendCommand( const char* aCommand, long aValue ) const;
    CyResult    SendCommand( const char* aCommand, long aIndex, long aValue ) const;
    CyResult    ReadValue  ( const char* aCommand, CyString& aValue ) const;
};


#endif // _CY_FAIRCHILD_OSPREY_H__
