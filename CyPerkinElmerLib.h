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
// File Name....: CyPERKINELMERLib.h
//
// Description..: Defines the DLL exporting
//
// *****************************************************************************
//
// $Log$
//
// *****************************************************************************

#ifndef _CY_PERKINELMER_LIB_H_
#define _CY_PERKINELMER_LIB_H_

// Macros
/////////////////////////////////////////////////////////////////////////////

#ifdef CY_PERKINELMER_LIB_EXPORTS
#define CY_PERKINELMER_LIB_API __declspec(dllexport)
#else
#define CY_PERKINELMER_LIB_API __declspec(dllimport)
#endif

#endif // _CY_PERKINELMER_LIB_H_
