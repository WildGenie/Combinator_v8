// *****************************************************************************
//
// $Id$
//
// cy1h07b1
//
// *****************************************************************************
//
//     Copyright (c) 2003, Pleora Technologies Inc., All rights reserved.
//
// *****************************************************************************
//
// File Name....: CyPulnixTMC6700.h
//
// Description..: Defines the interface of a CameraLink camera.
//
// *****************************************************************************
//
// $Log$
//
// *****************************************************************************

#ifndef __CY_PULNIX_TMCD6700CL_H__
#define __CY_PULNIX_TMCD6700CL_H__

// Headers
/////////////////////////////////////////////////////////////////////////////

// ===== This Project =====
#include "CyPulnixLib.h"
#include "CyCameraLink.h"


// Forward-Declaration
/////////////////////////////////////////////////////////////////////////////

class CyPulnixProtocol;


// Class
/////////////////////////////////////////////////////////////////////////////

class CyPulnixTMC6700 : public CyCameraLink
{
// types and constants
public:
    // Gain indexes
    CY_PULNIX_LIB_API static const unsigned short sVCAGainIndex;
    CY_PULNIX_LIB_API static const unsigned short sDSPGainIndex;

    // Offset indexes
    CY_PULNIX_LIB_API static const unsigned short sADCOffsetIndex;
    CY_PULNIX_LIB_API static const unsigned short sWhiteBalanceBlueOffsetIndex;
    CY_PULNIX_LIB_API static const unsigned short sWhiteBalanceRedOffsetIndex;

    // Black level offsets are actually from -128 to 127.  Since the
    // offset function of CyCameraInterface is an unsigned short, we
    // will use add 128 to the actual value to bring it from 0 to 255.
    CY_PULNIX_LIB_API static const unsigned short sBlueOffsetIndex;
    CY_PULNIX_LIB_API static const unsigned short sGreenOffsetIndex;
    CY_PULNIX_LIB_API static const unsigned short sRedOffsetIndex;

// Construction / Destruction
public:
    CY_PULNIX_LIB_API            CyPulnixTMC6700( CyGrabber*            aGrabber,
                                                  const CyCameraLimits& aLimits );
    CY_PULNIX_LIB_API virtual    ~CyPulnixTMC6700();
 

// Update Camera
protected:
    CY_PULNIX_LIB_API virtual CyResult InternalUpdate( bool aDeviceReset ) const;
    CY_PULNIX_LIB_API virtual CyResult LocalUpdate( bool aDeviceReset ) const;


// Show Configuration Dialog
protected:
    CY_PULNIX_LIB_API virtual CyResult AddPropertyPage  ( void* aPropertySheet );
    CY_PULNIX_LIB_API virtual CyResult OnApply          ( void* aPropertyPage );


// Save/load settings from XML
public:
    CY_PULNIX_LIB_API virtual CyResult InternalSave ( CyXMLDocument& aDocument ) const;
    CY_PULNIX_LIB_API virtual CyResult InternalLoad ( CyXMLDocument& aDocument );


// Camera specific parameters
public:
    // Change the RAM bank of the camera.  From 1 to 4.
    CY_PULNIX_LIB_API virtual CyResult SetRAMBank( unsigned char  aBank );
    CY_PULNIX_LIB_API virtual CyResult GetRAMBank( unsigned char& aBank ) const;


    // Shutter Mode
    //  Normal: Uses the shutter speed associated with the shutter dial
    //  Direct: Uses the shutter speed associated with the direct mode
    CY_PULNIX_LIB_API virtual CyResult  SetShutterMode( bool  aDirect ); 
    CY_PULNIX_LIB_API virtual CyResult  GetShutterMode( bool& aDirect ) const;

    // Shutter Dial.
    // Sets the dial value for a normal shutter. ( 0..9 ).  Unsigned in direct mode.
    CY_PULNIX_LIB_API virtual CyResult  SetShutterDial( unsigned char  aDial );
    CY_PULNIX_LIB_API virtual CyResult  GetShutterDial( unsigned char& aDial ) const;


    // Set the Shutter preset values.
    // There are 10 values ( from 0 to 9 ) for the manual shutter and 9 values
    // ( from 1 to 9 ).
    CY_PULNIX_LIB_API virtual CyResult  SetManualShutterPreset( unsigned char   aIndex, 
                                                                unsigned short  aValue );
    CY_PULNIX_LIB_API virtual CyResult  GetManualShutterPreset( unsigned char   aIndex, 
                                                                unsigned short& aValue ) const;
    CY_PULNIX_LIB_API virtual CyResult  SetAsyncShutterPreset ( unsigned char   aIndex, 
                                                                unsigned short  aValue );
    CY_PULNIX_LIB_API virtual CyResult  GetAsyncShutterPreset ( unsigned char   aIndex, 
                                                                unsigned short& aValue ) const;
    CY_PULNIX_LIB_API virtual CyResult  SetManualDirectShutter( unsigned short  aValue );
    CY_PULNIX_LIB_API virtual CyResult  GetManualDirectShutter( unsigned short& aValue ) const;
    CY_PULNIX_LIB_API virtual CyResult  SetAsyncDirectShutter ( unsigned short  aValue );
    CY_PULNIX_LIB_API virtual CyResult  GetAsyncDirectShutter ( unsigned short& aValue ) const;


