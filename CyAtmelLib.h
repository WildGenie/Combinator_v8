/* CyAtmelLib.h
/////////////////////////////////////////////////////////////////////////////
*/

#ifndef _CY_ATMEL_LIB_H_
#define _CY_ATMEL_LIB_H_

// Macros
/////////////////////////////////////////////////////////////////////////////

#ifdef WIN32
#ifdef CY_ATMEL_LIB_EXPORTS
#define CY_ATMEL_LIB_API __declspec(dllexport)
#else // CY_ATMEL_LIB_EXPORTS
#define CY_ATMEL_LIB_API __declspec(dllimport)
#endif // CY_ATMEL_LIB_EXPORTS
#endif // WIN32

#ifdef _LINUX_
#define CY_ATMEL_LIB_API
#endif // _LINUX_

#endif // _CY_ATMEL_LIB_H_
