// *****************************************************************************
//
// $Id$
//
//
// *****************************************************************************
//
//     Copyright (c) 2004, Pleora Technologies Inc., All rights reserved.
//
// *****************************************************************************
//
// File Name....: CyRedLakeLib.h
//
// Description..: Defines the DLL exporting
//
// *****************************************************************************
//
// $Log$
//
// *****************************************************************************

#ifndef _CY_REDLAKE_LIB_H_
#define _CY_REDLAKE_LIB_H_

// Macros
/////////////////////////////////////////////////////////////////////////////

#ifdef CY_REDLAKE_LIB_EXPORTS
#define CY_REDLAKE_LIB_API __declspec(dllexport)
#else
#define CY_REDLAKE_LIB_API __declspec(dllimport)
#endif

#endif // _CY_REDLAKE_LIB_H_
