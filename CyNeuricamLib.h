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
// File Name....: CyNeuricamLib.h
//
// Description..: Defines the DLL exporting
//
// *****************************************************************************
//
// $Log$
//
// *****************************************************************************

#ifndef _CY_NEURICAM_LIB_H_
#define _CY_NEURICAM_LIB_H_

// Macros
/////////////////////////////////////////////////////////////////////////////

#ifdef CY_NEURICAM_LIB_EXPORTS
#define CY_NEURICAM_LIB_API __declspec(dllexport)
#else
#define CY_NEURICAM_LIB_API __declspec(dllimport)
#endif

#endif // _CY_NEURICAM_LIB_H_
