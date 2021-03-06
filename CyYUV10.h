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
// File Name....: CyYUV10.h
//
// Description..: YUV on 10 bits
//
// *****************************************************************************
//
// $Log$
//
// *****************************************************************************

#ifndef __CY_YUV10_H__
#define __CY_YUV10_H__

// Includes
/////////////////////////////////////////////////////////////////////////////

#include "CyImgLib.h"
#include "CyPixelType.h"


// Class
/////////////////////////////////////////////////////////////////////////////

CY_DECLARE_PIXEL_TYPE( CyYUV10,
                       0x00000002 | CY_PIXEL_FLAG_YUV_COLOUR,
                       20,
                       4,
                       CY_IMG_LIB_API );


#endif //__CY_YUV10_H__
