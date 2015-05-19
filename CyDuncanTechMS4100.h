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
// File Name....: CyDuncanTechMS4100.h
//
// Description..: DuncanTech MS4100 camera implementation
//
// *****************************************************************************
//
// $Log$
//
// *****************************************************************************

#ifndef __CY_DUNCANTECH_MS4100_H__
#define __CY_DUNCANTECH_MS4100_H__

// Headers
/////////////////////////////////////////////////////////////////////////////

// ===== CyCamLib =====
#include <CyCameraLink.h>

// ===== This Project =====
#include "CyRedLakeLib.h"


// Class
/////////////////////////////////////////////////////////////////////////////

class CyDuncanTechMS4100 : public CyCameraLink
{
//
// Types
//
//  The channels are specifically indexes, use these constants when
//  a channel is used (or for Set/GetGain and Set/GetOffset)
public:
    // Channel indexes
    CY_REDLAKE_LIB_API static const unsigned short sRedChannel;
    CY_REDLAKE_LIB_API static const unsigned short sGreenChannel;
    CY_REDLAKE_LIB_API static const unsigned short sBlueChannel;

    // Data port indexed
    CY_REDLAKE_LIB_API static const unsigned short sPort0Index;
    CY_REDLAKE_LIB_API static const unsigned short sPort1Index;
    CY_REDLAKE_LIB_API static const unsigned short sPort2Index;



//
// Construction / Destruction
//
public:
    CY_REDLAKE_LIB_API            CyDuncanTechMS4100( CyGrabber* aGrabber );
    CY_REDLAKE_LIB_API virtual    ~CyDuncanTechMS4100();
 

//
// Camera Update Methods
//
protected:
    CY_REDLAKE_LIB_API virtual CyResult InternalUpdate( bool aDeviceReset ) const;
    CY_REDLAKE_LIB_API virtual CyResult LocalUpdate   ( bool aDeviceReset ) const;


//
// Configuration Dialog Methods.
//
protected:
    CY_REDLAKE_LIB_API virtual CyResult AddPropertyPage  ( void* aPropertySheet );
    CY_REDLAKE_LIB_API virtual CyResult OnApply          ( void* aPropertyPage );



//
// XML Storage methods.
//
protected:
    CY_REDLAKE_LIB_API virtual CyResult InternalSave ( CyXMLDocument& aDocument ) const;
    CY_REDLAKE_LIB_API virtual CyResult InternalLoad ( CyXMLDocument& aDocument );




//
// Overridden Parameters
//
public:
    // Camera Information Overrides
    CY_REDLAKE_LIB_API virtual CyResult GetVendor       ( CyString& aInfo );
    CY_REDLAKE_LIB_API virtual CyResult GetCameraModel  ( CyString& aInfo );
    CY_REDLAKE_LIB_API virtual CyResult ResetCamera     ( );


//
// Camera Parameters
//
    // Integration time
    // We will not use the standard SetExposureTime, because there is
    // one IT per sensor.

    CY_REDLAKE_LIB_API virtual CyResult SetIntegrationTime( unsigned char  aChannel,
                                                            unsigned long  aTime );
    CY_REDLAKE_LIB_API virtual CyResult GetIntegrationTime( unsigned char  aChannel,
                                                            unsigned long& aTime ) const;
    CY_REDLAKE_LIB_API virtual CyResult ReadIntegrations();

    // Read back the gains from the camera
    CY_REDLAKE_LIB_API virtual CyResult ReadGains();

    // Trigger Source
    // The trigger can be trigger be either the CC1 for the camera link cable or
    // the external BNC input.

    CY_REDLAKE_LIB_API virtual CyResult SetTriggerSource( bool  aCCTriggered );
    CY_REDLAKE_LIB_API virtual CyResult GetTriggerSource( bool& aCCTriggered ) const;

    // Trigger polarity
    CY_REDLAKE_LIB_API virtual CyResult SetTriggerPolarity( bool  aTriggerPositive );
    CY_REDLAKE_LIB_API virtual CyResult GetTriggerPolarity( bool& aTriggerPositive ) const;


    // Output Mux
    // The camera supports the selection of the data to be output by each channel
    // of the 24-bits.
    // The SDK supports RGB only, but an application could change the output
    // of the camera for its purpuses.
    //
    //  Values:
    //      0:  Array 1 ( Green )
    //      1:  Array 2 ( Red )
    //      2:  Array 3 ( Blue )
    //      3:  Processed Red
    //      4:  Processed Green
    //      5:  Processed Blue
    //      6:  Processed Mono
    //      7:  Off

    CY_REDLAKE_LIB_API virtual CyResult SetOutputMux( unsigned char  aPort,
                                                      unsigned char  aValue );
    CY_REDLAKE_LIB_API virtual CyResult GetOutputMux( unsigned char  aPort,
                                                      unsigned char& aValue ) const;

    // Digital Shift
    // A digital shift of 0, 1 or 2 bits can be applied to each channel
    // We do not use the CyCameraInterface::SetDigitalShift, because it supports
    // only one channel

