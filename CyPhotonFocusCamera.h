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
// File Name....: CyPhotonFocusCamera.h
//
// Description..: Defines the interface of a CameraLink camera.
//
// *****************************************************************************
//
// $Log$
//
// *****************************************************************************

#ifndef __CY_PHOTONFOCUS_CAMERA_H__
#define __CY_PHOTONFOCUS_CAMERA_H__

// Headers
/////////////////////////////////////////////////////////////////////////////

// ===== This Project =====
#include "CyPhotonFocusLib.h"
#include <CyCameraLink.h>

// Forward-Declaration
/////////////////////////////////////////////////////////////////////////////

struct PFCamera;


// Class
/////////////////////////////////////////////////////////////////////////////

class CyPhotonFocusCamera : public CyCameraLink
{
// Construction / Destruction
public:
    CY_PHOTONFOCUS_LIB_API            CyPhotonFocusCamera( CyGrabber*            aGrabber,
                                                           const CyCameraLimits& aLimits,
                                                           const CyString&       aName,
                                                           bool                  aEvenParity );
protected:
    CY_PHOTONFOCUS_LIB_API            CyPhotonFocusCamera( CyGrabber*            aGrabber,
                                                           const CyCameraLimits& aLimits,
                                                           const CyString&       aName,
                                                           const char * *        aLabels,
                                                           bool                  aEvenParity );
public:
    CY_PHOTONFOCUS_LIB_API virtual    ~CyPhotonFocusCamera();


// Update Camera
protected:
    CY_PHOTONFOCUS_LIB_API virtual CyResult InternalUpdate( bool aDeviceReset ) const;
    CY_PHOTONFOCUS_LIB_API virtual CyResult LocalUpdate( bool aDeviceReset ) const;


// Show Configuration Dialog
protected:
    CY_PHOTONFOCUS_LIB_API virtual CyResult AddPropertyPage  ( void* aPropertySheet );
    CY_PHOTONFOCUS_LIB_API virtual CyResult OnApply          ( void* aPropertyPage );


// Save/load settings to a file
protected:
    CY_PHOTONFOCUS_LIB_API virtual CyResult InternalSave ( CyXMLDocument& aDocument ) const; 
    CY_PHOTONFOCUS_LIB_API virtual CyResult InternalLoad ( CyXMLDocument& aDocument ); 


    // Camera Information
public:
    CY_PHOTONFOCUS_LIB_API virtual CyResult GetVendor       ( CyString& aInfo );
    CY_PHOTONFOCUS_LIB_API virtual CyResult GetCameraModel  ( CyString& aInfo );
    CY_PHOTONFOCUS_LIB_API virtual CyResult GetProductID    ( CyString& aInfo );
    CY_PHOTONFOCUS_LIB_API virtual CyResult GetSerialNumber ( CyString& aInfo );
    CY_PHOTONFOCUS_LIB_API virtual CyResult ResetCamera     ( );

    // Parameters
    CY_PHOTONFOCUS_LIB_API virtual CyResult SetLinePause( unsigned short  aLevel );
    CY_PHOTONFOCUS_LIB_API virtual CyResult GetLinePause( unsigned short& aLevel ) const;
    CY_PHOTONFOCUS_LIB_API virtual CyResult SetHighGainActive( bool  aEnabled );
    CY_PHOTONFOCUS_LIB_API virtual CyResult GetHighGainActive( bool& aEnabled ) const;
    CY_PHOTONFOCUS_LIB_API virtual CyResult SetLUTEnabled( bool  aEnabled );
    CY_PHOTONFOCUS_LIB_API virtual CyResult GetLUTEnabled( bool& aEnabled ) const;
    CY_PHOTONFOCUS_LIB_API virtual CyResult SetClockSource( bool  aEnabled );
    CY_PHOTONFOCUS_LIB_API virtual CyResult GetClockSource( bool& aEnabled ) const;
    CY_PHOTONFOCUS_LIB_API virtual CyResult SetClockInvert( bool  aClockInvert );
    CY_PHOTONFOCUS_LIB_API virtual CyResult GetClockInvert( bool& aClockInvert ) const;
    CY_PHOTONFOCUS_LIB_API virtual CyResult SetSkim( bool  aEnabled );
    CY_PHOTONFOCUS_LIB_API virtual CyResult GetSkim( bool& aEnabled ) const;
    CY_PHOTONFOCUS_LIB_API virtual CyResult SetConstantFrameRate( bool  aEnabled );
    CY_PHOTONFOCUS_LIB_API virtual CyResult GetConstantFrameRate( bool& aEnabled ) const;

    // LinLog settings
    CY_PHOTONFOCUS_LIB_API virtual CyResult SetLinLog( unsigned short  aLinLog );
    CY_PHOTONFOCUS_LIB_API virtual CyResult GetLinLog( unsigned short&  aLinLog ) const;
    CY_PHOTONFOCUS_LIB_API virtual CyResult SetLinLog2L( unsigned short  aLinLog );
    CY_PHOTONFOCUS_LIB_API virtual CyResult GetLinLog2L( unsigned short&  aLinLog ) const;
    CY_PHOTONFOCUS_LIB_API virtual CyResult SetLinLog2H( unsigned short  aLinLog );
    CY_PHOTONFOCUS_LIB_API virtual CyResult GetLinLog2H( unsigned short&  aLinLog ) const;
    CY_PHOTONFOCUS_LIB_API virtual CyResult SetLinLog2F( float  aLinLog );
    CY_PHOTONFOCUS_LIB_API virtual CyResult GetLinLog2F( float&  aLinLog ) const;


