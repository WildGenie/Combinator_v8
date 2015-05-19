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
// File Name....: CyRGBFilter.h
//
// Description..: Filter for RGB data
//
// *****************************************************************************
//
// $Log$
//
// *****************************************************************************

#ifndef __CY_RGB_FILTER_H__
#define __CY_RGB_FILTER_H__

// Includes
/////////////////////////////////////////////////////////////////////////////

// ===== CyUtilsLib =====
#include <CyTypes.h>
#include <CyObject.h>
#include <CyAssert.h>

// ===== This Project =====
#include "CyImgLib.h"


// Class
/////////////////////////////////////////////////////////////////////////////

#ifdef __cplusplus
class CY_IMG_LIB_API CyRGBFilter : public CyObject
{
    // construction / destruction
    public:
                CyRGBFilter( unsigned long aBitSize );
        virtual ~CyRGBFilter();

        // returns the size in bits of each channel
        virtual unsigned long GetBitSize() const;

        // returns the number of entries in each channel table
        virtual unsigned long GetEntryCount() const;

        // Returns the entry for a channel entry
        unsigned char  GetRedValue8 ( unsigned long aIndex ) const;
        unsigned char  GetGreenValue8 ( unsigned long aIndex ) const;
        unsigned char  GetBlueValue8 ( unsigned long aIndex ) const;
        unsigned short GetRedValue16( unsigned long aIndex ) const;
        unsigned short GetGreenValue16( unsigned long aIndex ) const;
        unsigned short GetBlueValue16( unsigned long aIndex ) const;

        // Changes the internal look-up tables based on a multiplier
        // for each channel (R, G or B )
        virtual CyResult SetMultipliers( double         aRedGain,
                                         double         aGreenGain,
                                         double         aBlueGain );
        virtual CyResult SetMultipliers( double         aRedGain,
                                         double         aGreenGain,
                                         double         aBlueGain,
                                         unsigned short aRedOffset,
                                         unsigned short aGreenOffset,
                                         unsigned short aBlueOffset);

        // Changes a single value of the look-up table
        virtual CyResult        SetRedValue    ( unsigned long aIndex, unsigned short aValue );
        virtual CyResult        SetGreenValue  ( unsigned long aIndex, unsigned short aValue );
        virtual CyResult        SetBlueValue   ( unsigned long aIndex, unsigned short aValue );

private:
    struct CyRGBFilterInternal : public CyObject
    {
        // Members
        unsigned long  mBitSize;
        unsigned long  mEntryCount;

        unsigned char* mRedTable8;
        unsigned char* mGreenTable8;
        unsigned char* mBlueTable8;

        unsigned short* mRedTable16;
        unsigned short* mGreenTable16;
        unsigned short* mBlueTable16;
    };

    struct CyRGBFilterInternal* mInternal;
};


// Inlines
/////////////////////////////////////////////////////////////////////////////

CY_FORCE_INLINE
unsigned long CyRGBFilter::GetBitSize() const
{
    return mInternal->mBitSize;
}


CY_FORCE_INLINE
unsigned long CyRGBFilter::GetEntryCount() const
{
    return mInternal->mEntryCount;
}


CY_FORCE_INLINE
unsigned char CyRGBFilter::GetRedValue8 ( unsigned long aIndex ) const
{
#ifdef _CY_DO_ASSERT_
    CyAssert( aIndex < GetEntryCount() );
    CyAssert( mInternal->mRedTable8 != 0 );
#endif

    return mInternal->mRedTable8[ aIndex % 256 ];
}


CY_FORCE_INLINE
unsigned char CyRGBFilter::GetGreenValue8 ( unsigned long aIndex ) const
{
#ifdef _CY_DO_ASSERT_
    CyAssert( aIndex < GetEntryCount() );
    CyAssert( mInternal->mGreenTable8 != 0 );
#endif

    return mInternal->mGreenTable8[ aIndex % 256 ];
}


CY_FORCE_INLINE
unsigned char CyRGBFilter::GetBlueValue8 ( unsigned long aIndex ) const
{
#ifdef _CY_DO_ASSERT_
    CyAssert( aIndex < GetEntryCount() );
    CyAssert( mInternal->mBlueTable8 != 0 );
#endif

    return mInternal->mBlueTable8[ aIndex % 256 ];
}



CY_FORCE_INLINE
unsigned short  CyRGBFilter::GetRedValue16 ( unsigned long aIndex ) const
{
#ifdef _CY_DO_ASSERT_
    CyAssert( GetBitSize() > 8 );
    CyAssert( GetBitSize() <= 16 );
    CyAssert( aIndex < GetEntryCount() );
    CyAssert( mInternal->mRedTable16 != 0 );
#endif

    // Note: normally we would use aIndex % mEntryCount as the index, but the % with a variable
    // slows things down terribly.  So we use only aIndex.
    return mInternal->mRedTable16[ aIndex ];
}