    CY_REDLAKE_LIB_API virtual CyResult SetDigitalShift( unsigned char  aChannel,
                                                         unsigned char  aShift );
    CY_REDLAKE_LIB_API virtual CyResult GetDigitalShift( unsigned char  aChannel,
                                                         unsigned char& aShift ) const;

    // Crosshairs
    // The camera can display a crosshair in the center of the image
    CY_REDLAKE_LIB_API virtual CyResult SetCrosshairs( bool  aEnabled );
    CY_REDLAKE_LIB_API virtual CyResult GetCrosshairs( bool& aEnabled ) const;

    // Auto Exposure
    //
    // Gain controlled or Integration controlled
    // Arrays can be controlled independently or ganged
    // CameraType: Applied on RGB=false or CIR=true
    //

    CY_REDLAKE_LIB_API virtual CyResult SetAutoExposure( bool            aEnabled,
                                                         bool            aIntControlled,
                                                         bool            aGanged,
                                                         bool            aCIR,
                                                         unsigned char   aMinThreshold,
                                                         unsigned char   aMaxThreshold,
                                                         unsigned long   aMaxIntTime,
                                                         unsigned short  aMaxGain );
    CY_REDLAKE_LIB_API virtual CyResult GetAutoExposure( bool&           aEnabled,
                                                         bool&           aIntControlled,
                                                         bool&           aGanged,
                                                         bool&           aCIR,
                                                         unsigned char&  aMinThreshold,
                                                         unsigned char&  aMaxThreshold,
                                                         unsigned long&  aMaxIntTime,
                                                         unsigned short& aMaxGain ) const;

    // White Balance
    //

    CY_REDLAKE_LIB_API virtual CyResult SetWhiteBalance( bool aEnabled,
                                                         bool aIntControlled,
                                                         bool aCameraType,
                                                         bool aExecute );
    CY_REDLAKE_LIB_API virtual CyResult GetWhiteBalance( bool& aEnabled,
                                                         bool& aIntControlled,
                                                         bool& aCameraType ) const;

                                                         
                                                         


    // Averages
    // Returns the average values (in 8-bits) of the data in each array

    CY_REDLAKE_LIB_API virtual CyResult GetAverages( unsigned char& aArray1,
                                                     unsigned char& aArray2,
                                                     unsigned char& aArray3,
                                                     unsigned char& aBayerRed,
                                                     unsigned char& aBayerGreen,
                                                     unsigned char& aBayerBlue ) const;


//
// Extra parameters.
//

    // Overridde Set/GetParameter for all types that we added above.
    CY_REDLAKE_LIB_API virtual CyResult SetParameter     ( const CyString& aName,
                                                           unsigned char      aValue );
    CY_REDLAKE_LIB_API virtual CyResult SetParameter     ( const CyString& aName,
                                                           unsigned short     aValue );
    CY_REDLAKE_LIB_API virtual CyResult SetParameter     ( const CyString& aName,
                                                           unsigned long      aValue );
    CY_REDLAKE_LIB_API virtual CyResult SetParameter     ( const CyString& aName,
                                                           bool               aValue );
    CY_REDLAKE_LIB_API virtual CyResult GetParameter     ( const CyString& aName,
                                                           unsigned char&     aValue ) const;
    CY_REDLAKE_LIB_API virtual CyResult GetParameter     ( const CyString& aName,
                                                           unsigned short&    aValue ) const;
    CY_REDLAKE_LIB_API virtual CyResult GetParameter     ( const CyString& aName,
                                                           unsigned long&     aValue ) const;
    CY_REDLAKE_LIB_API virtual CyResult GetParameter     ( const CyString& aName,
                                                           bool&              aValue ) const;

//
// Communication
//
private:
    CyResult SendCommand  ( unsigned char         aCommand,
                            const unsigned char*  aMessage,
                            unsigned long         aMessageSize,
                            unsigned char*        aResponse,
                            unsigned long*        aResponseSize,
                            unsigned long         aTimeout = 10000 ) const;
    static unsigned char ComputeChecksum( const unsigned char*  aData,
                                          unsigned long         aDataSize );
    static bool IsResponseComplete( const unsigned char* aData,
                                    unsigned long        aDataSize );


//
// Members
//

private:
    // Members
    unsigned long   mIntegrationTime[ 3 ];
    bool            mCCTriggered;
    bool            mTriggerPositive;
    unsigned char   mPortOutput[ 3 ];
    unsigned char   mDigitalShift[ 3 ];
    bool            mCrosshairs;

    // Auto exposure
    bool            mAEEnabled;
    bool            mAEIntControlled;
    bool            mAEGanged;
    bool            mAECameraType;
    unsigned char   mAEMinThreshold;
    unsigned char   mAEMaxThreshold;
    unsigned long   mAEMaxIntegration;
    unsigned short  mAEMaxGain;

    // White balance
    bool            mWBEnabled;
    bool            mWBIntControlled;
    bool            mWBCameraType;

    // Property page pointer
    void*           mPropertyPage;
};


#endif // __CY_DUNCANTECH_MS4100_H__
