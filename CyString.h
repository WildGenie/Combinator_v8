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
// File Name....: CyString.h
//
// Description..: Encapsulates a STL string.  The internal is actually a string
//                This is encapsulated to remove any dependencies on STL for cross
//                compiler support    
//
// *****************************************************************************
//
// $Log$
//
// *****************************************************************************

#ifndef _CY_STRING_H_
#define _CY_STRING_H_

// Includes
/////////////////////////////////////////////////////////////////////////////

#ifdef _UNIX_
#include <sys/types.h>
#endif // _UNIX_

#include "CyUtilsLib.h"
#include "CyTypes.h"
#include <stdlib.h>

// We include the STL string in order to generate the inline constructor that
// for the user's version of the STL Library.
#ifdef __cplusplus
#include <string>
#endif


// class
/////////////////////////////////////////////////////////////////////////////

#ifdef __cplusplus
struct CyStringInternal;
class CyString
{
    // Types
    public:
        typedef char     ascii_type;
        typedef wchar_t  unicode_type;

#ifdef UNICODE
        typedef unicode_type value_type;
#else // UNICODE
        typedef ascii_type   value_type;
#endif // UNICODE

		typedef size_t size_type;
        enum { npos = -1 };


    // Construction/Destruction
    public:
        CY_UTILS_LIB_API CyString();
        CY_UTILS_LIB_API CyString( const CyString& s, size_type pos = 0, size_type n = npos );
        CY_UTILS_LIB_API CyString( const ascii_type* s );
        CY_UTILS_LIB_API CyString( const ascii_type* s, size_type n );
        CY_UTILS_LIB_API CyString( const unicode_type* s );
        CY_UTILS_LIB_API CyString( const unicode_type* s, size_type n );
        CY_UTILS_LIB_API CyString( const ascii_type c );
        CY_UTILS_LIB_API CyString( const ascii_type c, size_type n );
        CY_UTILS_LIB_API CyString( const unicode_type c );
        CY_UTILS_LIB_API CyString( const unicode_type c, size_type n );
        CY_UTILS_LIB_API ~CyString();

        // This constructor is inlined and will be generated with the user's 
        // STL implementation and compiler.
        CyString( const std::string& aString );
        CyString( const std::wstring& aString );

    // Indicates if the internal string is unicode or not
        CY_UTILS_LIB_API bool IsUnicode() const;

    // accessors
        CY_UTILS_LIB_API size_type size() const;
        CY_UTILS_LIB_API size_type length() const;
        CY_UTILS_LIB_API size_type max_size() const;
        CY_UTILS_LIB_API size_type capacity() const;
        CY_UTILS_LIB_API bool empty() const;
        CY_UTILS_LIB_API const ascii_type* c_str_ascii() const;
        CY_UTILS_LIB_API const unicode_type* c_str_unicode() const;
        CY_UTILS_LIB_API const ascii_type* data_ascii() const;
        CY_UTILS_LIB_API const unicode_type* data_unicode() const;

    // The following methods change depending if the compiler is using UNICODE or not.
    // They are inlined at the end of this header file
        const value_type* c_str() const;
        const value_type* data() const;
        const value_type& operator[](size_type n) const;

    // Copy operator
        CY_UTILS_LIB_API CyString& operator=(const CyString&);
        CY_UTILS_LIB_API CyString& operator=(const ascii_type* s);
        CY_UTILS_LIB_API CyString& operator=(const unicode_type* s);
        CY_UTILS_LIB_API CyString& operator=(ascii_type c);
        CY_UTILS_LIB_API CyString& operator=(unicode_type c);


    // Comparison
        CY_UTILS_LIB_API int compare(const CyString& s) const;
        CY_UTILS_LIB_API int compare(size_type pos, size_type n, const CyString& s) const;
        CY_UTILS_LIB_API int compare(size_type pos, size_type n, const CyString& s, size_type pos1, size_type n1) const;
        CY_UTILS_LIB_API int compare(const ascii_type* s) const;
        CY_UTILS_LIB_API int compare(const unicode_type* s) const;
        CY_UTILS_LIB_API int compare(size_type pos, size_type n, const ascii_type* s, size_type len = npos) const;       
        CY_UTILS_LIB_API int compare(size_type pos, size_type n, const unicode_type* s, size_type len = npos) const;       
        CY_UTILS_LIB_API bool operator==( const CyString& s ) const;
        CY_UTILS_LIB_API bool operator==( const ascii_type* s ) const;
        CY_UTILS_LIB_API bool operator==( const unicode_type* s ) const;
        CY_UTILS_LIB_API bool operator!=( const CyString& s ) const;
        CY_UTILS_LIB_API bool operator!=( const ascii_type* s ) const;
        CY_UTILS_LIB_API bool operator!=( const unicode_type* s ) const;
        CY_UTILS_LIB_API bool operator<( const CyString& s ) const;
        CY_UTILS_LIB_API bool operator<( const ascii_type* s ) const;
        CY_UTILS_LIB_API bool operator<( const unicode_type* s ) const;


