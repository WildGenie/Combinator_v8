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
// File Name....: CyImperXLib.h
//
// Description..: Defines the DLL exporting
//
// Implementation Notes: Replace IMPERX with the real name
//
// *****************************************************************************
//
// $Log$
//
// *****************************************************************************

#ifndef _CY_IMPERX_LIB_H_
#define _CY_IMPERX_LIB_H_

// Macros
//
// NOTE: You will need to change CY_IMPERX_LIB_EXPORTS to a name that corresponds
// to your camera.  You will need to change this define in the project settings as
// well.
//
// Note: The same applies to CY_IMPERX_LIB_API in here and in the camera 
// class header file.
/////////////////////////////////////////////////////////////////////////////

#ifdef CY_IMPERX_LIB_EXPORTS
#define CY_IMPERX_LIB_API __declspec(dllexport)
#else
#define CY_IMPERX_LIB_API __declspec(dllimport)
#endif

#endif // _CY_IMPERX_LIB_H_
