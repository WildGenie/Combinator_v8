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
// File Name....: CyCISCorporationLib.h
//
// Description..: Defines the DLL exporting
//
// *****************************************************************************
//
// $Log$
//
// *****************************************************************************

#ifndef _CY_CIS_CORPORATION_LIB_H_
#define _CY_CIS_CORPORATION_LIB_H_

// Macros
//
// NOTE: You will need to change CY_CIS_CORPORATION_LIB_EXPORTS to a name that corresponds
// to your camera.  You will need to change this define in the project settings as
// well.
//
// Note: The same applies to CY_CIS_CORPORATION_LIB_API in here and in the camera 
// class header file.
/////////////////////////////////////////////////////////////////////////////

#ifdef WIN32
#ifdef CY_CIS_CORPORATION_LIB_EXPORTS
#define CY_CIS_CORPORATION_LIB_API __declspec(dllexport)
#else
#define CY_CIS_CORPORATION_LIB_API __declspec(dllimport)
#endif
#endif // WIN32

#ifdef _LINUX_
#define CY_CIS_CORPORATION_LIB_API
#endif // _LINUX_

#endif // _CY_CIS_CORPORATION_LIB_H_