    // Gamma correction
    CY_PULNIX_LIB_API virtual CyResult  SetGammaCorrection( bool  aEnabled );
    CY_PULNIX_LIB_API virtual CyResult  GetGammaCorrection( bool& aEnabled ) const;


    // Edge Enhancement.
    //      Mode:
    //          0: Bypass
    //          1: Horizontal
    //          2: Vertical
    //          3: H & V
    //
    //      Level:
    //          0: Max Enhancement level
    //          1: 
    //          2:
    //          3: Min Enhancement level
    CY_PULNIX_LIB_API virtual CyResult  SetEdgeEnhMode( unsigned char  aMode );
    CY_PULNIX_LIB_API virtual CyResult  GetEdgeEnhMode( unsigned char& aMode ) const;
    CY_PULNIX_LIB_API virtual CyResult  SetEdgeEnhLevel( unsigned char  aLevel );
    CY_PULNIX_LIB_API virtual CyResult  GetEdgeEnhLevel( unsigned char& aLevel ) const;



    // White Balance
    //
    // WB can be internal or external.  When external, it uses the value specified (see below).
    CY_PULNIX_LIB_API virtual CyResult  SetExternalWhiteBalance( bool  aExternal );
    CY_PULNIX_LIB_API virtual CyResult  GetExternalWhiteBalance( bool& aExternal ) const;


    // ADC Reference Top
    CY_PULNIX_LIB_API virtual CyResult  SetADCReferenceTop( unsigned char  aValue );
    CY_PULNIX_LIB_API virtual CyResult  GetADCReferenceTop( unsigned char&  aValue ) const;


    // Color Matrix.
    //
    //  [ Ro ]   [ RR RG RB ]   [ Ri ]
    //  [ Go ] = [ GR GG GB ] X [ Gi ]
    //  [ Bo ]   [ BR BG BB ]   [ Bi ]
    //
    // Note: The color matrix will be available 
    CY_PULNIX_LIB_API virtual CyResult  SetColorMatrix( float  aRR,  float  aRG, float  aRB,
                                                        float  aGR,  float  aGG, float  aGB,
                                                        float  aBR,  float  aBG, float  aBB );
    CY_PULNIX_LIB_API virtual CyResult  GetColorMatrix( float& aRR,  float& aRG, float& aRB,
                                                        float& aGR,  float& aGG, float& aGB,
                                                        float& aBR,  float& aBG, float& aBB ) const;


    // Extra parameter
    CY_PULNIX_LIB_API virtual CyResult SetParameter     ( const CyString& aName,
                                                          unsigned char      aValue );
    CY_PULNIX_LIB_API virtual CyResult SetParameter     ( const CyString& aName,
                                                          unsigned short     aValue );
    CY_PULNIX_LIB_API virtual CyResult SetParameter     ( const CyString& aName,
                                                          float              aValue );
    CY_PULNIX_LIB_API virtual CyResult SetParameter     ( const CyString& aName,
                                                          bool               aValue );
    CY_PULNIX_LIB_API virtual CyResult GetParameter     ( const CyString& aName,
                                                          unsigned char&     aValue ) const;
    CY_PULNIX_LIB_API virtual CyResult GetParameter     ( const CyString& aName,
                                                          unsigned short&    aValue ) const;
    CY_PULNIX_LIB_API virtual CyResult GetParameter     ( const CyString& aName,
                                                          float&             aValue ) const;
    CY_PULNIX_LIB_API virtual CyResult GetParameter     ( const CyString& aName,
                                                          bool&              aValue ) const;


private:
    // Members
    CyPulnixProtocol*   mProtocol;
    unsigned char       mRAMBank;
    bool                mDirectShutter;
    unsigned char       mShutterDial;
    unsigned short      mManualShutterPreset[9];
    unsigned short      mAsyncShutterPreset [8];
    unsigned short      mDirectManualShutter;
    unsigned short      mDirectAsyncShutter;
    bool                mGammaCorrection;
    unsigned char       mEdgeEnhMode;
    unsigned char       mEdgeEnhLevel;
    bool                mExternalWB;
    unsigned char       mADCRefTop;
    float               mColorMatrix[3][3];

    // Property page
    void*           mPropertyPage;
};


#endif // __CY_PULNIX_TMCD6700CL_H__