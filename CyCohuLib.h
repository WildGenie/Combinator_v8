/* CyCohuLib.h
/////////////////////////////////////////////////////////////////////////////
*/

#ifndef _CY_COHU_LIB_H_
#define _CY_COHU_LIB_H_

// Macros
/////////////////////////////////////////////////////////////////////////////

#ifdef WIN32
#ifdef CY_COHU_LIB_EXPORTS
#define CY_COHU_LIB_API __declspec(dllexport)
#else
#define CY_COHU_LIB_API __declspec(dllimport)
#endif
#endif // WIN32

#ifdef _LINUX_
#define CY_COHU_LIB_API
#endif // _LINUX_

#endif // _CY_COHU_LIB_H_
