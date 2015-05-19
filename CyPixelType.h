// *****************************************************************************
//
// $Id$
//
// 
//
// *****************************************************************************
//
//     Copyright (c) 2003, Pleora Technologies Inc., All rights reserved.
//
// *****************************************************************************
//
// File Name....: CyPixelType.h
//
// Description..: Pixel type base class
//
// *****************************************************************************
//
// $Log$
//
// *****************************************************************************

#ifndef __CY_PIXEL_TYPE_H__
#define __CY_PIXEL_TYPE_H__

// Includes
/////////////////////////////////////////////////////////////////////////////

#ifdef _UNIX_
//#include <stdlib.h>
typedef unsigned int size_t;
#endif // _UNIX_

#include "CyImgLib.h"
#include <CyTypes.h>
#include <CyObject.h>
#include <CyAssert.h>


// Forward declaration
/////////////////////////////////////////////////////////////////////////////

#ifdef __cplusplus
class CyPixelConverter;
#endif // __cplusplus

// Flags
/////////////////////////////////////////////////////////////////////////////

//
// Flag format (64-bits)
//
// Bits  0-15: Actual pixel identifier (+ the color space)
// Bits 16-19: Color space flag (there must be one and only one)
// Bits 20-23: Pixel packing and organization
// Bits 24-28: Pixel Output format
// Bits 32-63: Reserved
//

#define CY_PIXEL_FLAG_IDENTIFIER        0x000000000000FFFF

//
// Colour spaces
//

#define CY_PIXEL_FLAG_GRAYSCALE         0x0000000000010000
#define CY_PIXEL_FLAG_RGB_COLOUR        0x0000000000020000
#define CY_PIXEL_FLAG_YUV_COLOUR        0x0000000000040000

#define CY_PIXEL_FLAG_COLOUR_SPACE_MASK 0x0000000000070000

//
// Pixel packing and organization
//

#define CY_PIXEL_FLAG_NORMALIZED        0x0000000000100000
#define CY_PIXEL_FLAG_INTERLACED        0x0000000000200000
#define CY_PIXEL_FLAG_PACKED            0x0000000000400000
#define CY_PIXEL_FLAG_PLANAR            0x0000000000800000

//
// Pixel output format
//
// Normal   : 121212121>
// L-R      : 1111>2222>
// L-Rinv   : 1111><2222
// Linv-r   : <11112222>
// Linv-Rinv: <1111<2222
// Dual Lines: 
//          Line 1: 11111111>
//          Line 2: 22222222>
//          Buffer: 1212121212121212>
//
// The IP Engine assumes the data from the IP Engine
// is odd and even (as in normal), so for the other formats,
// the output of tap 1 is the left part and for tap 2, the right part.
//

#define CY_PIXEL_FLAG_DUAL_L_R          0x0000000001000000
#define CY_PIXEL_FLAG_DUAL_L_RINV       0x0000000002000000
#define CY_PIXEL_FLAG_DUAL_LINV_R       0x0000000004000000
#define CY_PIXEL_FLAG_DUAL_LINV_RINV    0x0000000008000000
#define CY_PIXEL_FLAG_DUAL_LINES        0x0000000010000000

#define CY_PIXEL_FLAG_OUTPUT_MASK       0x000000001F000000


// Class
/////////////////////////////////////////////////////////////////////////////

typedef __int64 CyPixelTypeID;

#ifdef __cplusplus
class CyPixelType : public CyObject
{
    // types
    public:
        // Flags for specifying type ID
        enum CyPixelTypeFlags
        {
            GRAYSCALE       = CY_PIXEL_FLAG_GRAYSCALE     ,
            RGB_COLOUR      = CY_PIXEL_FLAG_RGB_COLOUR    ,
            YUV_COLOUR      = CY_PIXEL_FLAG_YUV_COLOUR    ,

            NORMALIZED      = CY_PIXEL_FLAG_NORMALIZED    ,
            INTERLACED      = CY_PIXEL_FLAG_INTERLACED    ,
            PACKED          = CY_PIXEL_FLAG_PACKED        ,
            PLANAR          = CY_PIXEL_FLAG_PLANAR        ,

