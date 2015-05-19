/* CyPULNIXLib.h
/////////////////////////////////////////////////////////////////////////////
*/

#ifndef _CY_PULNIX_LIB_H_
#define _CY_PULNIX_LIB_H_

// Macros
/////////////////////////////////////////////////////////////////////////////

#ifdef CY_PULNIX_LIB_EXPORTS
#define CY_PULNIX_LIB_API __declspec(dllexport)
#else
#define CY_PULNIX_LIB_API __declspec(dllimport)
#endif

#endif // _CY_PULNIX_LIB_H_
