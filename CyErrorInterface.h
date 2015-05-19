// *****************************************************************************
//
// $Id$
//
// 
//
// *****************************************************************************
//
//     Copyright (c) 2003, Pleora Technologies Inc., All rights reserved.
//
// *****************************************************************************
//
// File Name....: CyErrorInterface.h
//
// Description..: Provides a mechanism for GetErrorInfo
//
// *****************************************************************************
//
// $Log$
//
// *****************************************************************************

#ifndef _CY_ERROR_INFO_H_
#define _CY_ERROR_INFO_H_

#ifdef _UNIX_
#include <stdlib.h>
#endif // _UNIX_

#include "CyUtilsLib.h"
#include "CyTypes.h"
#include "CyObject.h"

#ifdef __cplusplus
struct CyErrorInterfaceInternal;
class CY_UTILS_LIB_API CyErrorInterface : public CyObject
{
public:
    // Construction / Destruction
             CyErrorInterface();
    virtual ~CyErrorInterface();

// Setting the last error
    virtual CyResult    SetErrorInfo( const char *  aMessage,
                                      CyResult      aResult,
                                      const char *  aSourceFile,
                                      unsigned long aSourceLine,
                                      unsigned long aSystemCode ) const;
    virtual CyResult    SetErrorInfo( const CyErrorInterface& aError ) const;
    virtual CyResult    SetErrorInfo( const CyErrorInfo& aInfo ) const;

// Getting the error Info
    virtual CyResult    GetErrorInfo( CyErrorInfo * aInfo = 0 ) const;

// Clearing the error
    virtual CyResult    ClearErrorInfo() const;

// Members
private:
    struct CyErrorInterfaceInternal* mInternal;
};
#endif


// Standard C Wrapper
/////////////////////////////////////////////////////////////////////////////

// CyErrorInterface Handle
typedef void* CyErrorInterfaceH;

// Construction Destruction
CY_UTILS_LIB_C_API CyErrorInterfaceH CyErrorInterface_Init();
CY_UTILS_LIB_C_API void              CyErrorInterface_Destroy( CyErrorInterfaceH aHandle );

// SetErrorInfo methods
CY_UTILS_LIB_C_API CyResult CyErrorInterface_SetErrorInfo ( CyErrorInterfaceH aHandle,
                                                            const char *      aMessage,
                                                            CyResult          aResult,
                                                            const char *      aSourceFile,
                                                            unsigned long     aSourceLine,
                                                            unsigned long     aSystemCode );
CY_UTILS_LIB_C_API CyResult CyErrorInterface_SetErrorInfo2( CyErrorInterfaceH aHandle,
                                                            CyErrorInterfaceH aSource );
CY_UTILS_LIB_C_API CyResult CyErrorInterface_SetErrorInfo3( CyErrorInterfaceH  aHandle,
                                                            struct CyErrorInfo aInfo );

// GetErrorInfo Method
CY_UTILS_LIB_C_API CyResult CyErrorInterface_GetErrorInfo ( CyErrorInterfaceH   aHandle,
                                                            struct CyErrorInfo* aInfo );

// ClearErrorInfo method
CY_UTILS_LIB_C_API CyResult CyErrorInterface_ClearErrorInfo( CyErrorInterfaceH aHandle );

#endif // _CY_ERROR_INFO_H_
