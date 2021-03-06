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
// File Name....: CyGrayscale4.h
//
// Description..: Raw Grayscale on 4 bits
//
// *****************************************************************************
//
// $Log$
//
// *****************************************************************************

#ifndef __CY_GRAYSCALE4_H__
#define __CY_GRAYSCALE4_H__

// Includes
/////////////////////////////////////////////////////////////////////////////

#include "CyImgLib.h"
#include "CyPixelType.h"


// Class
/////////////////////////////////////////////////////////////////////////////

CY_DECLARE_PIXEL_TYPE( CyGrayscale4,
                       0x00000400 | CY_PIXEL_FLAG_GRAYSCALE,
                       4,
                       1,
                       CY_IMG_LIB_API );

#endif //__CY_GRAYSCALE4_H__
