// *****************************************************************************
//
// $Id$
//
// cy1h03b1
//
// *****************************************************************************
//
//     Copyright (c) 2003, Pleora Technologies Inc., All rights reserved.
//
// *****************************************************************************
//
// File Name....: CyCameraInterface.h
//
// Description..: Defines the base of a camera class.
//
// *****************************************************************************
//
// $Log$
//
// *****************************************************************************

#ifndef __CY_CAMERA_INTERFACE_H__
#define __CY_CAMERA_INTERFACE_H__

// Headers
/////////////////////////////////////////////////////////////////////////////

// ===== CyUtilsLib =====
#include <CyTypes.h>
#include <CyPersistentRepository.h>
#include <CyString.h>
#include <CyXMLDocument.h>

// ===== CyImgLib =====
#include <CyPixelType.h>
#include <CyPixelConverter.h>

// ===== CyComLib =====
#include <CyChannel.h>

// ===== This Project =====
#include "CyCamLib.h"
#include "CyGrabber.h"
#include "CyImageBuffer.h"
#include "CyCameraLimits.h"
#include "CyCameraInterfaceConstants.h"


// Class CyCameraInterface
/////////////////////////////////////////////////////////////////////////////

#ifdef __cplusplus
class CyCameraInterface : public CyPersistentRepository
{
// Construction / Destruction
public:
    CY_CAM_LIB_API            CyCameraInterface( CyGrabber&            aGrabber,
                                                 const CyCameraLimits& aLimits );
    CY_CAM_LIB_API            CyCameraInterface( CyGrabber*            aGrabber,
                                                 const CyCameraLimits& aLimits );
    CY_CAM_LIB_API virtual    ~CyCameraInterface();
private:
    CyResult                  Construct();


// Access to the grabber and camera limits
public:
    CY_CAM_LIB_API virtual CyGrabber&            GetGrabber() const;
    CY_CAM_LIB_API virtual const CyCameraLimits& GetLimits() const;


// Update Camera
public:
    CY_CAM_LIB_API virtual CyResult UpdateToCamera( bool aDeviceReset = false ) const;
    CY_CAM_LIB_API virtual CyResult LocalUpdate   ( bool aDeviceReset ) const;


// Save/load settings from XML
public:
    CY_CAM_LIB_API virtual CyResult SaveToXML    ( CyXMLDocument& aDocument ) const;
    CY_CAM_LIB_API virtual CyResult LoadFromXML  ( CyXMLDocument& aDocument );


// Show Configuration Dialog
public:
    // Using void* to avoid windows.h dependency
    CY_CAM_LIB_API virtual CyResult ShowDialog       ( void* aParent = NULL );


// Properties
public:
    // Indicates if the camera supports the specific pixel type at the specified tap quantity
    CY_CAM_LIB_API virtual bool          SupportsPixelType( const CyPixelTypeID& aPixel,
                                                            unsigned char        aTapQuantity ) const;

    // Returns the pixel type after pixel shifting is applied
    CY_CAM_LIB_API virtual CyResult      GetEffectivePixelType( CyPixelTypeID& aPixel ) const;

    // Sets up an image buffer based on the camera settings
    CY_CAM_LIB_API virtual CyResult      SetupBuffer( CyImageBuffer& aBuffer ) const;

    // Returns the RGB Filter to use for this camera
    CY_CAM_LIB_API virtual CyRGBFilter&  GetRGBFilter() const;

