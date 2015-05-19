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
// File Name....: CyAdimecLib.h
//
// Description..: Defines the DLL exporting
//
// *****************************************************************************
//
// $Log$
//
// *****************************************************************************

#ifndef _CY_ADIMEC_LIB_H_
#define _CY_ADIMEC_LIB_H_

// Macros
/////////////////////////////////////////////////////////////////////////////

#ifdef WIN32
#ifdef CY_ADIMEC_LIB_EXPORTS
#define CY_ADIMEC_LIB_API __declspec(dllexport)
#else
#define CY_ADIMEC_LIB_API __declspec(dllimport)
#endif
#endif // WIN32

#ifdef _UNIX_
#define CY_ADIMEC_LIB_API
#endif // _UNIX_

#endif // _CY_ADIMEC_LIB_H_
