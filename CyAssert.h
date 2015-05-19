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
// File Name....: CyAssert.h
//
// Description..: Encapsulates the assert and disables it in release
//
// *****************************************************************************
//
// $Log$
//
// *****************************************************************************

#ifndef _CY_ASSERT_H_
#define _CY_ASSERT_H_

#if defined( _DEBUG ) && defined( _DRIVER_ )

    #define CyAssert(A) ASSERT(A)

#elif defined ( _DEBUG )

    #include <assert.h>
    #define CyAssert(A) assert(A)

#else

    #define CyAssert(A)

#endif

#endif // _CY_ASSERT_H_