CY_FORCE_INLINE
unsigned short  CyRGBFilter::GetGreenValue16 ( unsigned long aIndex ) const
{
#ifdef _CY_DO_ASSERT_
    CyAssert( GetBitSize() > 8 );
    CyAssert( GetBitSize() <= 16 );
    CyAssert( aIndex < GetEntryCount() );
    CyAssert( mInternal->mGreenTable16 != 0 );
#endif

    // Note: normally we would use aIndex % mEntryCount as the index, but the % with a variable
    // slows things down terribly.  So we use only aIndex.
    return mInternal->mGreenTable16[ aIndex ];
}


CY_FORCE_INLINE
unsigned short  CyRGBFilter::GetBlueValue16 ( unsigned long aIndex ) const
{
#ifdef _CY_DO_ASSERT_
    CyAssert( GetBitSize() > 8 );
    CyAssert( GetBitSize() <= 16 );
    CyAssert( aIndex < GetEntryCount() );
    CyAssert( mInternal->mBlueTable16 != 0 );
#endif

    // Note: normally we would use aIndex % mEntryCount as the index, but the % with a variable
    // slows things down terribly.  So we use only aIndex.
    return mInternal->mBlueTable16[ aIndex ];
}
#endif // __cplusplus


// Standard C Wrapper
/////////////////////////////////////////////////////////////////////////////

// CyRGBFilter Handle
typedef void* CyRGBFilterH;

// Construction / Destruction
CY_IMG_LIB_C_API CyRGBFilterH   CyRGBFilter_Init( unsigned long aBitSize );
CY_IMG_LIB_C_API void           CyRGBFilter_Destroy( CyRGBFilterH aHandle );

// CyRGBFilter functions
CY_IMG_LIB_C_API unsigned long  CyRGBFilter_GetBitSize   ( CyRGBFilterH aHandle );
CY_IMG_LIB_C_API unsigned long  CyRGBFilter_GetEntryCount( CyRGBFilterH aHandle );

// Returns the 8-bit value or 16-bits value of an entry
// Note: these functions will not be as efficient as their C++ counterpart.
// The C++ methods are inlined and does not create a function call.
// The filter, when used INSIDE the wrapper functions WILL be as efficient as C++
CY_IMG_LIB_C_API unsigned char  CyRGBFilter_GetRedValue8   ( CyRGBFilterH  aHandle,
                                                             unsigned long aIndex );
CY_IMG_LIB_C_API unsigned char  CyRGBFilter_GetGreenValue8 ( CyRGBFilterH  aHandle,
                                                             unsigned long aIndex );
CY_IMG_LIB_C_API unsigned char  CyRGBFilter_GetBlueValue8  ( CyRGBFilterH  aHandle,
                                                             unsigned long aIndex );
CY_IMG_LIB_C_API unsigned short CyRGBFilter_GetRedValue16  ( CyRGBFilterH  aHandle,
                                                             unsigned long aIndex );
CY_IMG_LIB_C_API unsigned short CyRGBFilter_GetGreenValue16( CyRGBFilterH  aHandle,
                                                             unsigned long aIndex );
CY_IMG_LIB_C_API unsigned short CyRGBFilter_GetBlueValue16 ( CyRGBFilterH  aHandle,
                                                             unsigned long aIndex );

// Set the values of the filter's entries
CY_IMG_LIB_C_API CyResult CyRGBFilter_SetRedValue  ( CyRGBFilterH   aHandle,
                                                     unsigned long  aIndex,
                                                     unsigned short aValue );
CY_IMG_LIB_C_API CyResult CyRGBFilter_SetGreenValue( CyRGBFilterH   aHandle,
                                                     unsigned long  aIndex,
                                                     unsigned short aValue );
CY_IMG_LIB_C_API CyResult CyRGBFilter_SetBlueValue ( CyRGBFilterH   aHandle,
                                                     unsigned long  aIndex,
                                                     unsigned short aValue );

// Utility functions to apply gains and offsets to the filter
CY_IMG_LIB_C_API CyResult CyRGBFilter_SetMultipliers( CyRGBFilterH   aHandle,
                                                      double         aRedGain,
                                                      double         aGreenGain,
                                                      double         aBlueGain,
                                                      unsigned short aRedOffset,
                                                      unsigned short aGreenOffset,
                                                      unsigned short aBlueOffset );


#endif // __CY_RGB_FILTER_H__


