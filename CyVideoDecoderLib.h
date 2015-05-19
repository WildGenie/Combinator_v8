/* CyVideoDecoderLib.h
/////////////////////////////////////////////////////////////////////////////
*/

#ifndef _CY_VIDEO_DECODER_LIB_H_
#define _CY_VIDEO_DECODER_LIB_H_

// Macros
/////////////////////////////////////////////////////////////////////////////

#ifdef _UNIX_
#define CY_VIDEO_LIB_API
#endif // _UNIX_

#ifdef WIN32
#ifdef CY_VIDEO_DECODER_LIB_EXPORTS
#define CY_VIDEO_LIB_API __declspec(dllexport)
#else
#define CY_VIDEO_LIB_API __declspec(dllimport)
#endif
#endif // WIN32

#endif // _CY_VIDEO_DECODER_LIB_H_
