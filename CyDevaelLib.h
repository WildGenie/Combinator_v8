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
// File Name....: CyDevaelLib.h
//
// Description..: Defines the DLL exporting
//
// *****************************************************************************
//
// $Log$
//
// *****************************************************************************

#ifndef _CY_DEVAEL_LIB_H_
#define _CY_DEVAEL_LIB_H_

// Macros
/////////////////////////////////////////////////////////////////////////////

#ifdef WIN32
#ifdef CY_DEVAEL_LIB_EXPORTS
#define CY_DEVAEL_LIB_API __declspec(dllexport)
#else
#define CY_DEVAEL_LIB_API __declspec(dllimport)
#endif
#endif // WIN32

#ifdef _LINUX_
#define CY_DEVAEL_LIB_API
#endif // _LINUX_

#endif // _CY_DEVAEL_LIB_H_
