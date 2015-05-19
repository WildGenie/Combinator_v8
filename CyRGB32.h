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
// File Name....: CyRGB32.h
//
// Description..: RGB on 32 bits
//
// *****************************************************************************
//
// $Log$
//
// *****************************************************************************

#ifndef __CY_RGB32_H__
#define __CY_RGB32_H__

// Includes
/////////////////////////////////////////////////////////////////////////////

#include "CyImgLib.h"
#include "CyPixelType.h"


// Class
/////////////////////////////////////////////////////////////////////////////

CY_DECLARE_PIXEL_TYPE_RGB( CyRGB32,
                       0x00000003 | CY_PIXEL_FLAG_RGB_COLOUR,
                       32,
                       4,
                       CY_IMG_LIB_API,
                       false );

CY_DECLARE_PIXEL_TYPE_RGB( CyBGR32,
                       0x00000007 | CY_PIXEL_FLAG_RGB_COLOUR,
                       32,
                       4,
                       CY_IMG_LIB_API,
                       false );


CY_DECLARE_PIXEL_TYPE_RGB( CyRGB8_4,
                       0x0000000B | CY_PIXEL_FLAG_RGB_COLOUR,
                       8,
                       4,
                       CY_IMG_LIB_API,
                       false );

#endif //__CY_RGB32_H__

