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
// File Name....: CyTakenakaLib.h
//
// Description..: Defines the DLL exporting
//
// *****************************************************************************
//
// $Log$
//
// *****************************************************************************

#ifndef _CY_TAKENAKA_LIB_H_
#define _CY_TAKENAKA_LIB_H_

// Macros
/////////////////////////////////////////////////////////////////////////////

#ifdef CY_TAKENAKA_LIB_EXPORTS
#define CY_TAKENAKA_LIB_API __declspec(dllexport)
#else
#define CY_TAKENAKA_LIB_API __declspec(dllimport)
#endif

#endif // _CY_TAKENAKA_LIB_H_
