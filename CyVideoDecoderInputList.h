// *****************************************************************************
//
// $Id$
//
// cy1h11b1
//
// *****************************************************************************
//
//     Copyright (c) 2003, Pleora Technologies Inc., All rights reserved.
//
// *****************************************************************************
//
// File Name....: CyVideoDecoderInputList.h
//
// Description..: 
//
// *****************************************************************************
//
// $Log$
//
// *****************************************************************************

#ifndef __CY_VIDEO_DECODER_INPUT_LIST_H__
#define __CY_VIDEO_DECODER_INPUT_LIST_H__

// Headers
/////////////////////////////////////////////////////////////////////////////

// ===== This Project =====
#include "CyVideoDecoderLib.h"


// Class
/////////////////////////////////////////////////////////////////////////////

#ifdef __cplusplus
class CY_VIDEO_LIB_API CyVideoDecoderInputList
{
    // Construction/Destruction
    public:
        CyVideoDecoderInputList();
        CyVideoDecoderInputList( const CyVideoDecoderInputList& aList );
        ~CyVideoDecoderInputList();
        
    // Copy operator
        CyVideoDecoderInputList& operator=( const CyVideoDecoderInputList& aObj );


    // Clear, Insertion
        void Clear();
        void push_back( unsigned char aNumber, const CyString& aName );

    // Access
        unsigned long   GetInputCount() const;
        unsigned char   GetInputNumber( unsigned long aIndex ) const;
        const CyString& GetInputName( unsigned long aIndex ) const;

    // find an input in the list
        bool FindInputByNumber( unsigned char aNumber ) const;

    private:
        void* mInputs;
};
#endif // __cplusplus

#endif // __CY_VIDEO_DECODER_INPUT_LIST_H__



