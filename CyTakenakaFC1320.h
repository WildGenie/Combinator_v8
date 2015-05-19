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
// File Name....: CyTakenakaFC1320.h
//
// Description..: Defines the basic of a camera implementation based on CameraLink
//
// *****************************************************************************
//
// $Log$
//
// *****************************************************************************

#ifndef __CY_TAKENAKA_FC1320_H__
#define __CY_TAKENAKA_FC1320_H__

// Headers
/////////////////////////////////////////////////////////////////////////////

// ===== CyCamLib =====
#include <CyCameraLink.h>

// ===== This Project =====
#include "CyTakenakaLib.h"


// Class
/////////////////////////////////////////////////////////////////////////////

class CyTakenakaFC1320: public CyCameraLink
{
//
// Construction / Destruction
//
public:
    CY_TAKENAKA_LIB_API            CyTakenakaFC1320( CyGrabber* aGrabber );
    CY_TAKENAKA_LIB_API virtual    ~CyTakenakaFC1320();
 

//
// Camera Update Methods
//
protected:
    CY_TAKENAKA_LIB_API virtual CyResult InternalUpdate( bool aDeviceReset ) const;
    CY_TAKENAKA_LIB_API virtual CyResult LocalUpdate   ( bool aDeviceReset ) const;


//
// Configuration Dialog Methods.
//
protected:
    CY_TAKENAKA_LIB_API virtual CyResult AddPropertyPage  ( void* aPropertySheet );
    CY_TAKENAKA_LIB_API virtual CyResult OnApply          ( void* aPropertyPage );



//
// XML Storage methods.
//
protected:
    CY_TAKENAKA_LIB_API virtual CyResult InternalSave ( CyXMLDocument& aDocument ) const;
    CY_TAKENAKA_LIB_API virtual CyResult InternalLoad ( CyXMLDocument& aDocument );




//
// Extra parameters.
//

    // We can use a direct value (0001H to ffffH ) or a "dial" value
    // When using a direct value, the value is stored in Get/SetExposureTime
    CY_TAKENAKA_LIB_API virtual CyResult SetDirectShutter( bool  aEnabled );
    CY_TAKENAKA_LIB_API virtual CyResult GetDirectShutter( bool& aEnabled ) const;

    // Set the shutter value (when not using a direct value)
    CY_TAKENAKA_LIB_API virtual CyResult SetShutterValue( unsigned char  aValue );
    CY_TAKENAKA_LIB_API virtual CyResult GetShutterValue( unsigned char& aValue ) const;

    // Long Time Shutter mode (as opposed to high-speed)
    CY_TAKENAKA_LIB_API virtual CyResult SetLongTimeShutterMode( bool  aEnabled );
    CY_TAKENAKA_LIB_API virtual CyResult GetLongTimeShutterMode( bool& aEnabled ) const;

    // Double frame rate.  Camera will send half the number of lines, thus doubling
    // the frate rate.  Height must adjusted accordingly
    CY_TAKENAKA_LIB_API virtual CyResult SetDoubleFrameRead( bool  aEnabled );
    CY_TAKENAKA_LIB_API virtual CyResult GetDoubleFrameRead( bool& aEnabled ) const;

    // Shutter dial exposure values.  Changes the exposure value associated with
    // a shutter dial value.
    // Applicable to either high-speed shutter or long time shutter.

    CY_TAKENAKA_LIB_API virtual CyResult SetShutterSwitchValue( bool            aLongTimeShutterMode,
                                                                unsigned char   aIndex,
                                                                unsigned short  aValue );
    CY_TAKENAKA_LIB_API virtual CyResult GetShutterSwitchValue( bool            aLongTimeShutterMode,
                                                                unsigned char   aIndex,
                                                                unsigned short& aValue ) const;



    // Set/GetParameter Overrides
    CY_TAKENAKA_LIB_API virtual CyResult SetParameter     ( const CyString& aName,
                                                            bool               aValue );
    CY_TAKENAKA_LIB_API virtual CyResult SetParameter     ( const CyString& aName,
                                                            unsigned char      aValue );
    CY_TAKENAKA_LIB_API virtual CyResult SetParameter     ( const CyString& aName,
                                                            unsigned short     aValue );
    CY_TAKENAKA_LIB_API virtual CyResult GetParameter     ( const CyString& aName,
                                                            bool&              aValue ) const;
    CY_TAKENAKA_LIB_API virtual CyResult GetParameter     ( const CyString& aName,
                                                            unsigned char&     aValue ) const;
    CY_TAKENAKA_LIB_API virtual CyResult GetParameter     ( const CyString& aName,
                                                            unsigned short&    aValue ) const;

//
// Camera Communication utilities.
//
private:
    virtual CyResult SendCommand ( const unsigned char* aCommand,
                                   unsigned long        aCommandSize,
                                   unsigned char*       aResponse,
                                   unsigned long*       aResponseSize ) const;


//
// Members
//

private:
    bool            mDirectShutter;
    unsigned char   mShutterValue;
    bool            mLongTimeShutter;
    bool            mDoubleFrameRead;
    unsigned long   mShutterValues[2][10]; // 0 is high-speed and 1 is long-time

    // Property page pointer.
    void*           mPropertyPage;
};


#endif // __CY_TAKENAKA_FC1320_H__