    // Resets the camera.
    // NOTE: must be overriden for a specific camera.  The overriden function will then
    // have to send the right command to the camera.  If not, then this method returns
    // CY_RESULT_NOT_SUPPORTED.
    CY_CAM_LIB_API virtual CyResult ResetCamera     ( );

protected:
    CY_CAM_LIB_API virtual CyResult InternalUpdate  ( bool aDeviceReset ) const;
    CY_CAM_LIB_API virtual CyResult InternalSave    ( CyXMLDocument& aDocument ) const;
    CY_CAM_LIB_API virtual CyResult InternalLoad    ( CyXMLDocument& aDocument );
    CY_CAM_LIB_API virtual CyResult AddPropertyPage ( void* aPropertySheet );
    CY_CAM_LIB_API virtual CyResult OnParameterSet  ( unsigned long   aParameterIndex,
                                                      unsigned long   aParameterID,
                                                      const CyString& aParameterName,
                                                      bool            aTest,
                                                      const CyString& aValueS,
                                                      __int64         aValueI,
                                                      double          aValueD );
    CY_CAM_LIB_API virtual CyResult OnParameterGet  ( unsigned long   aParameterIndex,
                                                      unsigned long   aParameterID,
                                                      const CyString& aParameterName  );
    CY_CAM_LIB_API virtual CyResult OnParameterChanged( unsigned long   aParameterIndex,
                                                        unsigned long   aParameterID,
                                                        const CyString& aParameterName,
                                                        const CyString& aValueS,
                                                        __int64         aValueI,
                                                        double          aValueD );


//protected: // public for technical reasons, but really protected
public:
    CY_CAM_LIB_API virtual CyResult OnApply         ( void* aPropertyPage );

// Members
private:
    friend struct CyCameraInterfaceInternal;
    struct CyCameraInterfaceInternal* mInternal;

#ifndef CY_CAMERA_NO_BACKWARD_COMPATIBILITY
#include "CyCameraInterfaceBackwardCompatibility.h"
#endif // CY_CAMERA_NO_BACKWARD_COMPATIBILITY
};
#endif // __cplusplus


// Standard C Wrapper
/////////////////////////////////////////////////////////////////////////////

// CyCameraInterface Handle
typedef void* CyCameraInterfaceH;
typedef void* CyGrabberH;

// Destruction
// A camera object can only be obtained from a CyCameraRegistryH objects
CY_CAM_LIB_C_API void CyCameraInterface_Destroy( CyCameraInterfaceH aHandle );

// Access to the grabber
CY_CAM_LIB_C_API CyGrabberH CyCameraInterface_GetGrabber( CyCameraInterfaceH aHandle );

// Returns the limits of the camera
CY_CAM_LIB_C_API CyResult CyCameraInterface_GetLimits( CyCameraInterfaceH     aHandle,
                                                       struct CyCameraLimits* aLimits );

// Update settings on camera
CY_CAM_LIB_C_API CyResult CyCameraInterface_UpdateToCamera( CyCameraInterfaceH aHandle,
                                                            int                aDeviceReset );
CY_CAM_LIB_C_API CyResult CyCameraInterface_LocalUpdate   ( CyCameraInterfaceH aHandle,
                                                            int                aDeviceReset );

// Save/load settings from XML
CY_CAM_LIB_C_API CyResult CyCameraInterface_SaveToXML  ( CyCameraInterfaceH aHandle,
                                                         CyXMLDocumentH     aDocument );
CY_CAM_LIB_C_API CyResult CyCameraInterface_LoadFromXML( CyCameraInterfaceH aHandle,
                                                         CyXMLDocumentH     aDocument );

// Show Configuration Dialog
CY_CAM_LIB_C_API CyResult CyCameraInterface_ShowDialog ( CyCameraInterfaceH aHandle,
                                                         void*              aParent,
                                                         unsigned long      aFlags );

// Properties
CY_CAM_LIB_C_API int      CyCameraInterface_SupportsPixelType   ( CyCameraInterfaceH aHandle,
                                                                  CyPixelTypeID      aPixel,
                                                                  unsigned char      aTapQuantity);
CY_CAM_LIB_C_API CyResult CyCameraInterface_GetEffectivePixelType( CyCameraInterfaceH aHandle,
                                                                   CyPixelTypeID* aPixel );
CY_CAM_LIB_C_API CyResult CyCameraInterface_SetupBuffer       ( CyCameraInterfaceH aHandle,
                                                                CyImageBufferH     aBuffer );
CY_CAM_LIB_C_API CyRGBFilterH CyCameraInterface_GetRGBFilter  ( CyCameraInterfaceH aHandle );

CY_CAM_LIB_C_API CyResult CyCameraInterface_ResetCamera    ( CyCameraInterfaceH aHandle );

#endif  // __CY_CAMERA_INTERFACE_H__