    // Insertion
        CY_UTILS_LIB_API CyString& insert(size_type pos, const CyString& s);
        CY_UTILS_LIB_API CyString& insert(size_type pos, const CyString& s, size_type pos1, size_type n);
        CY_UTILS_LIB_API CyString& insert(size_type pos, const ascii_type* s);
        CY_UTILS_LIB_API CyString& insert(size_type pos, const unicode_type* s);
        CY_UTILS_LIB_API CyString& insert(size_type pos, const ascii_type* s, size_type n);
        CY_UTILS_LIB_API CyString& insert(size_type pos, const unicode_type* s, size_type n);
        CY_UTILS_LIB_API CyString& insert(size_type pos, size_type n, ascii_type c);
        CY_UTILS_LIB_API CyString& insert(size_type pos, size_type n, unicode_type c);


    // Append
        CY_UTILS_LIB_API CyString& append(const CyString& s);
        CY_UTILS_LIB_API CyString& append(const CyString& s, size_type pos, size_type n);
        CY_UTILS_LIB_API CyString& append(const ascii_type* s);
        CY_UTILS_LIB_API CyString& append(const unicode_type* s);
        CY_UTILS_LIB_API CyString& append(const ascii_type* s, size_type n);
        CY_UTILS_LIB_API CyString& append(const unicode_type* s, size_type n);
        CY_UTILS_LIB_API CyString& append(size_type n, ascii_type c);
        CY_UTILS_LIB_API CyString& append(size_type n, unicode_type c);
        CY_UTILS_LIB_API void push_back(ascii_type c);
        CY_UTILS_LIB_API void push_back(unicode_type c);
        CY_UTILS_LIB_API CyString& operator+=(const CyString& s);
        CY_UTILS_LIB_API CyString& operator+=(const ascii_type* s);
        CY_UTILS_LIB_API CyString& operator+=(const unicode_type* s);
        CY_UTILS_LIB_API CyString& operator+=(ascii_type c);
        CY_UTILS_LIB_API CyString& operator+=(unicode_type c);


    // Deletion
        CY_UTILS_LIB_API CyString& erase(size_type pos = 0, size_type n = npos);
        CY_UTILS_LIB_API void resize(size_type n, ascii_type c = ascii_type() );
        CY_UTILS_LIB_API void resize(size_type n, unicode_type c );

    // Assignement
        CY_UTILS_LIB_API CyString& assign(const CyString&);
        CY_UTILS_LIB_API CyString& assign(const CyString& s, size_type pos, size_type n);
        CY_UTILS_LIB_API CyString& assign(const ascii_type* s, size_type n);
        CY_UTILS_LIB_API CyString& assign(const unicode_type* s, size_type n);
        CY_UTILS_LIB_API CyString& assign(const ascii_type* s);
        CY_UTILS_LIB_API CyString& assign(const unicode_type* s);
        CY_UTILS_LIB_API CyString& assign(size_type n, ascii_type c);
        CY_UTILS_LIB_API CyString& assign(size_type n, unicode_type c);


    // Replacement
        CY_UTILS_LIB_API CyString& replace(size_type pos, size_type n, const CyString& s);
        CY_UTILS_LIB_API CyString& replace(size_type pos, size_type n, const CyString& s, size_type pos1, size_type n1);
        CY_UTILS_LIB_API CyString& replace(size_type pos, size_type n, const ascii_type* s, size_type n1);
        CY_UTILS_LIB_API CyString& replace(size_type pos, size_type n, const unicode_type* s, size_type n1);
        CY_UTILS_LIB_API CyString& replace(size_type pos, size_type n, const ascii_type* s);
        CY_UTILS_LIB_API CyString& replace(size_type pos, size_type n, const unicode_type* s);
        CY_UTILS_LIB_API CyString& replace(size_type pos, size_type n, size_type n1, ascii_type c);
        CY_UTILS_LIB_API CyString& replace(size_type pos, size_type n, size_type n1, unicode_type c);


