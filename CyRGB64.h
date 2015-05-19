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
// File Name....: CyRGB64.h
//
// Description..: RGB on 64 bits
//
// *****************************************************************************
//
// $Log$
//
// *****************************************************************************

#ifndef __CY_RGB64_H__
#define __CY_RGB64_H__

// Includes
/////////////////////////////////////////////////////////////////////////////

#include "CyImgLib.h"
#include "CyPixelType.h"


// Class
/////////////////////////////////////////////////////////////////////////////

CY_DECLARE_PIXEL_TYPE_RGB( CyRGB64,
                       0x00000005 | CY_PIXEL_FLAG_RGB_COLOUR,
                       64,
                       8,
                       CY_IMG_LIB_API,
                       false );

CY_DECLARE_PIXEL_TYPE_RGB( CyRGB64_10Bits,
                       0x00000009 | CY_PIXEL_FLAG_RGB_COLOUR,
                       10,
                       8,
                       CY_IMG_LIB_API,
                       false );

CY_DECLARE_PIXEL_TYPE_RGB( CyRGB64_12Bits,
                       0x0000000D | CY_PIXEL_FLAG_RGB_COLOUR,
                       12,
                       8,
                       CY_IMG_LIB_API,
                       false );



#endif //__CY_RGB64_H__
