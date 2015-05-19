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
// File Name....: CyRGB48.h
//
// Description..: RGB on 48 bits
//
// *****************************************************************************
//
// $Log$
//
// *****************************************************************************

#ifndef __CY_RGB48_H__
#define __CY_RGB48_H__

// Includes
/////////////////////////////////////////////////////////////////////////////

#include "CyImgLib.h"
#include "CyPixelType.h"


// Class
/////////////////////////////////////////////////////////////////////////////

CY_DECLARE_PIXEL_TYPE_RGB( CyRGB48,
                       0x00000004 | CY_PIXEL_FLAG_RGB_COLOUR,
                       48,
                       6,
                       CY_IMG_LIB_API,
                       false );

CY_DECLARE_PIXEL_TYPE_RGB( CyRGB48_10Bits,
                       0x00000008 | CY_PIXEL_FLAG_RGB_COLOUR,
                       10,
                       6,
                       CY_IMG_LIB_API,
                       false );

CY_DECLARE_PIXEL_TYPE_RGB( CyRGB48_12Bits,
                       0x0000000C | CY_PIXEL_FLAG_RGB_COLOUR,
                       12,
                       6,
                       CY_IMG_LIB_API,
                       false );



#endif //__CY_RGB48_H__