    // Search
        CY_UTILS_LIB_API size_type find(const CyString& s, size_type pos = 0) const;
        CY_UTILS_LIB_API size_type find(const ascii_type* s, size_type pos, size_type n) const;
        CY_UTILS_LIB_API size_type find(const unicode_type* s, size_type pos, size_type n) const;
        CY_UTILS_LIB_API size_type find(const ascii_type* s, size_type pos = 0) const;
        CY_UTILS_LIB_API size_type find(const unicode_type* s, size_type pos = 0) const;
        CY_UTILS_LIB_API size_type find(ascii_type c, size_type pos = 0) const;
        CY_UTILS_LIB_API size_type find(unicode_type c, size_type pos = 0) const;
        CY_UTILS_LIB_API size_type rfind(const CyString& s, size_type pos = npos) const;
        CY_UTILS_LIB_API size_type rfind(const ascii_type* s, size_type pos, size_type n) const;
        CY_UTILS_LIB_API size_type rfind(const unicode_type* s, size_type pos, size_type n) const;
        CY_UTILS_LIB_API size_type rfind(const ascii_type* s, size_type pos = npos) const;
        CY_UTILS_LIB_API size_type rfind(const unicode_type* s, size_type pos = npos) const;
        CY_UTILS_LIB_API size_type rfind(ascii_type c, size_type pos = npos) const;
        CY_UTILS_LIB_API size_type rfind(unicode_type c, size_type pos = npos) const;
        CY_UTILS_LIB_API size_type find_first_of(const CyString& s, size_type pos = 0) const;
        CY_UTILS_LIB_API size_type find_first_of(const ascii_type* s, size_type pos, size_type n) const;
        CY_UTILS_LIB_API size_type find_first_of(const unicode_type* s, size_type pos, size_type n) const;
        CY_UTILS_LIB_API size_type find_first_of(const ascii_type* s, size_type pos = 0) const;
        CY_UTILS_LIB_API size_type find_first_of(const unicode_type* s, size_type pos = 0) const;
        CY_UTILS_LIB_API size_type find_first_of(ascii_type c, size_type pos = 0) const;
        CY_UTILS_LIB_API size_type find_first_of(unicode_type c, size_type pos = 0) const;
        CY_UTILS_LIB_API size_type find_first_not_of(const CyString& s, size_type pos = 0) const;
        CY_UTILS_LIB_API size_type find_first_not_of(const ascii_type* s, size_type pos, size_type n) const;
        CY_UTILS_LIB_API size_type find_first_not_of(const unicode_type* s, size_type pos, size_type n) const;
        CY_UTILS_LIB_API size_type find_first_not_of(const ascii_type* s, size_type pos = 0) const;
        CY_UTILS_LIB_API size_type find_first_not_of(const unicode_type* s, size_type pos = 0) const;
        CY_UTILS_LIB_API size_type find_first_not_of(ascii_type c, size_type pos = 0) const;
        CY_UTILS_LIB_API size_type find_first_not_of(unicode_type c, size_type pos = 0) const;
        CY_UTILS_LIB_API size_type find_last_of(const CyString& s, size_type pos = npos) const;
        CY_UTILS_LIB_API size_type find_last_of(const ascii_type* s, size_type pos, size_type n) const;
        CY_UTILS_LIB_API size_type find_last_of(const unicode_type* s, size_type pos, size_type n) const;
        CY_UTILS_LIB_API size_type find_last_of(const ascii_type* s, size_type pos = npos) const;
        CY_UTILS_LIB_API size_type find_last_of(const unicode_type* s, size_type pos = npos) const;
        CY_UTILS_LIB_API size_type find_last_of(ascii_type c, size_type pos = npos) const;
        CY_UTILS_LIB_API size_type find_last_of(unicode_type c, size_type pos = npos) const;
        CY_UTILS_LIB_API size_type find_last_not_of(const CyString& s, size_type pos = npos) const;
        CY_UTILS_LIB_API size_type find_last_not_of(const ascii_type* s, size_type pos, size_type n) const;
        CY_UTILS_LIB_API size_type find_last_not_of(const unicode_type* s, size_type pos, size_type n) const;
        CY_UTILS_LIB_API size_type find_last_not_of(const ascii_type* s, size_type pos = npos) const;
        CY_UTILS_LIB_API size_type find_last_not_of(const unicode_type* s, size_type pos = npos) const;
        CY_UTILS_LIB_API size_type find_last_not_of(ascii_type c, size_type pos = npos) const;
        CY_UTILS_LIB_API size_type find_last_not_of(unicode_type c, size_type pos = npos) const;

    
    // Miscellaneous
        CY_UTILS_LIB_API void reserve(size_t);
        CY_UTILS_LIB_API CyString substr(size_type pos = 0, size_type n = npos) const;

    // in order to support the inline constructor from an STL string
    private:
        CY_UTILS_LIB_API void Construct( const ascii_type* s );
        CY_UTILS_LIB_API void Construct( const unicode_type* s );

    private:
        struct CyStringInternal* mInternal;
};


// Inlines
/////////////////////////////////////////////////////////////////////////////

CY_INLINE CyString::CyString( const std::string& aString )
{
    Construct( (const ascii_type*)aString.c_str() );
}
CY_INLINE CyString::CyString( const std::wstring& aString )
{
    Construct( (const unicode_type*)aString.c_str() );
}

CY_INLINE const CyString::value_type& CyString::operator[](size_type n) const
{
    return c_str()[ n ];
}

#ifdef UNICODE
    CY_INLINE const CyString::value_type* CyString::c_str() const
    {
        return c_str_unicode();
    }
    CY_INLINE const CyString::value_type* CyString::data() const
    {
        return c_str_unicode();
    }
#else // UNICODE
    CY_INLINE const CyString::value_type* CyString::c_str() const
    {
        return c_str_ascii();
    }
    CY_INLINE const CyString::value_type* CyString::data() const
    {
        return c_str_ascii();
    }
#endif //  UNICODE

#endif // __cplusplus

#endif // _CY_STRING_H_

