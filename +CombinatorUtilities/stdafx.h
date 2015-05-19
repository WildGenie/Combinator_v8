// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers

// Windows Header Files:
#include <windows.h>
#include <commctrl.h>
#include <commdlg.h>
#include <shlobj.h>
#include <shellapi.h>

// C RunTime Header Files
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>
#include <stdio.h>

#include "tc/tc.h"
#include "tc.ui/tc.ui.h"
#include "tc.cam/tc.cam.h"

#pragma warning(disable:4996)
#pragma warning(disable:4355)

#ifndef bool2BOOL
#	define bool2BOOL(b) ((b) ? TRUE : FALSE)
#	define BOOL2bool(b) ((b) ? true : false)
#endif
