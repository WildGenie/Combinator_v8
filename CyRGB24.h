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
// File Name....: CyRGB24.h
//
// Description..: RGB on 24 bits
//
// *****************************************************************************
//
// $Log$
//
// *****************************************************************************

#ifndef __CY_RGB24_H__
#define __CY_RGB24_H__

// Includes
/////////////////////////////////////////////////////////////////////////////

#include "CyImgLib.h"
#include "CyPixelType.h"


// Class
/////////////////////////////////////////////////////////////////////////////

CY_DECLARE_PIXEL_TYPE_RGB( CyRGB24,
                       0x00000002 | CY_PIXEL_FLAG_RGB_COLOUR,
                       24,
                       3,
                       CY_IMG_LIB_API,
                       false );

CY_DECLARE_PIXEL_TYPE_RGB( CyBGR24,
                       0x00000006 | CY_PIXEL_FLAG_RGB_COLOUR,
                       24,
                       3,
                       CY_IMG_LIB_API,
                       false );

CY_DECLARE_PIXEL_TYPE_RGB( CyRGB8_3,
                       0x0000000A | CY_PIXEL_FLAG_RGB_COLOUR,
                       8,
                       3,
                       CY_IMG_LIB_API,
                       false );

#endif //__CY_RGB24_H__
