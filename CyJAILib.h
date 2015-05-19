/* CyJAILib.h
/////////////////////////////////////////////////////////////////////////////
*/

#ifndef _CY_JAI_LIB_H_
#define _CY_JAI_LIB_H_

// Macros
/////////////////////////////////////////////////////////////////////////////

#ifdef WIN32
#ifdef CY_JAI_LIB_EXPORTS
#define CY_JAI_LIB_API __declspec(dllexport)
#else
#define CY_JAI_LIB_API __declspec(dllimport)
#endif
#endif // WIN32

#ifdef _UNIX_
#define CY_JAI_LIB_API
#endif // _UNIX_

#endif // _CY_JAI_LIB_H_