            DUAL_L_R        = CY_PIXEL_FLAG_DUAL_L_R      ,
            DUAL_L_RINV     = CY_PIXEL_FLAG_DUAL_L_RINV   ,
            DUAL_LINV_R     = CY_PIXEL_FLAG_DUAL_LINV_R   ,
            DUAL_LINV_RINV  = CY_PIXEL_FLAG_DUAL_LINV_RINV,
            DUAL_LINES      = CY_PIXEL_FLAG_DUAL_LINES    ,
        } Flags;
		

    // Construction / Destruction
    public:
        CY_IMG_LIB_API        CyPixelType ( const CyPixelTypeID& aID,
                                            unsigned short       aBitSize,
                                            unsigned short       aByteSize,
                                            bool                 aBayerPattern = false );
        CY_IMG_LIB_API virtual ~CyPixelType();

        // Copy of a pixel type
        CY_IMG_LIB_API virtual CyPixelType*
                               Clone() const;


    // Accessors
    public:
        // returns the ID of the current pixel type
        CY_IMG_LIB_API virtual const CyPixelTypeID&
                        GetTypeID() const;

        // returns the size of a single pixel in bits and bytes
        CY_IMG_LIB_API virtual unsigned short  
                        GetPixelBitSize () const;
        CY_IMG_LIB_API virtual unsigned short
                        GetPixelByteSize() const;

        // For RGB_COLOUR only, indicates if the format is a bayer pattern
        CY_IMG_LIB_API virtual bool IsBayerPattern() const;

        // Returns the size of a buffer for a particular size
        CY_IMG_LIB_API virtual unsigned long
                        GetBufferSizeFor( unsigned long aSizeX,
                                          unsigned long aSizeY ) const;


    // Converter methods
    public:
        CY_IMG_LIB_API bool HasConverterTo( const CyPixelType& aType ) const;
        CY_IMG_LIB_API bool HasConverterFrom( const CyPixelType& aType ) const;

        CY_IMG_LIB_API const CyPixelConverter&
                        GetConverterTo( const CyPixelType& aType ) const;
        CY_IMG_LIB_API const CyPixelConverter&
                        GetConverterFrom( const CyPixelType& aType ) const;


    protected:
        // Members
        const CyPixelTypeID  mID;
        const unsigned short mBitSize;
        const unsigned short mByteSize;
        const bool           mBayerPattern;

    // disabled methods
    private:
        CyPixelType ( const CyPixelType& aObj );
        CyPixelType& operator=(const CyPixelType&);
};


/* ==========================================================================
@mfunc  const CyPixelConverter& | CyPixelType | GetConverterFrom

@parm const CyPixelType& | aType | [in]

@rdesc  returns a pixel type converter from the sopecified type to this.

@since  2003-01-08
========================================================================== */
inline const CyPixelConverter&
CyPixelType::GetConverterFrom( const CyPixelType& aType ) const
{
    return aType.GetConverterTo( *this );
}


/* ==========================================================================
@mfunc  bool | CyPixelType | HasConverterFrom

@parm const CyPixelType& | aType | [in]

@rdesc  Indicates if a pixel type converter from the sopecified type to this exists

@since  2003-01-08
========================================================================== */
inline bool CyPixelType::HasConverterFrom( const CyPixelType& aType ) const
{
    return aType.HasConverterTo( *this );
}


// Macros
/////////////////////////////////////////////////////////////////////////////

#define CY_DECLARE_PIXEL_TYPE( aClassName, aPixelTypeID, aByteSize, aBitSize, aExportSymbol ) \
    class aClassName : public CyPixelType \
    { \
        public: \
            enum { ID = aPixelTypeID }; \
     \
            aExportSymbol   aClassName() \
                : CyPixelType( aPixelTypeID, aByteSize, aBitSize ) \
            { \
            } \
            aExportSymbol   aClassName( const CyPixelTypeID& aID ) \
                : CyPixelType( aID, aByteSize, aBitSize ) \
            { \
            } \
    };

