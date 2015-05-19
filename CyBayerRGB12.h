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
// File Name....: CyBayerRGB12.h
//
// Description..: Bayer RGB on 8 bits
//
// *****************************************************************************
//
// $Log$
//
// *****************************************************************************

#ifndef __CY_BAYER_RGB12_H__
#define __CY_BAYER_RGB12_H__

// Includes
/////////////////////////////////////////////////////////////////////////////

#include "CyImgLib.h"
#include "CyPixelType.h"


// Class
/////////////////////////////////////////////////////////////////////////////

CY_DECLARE_PIXEL_TYPE_RGB( CyBayerRGB12,
                       0x00000012 | CY_PIXEL_FLAG_RGB_COLOUR,
                       12,
                       2,
                       CY_IMG_LIB_API,
                       true );

// For backward compatibility
CY_DECLARE_PIXEL_TYPE_RGB( CyBayerRGGB12,
                       0x00000015 | CY_PIXEL_FLAG_RGB_COLOUR,
                       12,
                       2,
                       CY_IMG_LIB_API,
                       true );

#endif //__CY_BAYER_RGB12_H__