    // 10-bits to 8-bits look up tables
    CY_PHOTONFOCUS_LIB_API virtual unsigned int GetLUTCount() const;
    CY_PHOTONFOCUS_LIB_API virtual CyResult SetActiveLUT( unsigned char  aLUT );
    CY_PHOTONFOCUS_LIB_API virtual CyResult GetActiveLUT( unsigned char& aLUT  ) const;
    CY_PHOTONFOCUS_LIB_API virtual CyResult SetNonVolatileLUT( bool  aEnabled );
    CY_PHOTONFOCUS_LIB_API virtual CyResult GetNonVolatileLUT( bool& aEnabled ) const;
    CY_PHOTONFOCUS_LIB_API virtual CyResult SetLUTData( unsigned char        aLUT,
                                                  const unsigned char* aData );
    CY_PHOTONFOCUS_LIB_API virtual CyResult GetLUTData( unsigned char        aLUT,
                                                  unsigned char*       aData ) const;

// Support of extra parameters
    CY_PHOTONFOCUS_LIB_API virtual CyResult SetParameter     ( const CyString& aName,
                                                         unsigned char      aValue );
    CY_PHOTONFOCUS_LIB_API virtual CyResult SetParameter     ( const CyString& aName,
                                                         unsigned short     aValue );
    CY_PHOTONFOCUS_LIB_API virtual CyResult SetParameter     ( const CyString& aName,
                                                         float              aValue );
    CY_PHOTONFOCUS_LIB_API virtual CyResult SetParameter     ( const CyString& aName,
                                                         bool               aValue );
    CY_PHOTONFOCUS_LIB_API virtual CyResult GetParameter     ( const CyString& aName,
                                                         unsigned char&     aValue ) const;
    CY_PHOTONFOCUS_LIB_API virtual CyResult GetParameter     ( const CyString& aName,
                                                         unsigned short&    aValue ) const;
    CY_PHOTONFOCUS_LIB_API virtual CyResult GetParameter     ( const CyString& aName,
                                                         float&             aValue ) const;
    CY_PHOTONFOCUS_LIB_API virtual CyResult GetParameter     ( const CyString& aName,
                                                         bool&              aValue ) const;

    
// Limits
protected:
    unsigned short  mMinLinePause;
    unsigned short  mMaxLinePause;


private:
    // Members
    PFCamera*       mCameraPort;
    unsigned short  mLinePause;
    bool            mHighGainActive;
    bool            mLUTEnabled;
    bool            mClockSource;
    bool            mClockInvert;
    bool            mSkimEnabled;
    bool            mConstantFrameRate;
    unsigned short  mLinLog;
    unsigned short  mLinLog2L;
    unsigned short  mLinLog2H;
    float           mLinLog2F;

    // Look-Up table, some cameras don't have editable or selectable LUT
    unsigned int    mLUTCount;
    struct LookUpTable
    {
        unsigned char mData[ 1024 ];
    };
    bool            mLUTUpdated[4];
    LookUpTable     mLUTs[4];
    unsigned int    mActiveLUT;
    bool            mNonVolatileLUT;

    // Cache of the last setting sent to camera to avoid
    // resending for optimization
    mutable CyPixelTypeID   mCachedPixelTypeID;
    mutable CyCameraInterface::SynchronizationMode
                            mCachedSyncMode;
    mutable unsigned long   mCachedExposureTime;
    mutable double          mCachedFrameRate;
    mutable unsigned short  mCachedOffsetX;
    mutable unsigned short  mCachedOffsetY;
    mutable unsigned short  mCachedSizeX;
    mutable unsigned short  mCachedSizeY;
    mutable short           mCachedGain;
    mutable short           mCachedOffset;
    mutable bool            mCachedImageFlip;
    mutable unsigned short  mCachedLinePause;
    mutable bool            mCachedHighGainActive;
    mutable bool            mCachedLUTEnabled;
    mutable bool            mCachedClockSource;
    mutable bool            mCachedClockInvert;
    mutable bool            mCachedSkimEnabled;
    mutable bool            mCachedConstantFrameRate;
    mutable unsigned short  mCachedLinLog;
    mutable unsigned short  mCachedLinLog2L;
    mutable unsigned short  mCachedLinLog2H;
    mutable float           mCachedLinLog2F;
    mutable unsigned int    mCachedLUTCount;
    mutable LookUpTable     mCachedLUTs[4];
    mutable unsigned int    mCachedActiveLUT;

    // Property page
    const CyString    mName;
    const char * *    mLabels;
    bool              mEvenParity;
    void*             mPropertyPage;
    friend class CyPhotonFocusPage;

private:
    CyResult Construct();
};


#endif // __CY_PHOTONFOCUS_CAMERA_H__

