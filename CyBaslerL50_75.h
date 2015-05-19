// *****************************************************************************
//
// $Id$
//
// cy1c01b1
//
// *****************************************************************************
//
//     Copyright (c) 2003, Pleora Technologies Inc., All rights reserved.
//
// *****************************************************************************
//
// File Name....: CyBaslerL50_75.h
//
// Description..: Basler L50/75 series ( L50 and L75 )
//
// *****************************************************************************
//
// $Log$
//
// *****************************************************************************

#ifndef __CY_BASLER_L50_75_H__
#define __CY_BASLER_L50_75_H__

// Headers
/////////////////////////////////////////////////////////////////////////////

// ===== This Project =====
#include "CyBaslerLib.h"
#include "CyCameraLVDS.h"


// Forward-Declaration
/////////////////////////////////////////////////////////////////////////////


// Class
/////////////////////////////////////////////////////////////////////////////

class CyBaslerL50_75 : public CyCameraLVDS
{
// Construction / Destruction
public:
    CY_BASLER_LIB_API            CyBaslerL50_75( CyGrabber*            aGrabber,
                                                const CyCameraLimits& aLimits,
                                                const CyString&    aName );
    CY_BASLER_LIB_API virtual    ~CyBaslerL50_75();


// Implementation members
private:
    const CyString mName;
};


#endif // __CY_BASLER_L50_75_H__
