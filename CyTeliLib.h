/* CyTeliLib.h
/////////////////////////////////////////////////////////////////////////////
*/

#ifndef _CY_TELI_LIB_H_
#define _CY_TELI_LIB_H_

// Macros
/////////////////////////////////////////////////////////////////////////////

#ifdef CY_TELI_LIB_EXPORTS
#define CY_TELI_LIB_API __declspec(dllexport)
#else
#define CY_TELI_LIB_API __declspec(dllimport)
#endif

#endif // _CY_TELI_LIB_H_
