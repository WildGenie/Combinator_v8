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
// File Name....: CyYUV8.h
//
// Description..: YUV on 8 bits
//
// *****************************************************************************
//
// $Log$
//
// *****************************************************************************

#ifndef __CY_YUV8_H__
#define __CY_YUV8_H__

// Includes
/////////////////////////////////////////////////////////////////////////////

#include "CyImgLib.h"
#include "CyPixelType.h"


// Class
/////////////////////////////////////////////////////////////////////////////

CY_DECLARE_PIXEL_TYPE( CyYUV8,
                       0x00000001 | CY_PIXEL_FLAG_YUV_COLOUR,
                       16,
                       2,
                       CY_IMG_LIB_API );


CY_DECLARE_PIXEL_TYPE( CyYUV8_444,
                       0x00000003 | CY_PIXEL_FLAG_YUV_COLOUR,
                       24,
                       3,
                       CY_IMG_LIB_API );

CY_DECLARE_PIXEL_TYPE( CyYCrCb,
                       0x00000005 | CY_PIXEL_FLAG_YUV_COLOUR,
                       24,
                       3,
                       CY_IMG_LIB_API );


#ifdef __cplusplus
typedef CyYUV8 CyYUV8_422;
typedef CyYUV8_444 CyYCbCr;
#endif // __cplusplus

#endif //__CY_YUV8_H__

