// *****************************************************************************
//
// $Id$
//
//
// *****************************************************************************
//
//     Copyright (c) 2003, Pleora Technologies Inc., All rights reserved.
//
// *****************************************************************************
//
// File Name....: CyVarianPaxScan.h
//
// Description..: Defines the basic of a camera implementation based on CameraLink
//
// *****************************************************************************
//
// $Log$
//
// *****************************************************************************

#ifndef __CY_VARIAN_PAXSCAN_H__
#define __CY_VARIAN_PAXSCAN_H__

// Headers
/////////////////////////////////////////////////////////////////////////////

// ===== This Project =====
#include "CyVarianLib.h"


// Class
//
// Note:  The PaxScanis available as LVDS or Camera Link models.  This class
// is a template class that can derive from either CyCameraLink or CyCameraLVDS.
//
// Both versions are registered in the camera registry.  To use directly, simply
// use CyVarianPaxScan<CyCameraLink> or CyVarianPaxScan<CyCameraLVDS>.
//
/////////////////////////////////////////////////////////////////////////////

template<class Ancestor>
class CyVarianPaxScan: public Ancestor
{
//
// Construction / Destruction
//
public:
    CY_VARIAN_LIB_API            CyVarianPaxScan( CyGrabber* aGrabber );
    CY_VARIAN_LIB_API virtual    ~CyVarianPaxScan();
};


#endif // __CY_VARIAN_PAXSCAN_H__