#define CY_DECLARE_PIXEL_TYPE_RGB( aClassName, aPixelTypeID, aByteSize, aBitSize, aExportSymbol, aBayerPattern ) \
    class aClassName : public CyPixelType \
    { \
        public: \
            enum { ID = aPixelTypeID }; \
     \
            aExportSymbol   aClassName() \
                : CyPixelType( aPixelTypeID, aByteSize, aBitSize, aBayerPattern ) \
            { \
            } \
            aExportSymbol   aClassName( const CyPixelTypeID& aID ) \
                : CyPixelType( aID, aByteSize, aBitSize, aBayerPattern ) \
            { \
            } \
    };


#define CY_REGISTER_PIXEL_TYPE( aClassName, aPixelTypeID ) \
{ \
	CyAssert( !CyPixelTypeFactory::HasPixelType( aPixelTypeID ) ); \
	aClassName lTmp( aPixelTypeID ); \
    CyPixelTypeFactory::RegisterPixelType( aClassName::ID | aPixelTypeID, \
                                           &lTmp ); \
} 

#define CY_REGISTER_PIXEL_TYPE_NAME( aClassName, aPixelTypeID, aName ) \
{ \
	CyAssert( !CyPixelTypeFactory::HasPixelType( aPixelTypeID ) ); \
	aClassName lTmp( aPixelTypeID ); \
	CyPixelTypeFactory::RegisterPixelType( aClassName::ID | aPixelTypeID, \
                                           &lTmp, \
                                           aName ); \
}

#endif // __cplusplus

#ifndef __cplusplus
#define CY_DECLARE_PIXEL_TYPE( aClassName, aPixelTypeID, aByteSize, aBitSize, aExportSymbol ) \
    enum { aClassName##_ID = aPixelTypeID };

#define CY_DECLARE_PIXEL_TYPE_RGB( aClassName, aPixelTypeID, aByteSize, aBitSize, aExportSymbol, aBayerPattern ) \
    enum { aClassName##_ID = aPixelTypeID };

#endif


// Standard C Wrapper
/////////////////////////////////////////////////////////////////////////////

// CyPixelType & CyPixelConverter Handles
typedef void* CyPixelTypeH;
typedef void* CyPixelConverterH;

// A pixel type handle can only be obtained through the CyPixelTypeFactory
// So only a destructor is available for the CyPixelTypeH
CY_IMG_LIB_C_API void CyPixelType_Destroy( CyPixelTypeH aHandle );

// Clone - Creates a copy of a pixel type.  The caller is responsible for its deletion
CY_IMG_LIB_C_API CyPixelTypeH CyPixelType_Clone( CyPixelTypeH aHandle );

// CyPixelType functions
CY_IMG_LIB_C_API CyPixelTypeID  CyPixelType_GetTypeID( CyPixelTypeH aHandle );
CY_IMG_LIB_C_API unsigned short CyPixelType_GetPixelBitSize ( CyPixelTypeH  aHandle );
CY_IMG_LIB_C_API unsigned short CyPixelType_GetPixelByteSize( CyPixelTypeH  aHandle );
CY_IMG_LIB_C_API int            CyPixelType_IsBayerPattern( CyPixelTypeH  aHandle );
CY_IMG_LIB_C_API unsigned long  CyPixelType_GetBufferSizeFor( CyPixelTypeH  aHandle,
                                                              unsigned long aSizeX,
                                                              unsigned long aSizeY );

CY_IMG_LIB_C_API int CyPixelType_HasConverterTo  ( CyPixelTypeH aHandle,
                                                   CyPixelTypeH aType );
CY_IMG_LIB_C_API int CyPixelType_HasConverterFrom( CyPixelTypeH aHandle,
                                                   CyPixelTypeH aType );

CY_IMG_LIB_C_API CyPixelConverterH
                     CyPixelType_GetConverterTo  ( CyPixelTypeH aHandle,
                                                   CyPixelTypeH aType );
CY_IMG_LIB_C_API CyPixelConverterH
                     CyPixelType_GetConverterFrom( CyPixelTypeH aHandle,
                                                   CyPixelTypeH aType );

#endif // __CY_PIXEL_TYPE_H__
