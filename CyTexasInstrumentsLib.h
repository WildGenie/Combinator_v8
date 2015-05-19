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
// File Name....: CyTexasInstrumentsLib.h
//
// Description..: Defines the DLL exporting
//
// *****************************************************************************
//
// $Log$
//
// *****************************************************************************

#ifndef _CY_TEXAS_INSTRUMENTS_LIB_H_
#define _CY_TEXAS_INSTRUMENTS_LIB_H_

// Macros
//
// NOTE: You will need to change CY_TEXAS_INSTRUMENTS_LIB_EXPORTS to a name that corresponds
// to your camera.  You will need to change this define in the project settings as
// well.
//
// Note: The same applies to CY_TEXAS_INSTRUMENTS_LIB_API in here and in the camera 
// class header file.
/////////////////////////////////////////////////////////////////////////////

#ifdef CY_TEXAS_INSTRUMENTS_LIB_EXPORTS
#define CY_TEXAS_INSTRUMENTS_LIB_API __declspec(dllexport)
#else
#define CY_TEXAS_INSTRUMENTS_LIB_API __declspec(dllimport)
#endif

#endif // _CY_TEXAS_INSTRUMENTS_LIB_H_
