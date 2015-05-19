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
// File Name....: CyXMLDocument.h
//
// Description..: XML document, internally using Apache Xerces
//
// *****************************************************************************
//
// $Log$
//
// *****************************************************************************

#ifndef _CY_XML_DOCUMENT_H_
#define _CY_XML_DOCUMENT_H_

// Headers
/////////////////////////////////////////////////////////////////////////////

#include "CyTypes.h"
#include "CyErrorInterface.h"
#include "CyString.h"


// Class CyXMLDocument
/////////////////////////////////////////////////////////////////////////////

#ifdef __cplusplus
struct CyXMLDocumentInternal;
class CY_UTILS_LIB_API CyXMLDocument : public CyErrorInterface
{
// Constructors / Destructor
public:
            CyXMLDocument( const CyString& aFileName );
    virtual ~CyXMLDocument( );

// Methods
public:
    // save the document to file
    CyResult WriteToFile( );

    // Load the document from the file name
    CyResult LoadDocument( );

    // Create a new empty document
    CyResult CreateDocument( const CyString& aRoot,
                             unsigned char   aVersionMajor = 1,
                             unsigned char   aVersionMinor = 0 );

    // Document version
    // If no version is available, 0.0 is returned
    CyResult SetVersion( unsigned char  aVersionMajor,
                         unsigned char  aVersionMinor );
    CyResult GetVersion( unsigned char& aVersionMajor,
                         unsigned char& aVersionMinor ) const;
    CyResult GetVersion( double& aVersion ) const;

    // Element creation / deletion.
    CyResult CreateElement( const CyString& aName );
    CyResult DeleteElement( );

    // Create a child element with the specified value
    CyResult CreateElement( const CyString& aName,
                            const char*     aValue );
    CyResult CreateElement( const CyString& aName,
                            const CyString& aValue );
    CyResult CreateElement( const CyString& aName,
                            char            aValue );
    CyResult CreateElement( const CyString& aName,
                            unsigned char   aValue );
    CyResult CreateElement( const CyString& aName,
                            short           aValue );
    CyResult CreateElement( const CyString& aName,
                            unsigned short  aValue );
    CyResult CreateElement( const CyString& aName,
                            int             aValue );
    CyResult CreateElement( const CyString& aName,
                            unsigned int    aValue );
    CyResult CreateElement( const CyString& aName,
                            long            aValue );
    CyResult CreateElement( const CyString& aName,
                            unsigned long   aValue );
    CyResult CreateElement( const CyString&  aName,
                            __int64          aValue );
    CyResult CreateElement( const CyString&  aName,
                            unsigned __int64 aValue );
    CyResult CreateElement( const CyString& aName,
                            float           aValue );
    CyResult CreateElement( const CyString& aName,
                            double          aValue );
    CyResult CreateElement( const CyString& aName,
                            bool            aValue );


    // Properties of the current element
    CyResult SetName        ( const CyString& aName );
    CyResult GetName        ( CyString&       aName ) const;
    CyResult SetAttribute   ( const CyString& aAttrib,
                              const char*     aValue );
    CyResult SetAttribute   ( const CyString& aAttrib,
                              const CyString& aValue );
    CyResult SetAttribute   ( const CyString& aAttrib,
                              char            aValue );
    CyResult SetAttribute   ( const CyString& aAttrib,
                              unsigned char   aValue );
    CyResult SetAttribute   ( const CyString& aAttrib,
                              short           aValue );
    CyResult SetAttribute   ( const CyString& aAttrib,
                              unsigned short  aValue );
    CyResult SetAttribute   ( const CyString& aAttrib,
                              int             aValue );
    CyResult SetAttribute   ( const CyString& aAttrib,
                              unsigned int    aValue );
    CyResult SetAttribute   ( const CyString& aAttrib,
                              long            aValue );
    CyResult SetAttribute   ( const CyString& aAttrib,
                              unsigned long   aValue );
    CyResult SetAttribute   ( const CyString&  aAttrib,
                              __int64          aValue );
    CyResult SetAttribute   ( const CyString&  aAttrib,
                              unsigned __int64 aValue );
    CyResult SetAttribute   ( const CyString& aAttrib,
                              float           aValue );
    CyResult SetAttribute   ( const CyString& aAttrib,
                              double          aValue );
    CyResult SetAttribute   ( const CyString& aAttrib,
                              bool            aValue );
    CyResult RemoveAttribute( const CyString& aAttrib );
    CyResult GetAttribute   ( const CyString& aAttrib,
                              CyString&       aValue ) const;
    CyResult GetAttribute   ( const CyString& aAttrib,
                              char&           aValue ) const;
    CyResult GetAttribute   ( const CyString& aAttrib,
                              unsigned char&  aValue ) const;
    CyResult GetAttribute   ( const CyString& aAttrib,
                              short&          aValue ) const;
    CyResult GetAttribute   ( const CyString& aAttrib,
                              unsigned short& aValue ) const;
    CyResult GetAttribute   ( const CyString& aAttrib,
                              int&            aValue ) const;
    CyResult GetAttribute   ( const CyString& aAttrib,
                              unsigned int&   aValue ) const;
    CyResult GetAttribute   ( const CyString& aAttrib,
                              long&           aValue ) const;
    CyResult GetAttribute   ( const CyString& aAttrib,
                              unsigned long&  aValue ) const;
    CyResult GetAttribute   ( const CyString&   aAttrib,
                              __int64&          aValue ) const;
    CyResult GetAttribute   ( const CyString&   aAttrib,
                              unsigned __int64& aValue ) const;
    CyResult GetAttribute   ( const CyString& aAttrib,
                              float&          aValue ) const;
    CyResult GetAttribute   ( const CyString& aAttrib,
                              double&         aValue ) const;
    CyResult GetAttribute   ( const CyString& aAttrib,
                              bool&           aValue ) const;

    // Get/Set the value of the current element
    CyResult SetValue       ( const char* aValue );
    CyResult SetValue       ( const CyString& aValue );
    CyResult SetValue       ( char aValue );
    CyResult SetValue       ( unsigned char aValue );
    CyResult SetValue       ( short aValue );
    CyResult SetValue       ( unsigned short aValue );
    CyResult SetValue       ( int aValue );
    CyResult SetValue       ( unsigned int aValue );
    CyResult SetValue       ( long aValue );
    CyResult SetValue       ( unsigned long aValue );
    CyResult SetValue       ( __int64 aValue );
    CyResult SetValue       ( unsigned __int64 aValue );
    CyResult SetValue       ( float aValue );
    CyResult SetValue       ( double aValue );
    CyResult SetValue       ( bool aValue );
    CyResult GetValue       ( CyString& aValue) const;
    CyResult GetValue       ( char& aValue ) const;
    CyResult GetValue       ( unsigned char& aValue ) const;
    CyResult GetValue       ( short& aValue ) const;
    CyResult GetValue       ( unsigned short& aValue ) const;
    CyResult GetValue       ( int& aValue ) const;
    CyResult GetValue       ( unsigned int& aValue ) const;
    CyResult GetValue       ( long& aValue ) const;
    CyResult GetValue       ( unsigned long& aValue ) const;
    CyResult GetValue       ( __int64& aValue ) const;
    CyResult GetValue       ( unsigned __int64& aValue ) const;
    CyResult GetValue       ( float& aValue ) const;
    CyResult GetValue       ( double& aValue ) const;
    CyResult GetValue       ( bool& aValue ) const;

    // Get the value of a child element
    CyResult GetValue       ( const CyString& aName,
                              CyString& aValue) const;
    CyResult GetValue       ( const CyString& aName,
                              char& aValue ) const;
    CyResult GetValue       ( const CyString& aName,
                              unsigned char& aValue ) const;
    CyResult GetValue       ( const CyString& aName,
                              short& aValue ) const;
    CyResult GetValue       ( const CyString& aName,
                              unsigned short& aValue ) const;
    CyResult GetValue       ( const CyString& aName,
                              int& aValue ) const;
    CyResult GetValue       ( const CyString& aName,
                              unsigned int& aValue ) const;
    CyResult GetValue       ( const CyString& aName,
                              long& aValue ) const;
    CyResult GetValue       ( const CyString& aName,
                              unsigned long& aValue ) const;
    CyResult GetValue       ( const CyString& aName,
                              __int64& aValue ) const;
    CyResult GetValue       ( const CyString& aName,
                              unsigned __int64& aValue ) const;
    CyResult GetValue       ( const CyString& aName,
                              float& aValue ) const;
    CyResult GetValue       ( const CyString& aName,
                              double& aValue ) const;
    CyResult GetValue       ( const CyString& aName,
                              bool& aValue ) const;

    // Go to the parent element
    CyResult GotoParentElement();
    bool     HasChildElements();

    // Find a child  element base on name in the current node
    // if successful, the current element will be set on the found element
    CyResult GotoElement( const CyString& aName );
    CyResult GotoElement( const CyString& aName,
                          const CyString& aAttrib,
                          const CyString& aValue );

    // Push/pop current XML location
    CyResult PushLocation();
    CyResult PopLocation();

    // Traverse the sibling elements
    CyResult GotoPreviousElement();
    CyResult GotoNextElement    ();

    // Goto to the child elements
    CyResult GotoFirstChild();
    CyResult GotoLastChild();

    
// Members
private:
    struct CyXMLDocumentInternal* mInternal;

private:
    CyXMLDocument( const CyXMLDocument& );
    CyXMLDocument& operator=( const CyXMLDocument& );
};
#endif // __cplusplus


// Standard C Wrapper
/////////////////////////////////////////////////////////////////////////////

// CyXMLDocument Handle
typedef void* CyXMLDocumentH;

// Construction - Destruction
CY_UTILS_LIB_C_API CyXMLDocumentH CyXMLDocument_Init( const char * aFileName );
CY_UTILS_LIB_C_API void           CyXMLDocument_Destroy( CyXMLDocumentH aHandle );

// Document parsing and creation
CY_UTILS_LIB_C_API CyResult       CyXMLDocument_LoadDocument  ( CyXMLDocumentH aHandle );
CY_UTILS_LIB_C_API CyResult       CyXMLDocument_CreateDocument( CyXMLDocumentH aHandle,
                                                                const char*    aRoot );

// Save a document to file
CY_UTILS_LIB_C_API CyResult       CyXMLDocument_WriteToFile( CyXMLDocumentH aHandle );

// Creates an element at the current level and moves the current location to it
CY_UTILS_LIB_C_API CyResult CyXMLDocument_CreateElement( CyXMLDocumentH aHandle,
                                                         const char*    aName );

// Delete the current element and moves to the parent element
CY_UTILS_LIB_C_API CyResult CyXMLDocument_DeleteElement( CyXMLDocumentH aHandle );

// Create a child element with the specified value
CY_UTILS_LIB_C_API CyResult CyXMLDocument_CreateElementString( CyXMLDocumentH aHandle,
                                                               const char*    aName,
                                                               const char*    aValue );
CY_UTILS_LIB_C_API CyResult CyXMLDocument_CreateElementChar  ( CyXMLDocumentH aHandle,
                                                               const char*    aName,
                                                               char           aValue );
CY_UTILS_LIB_C_API CyResult CyXMLDocument_CreateElementByte  ( CyXMLDocumentH aHandle,
                                                               const char*    aName,
                                                               unsigned char  aValue );
CY_UTILS_LIB_C_API CyResult CyXMLDocument_CreateElementShort ( CyXMLDocumentH aHandle,
                                                               const char*    aName,
                                                               short          aValue );
CY_UTILS_LIB_C_API CyResult CyXMLDocument_CreateElementUShort( CyXMLDocumentH aHandle,
                                                               const char*    aName,
                                                               unsigned short aValue );
CY_UTILS_LIB_C_API CyResult CyXMLDocument_CreateElementInt   ( CyXMLDocumentH aHandle,
                                                               const char*    aName,
                                                               int            aValue );
CY_UTILS_LIB_C_API CyResult CyXMLDocument_CreateElementUInt  ( CyXMLDocumentH aHandle,
                                                               const char*    aName,
                                                               unsigned int   aValue );
CY_UTILS_LIB_C_API CyResult CyXMLDocument_CreateElementLong  ( CyXMLDocumentH aHandle,
                                                               const char*    aName,
                                                               long           aValue );
CY_UTILS_LIB_C_API CyResult CyXMLDocument_CreateElementULong ( CyXMLDocumentH aHandle,
                                                               const char*    aName,
                                                               unsigned long  aValue );
CY_UTILS_LIB_C_API CyResult CyXMLDocument_CreateElementInt64 ( CyXMLDocumentH   aHandle,
                                                               const char*      aName,
                                                               __int64          aValue );
CY_UTILS_LIB_C_API CyResult CyXMLDocument_CreateElementUInt64( CyXMLDocumentH   aHandle,
                                                               const char*      aName,
                                                               unsigned __int64 aValue );
CY_UTILS_LIB_C_API CyResult CyXMLDocument_CreateElementFloat ( CyXMLDocumentH aHandle,
                                                               const char*    aName,
                                                               float          aValue );
CY_UTILS_LIB_C_API CyResult CyXMLDocument_CreateElementDouble( CyXMLDocumentH aHandle,
                                                               const char*    aName,
                                                               double         aValue );
CY_UTILS_LIB_C_API CyResult CyXMLDocument_CreateElementBool  ( CyXMLDocumentH aHandle,
                                                               const char*    aName,
                                                               int            aValue );

// Set/Get the properties of the current element
CY_UTILS_LIB_C_API CyResult CyXMLDocument_SetName ( CyXMLDocumentH aHandle,
                                                    const char*    aName );
CY_UTILS_LIB_C_API CyResult CyXMLDocument_GetName ( CyXMLDocumentH aHandle,
                                                    char*          aBuffer,
                                                    unsigned long  aBufferSize );

CY_UTILS_LIB_C_API CyResult CyXMLDocument_RemoveAttribute   ( CyXMLDocumentH  aHandle,
                                                              const char*     aAttrib );

CY_UTILS_LIB_C_API CyResult CyXMLDocument_SetAttributeString( CyXMLDocumentH  aHandle,
                                                              const char*     aName,
                                                              const char*     aAttrib );
CY_UTILS_LIB_C_API CyResult CyXMLDocument_SetAttributeChar  ( CyXMLDocumentH  aHandle,
                                                              const char*     aName,
                                                              char            aAttrib );
CY_UTILS_LIB_C_API CyResult CyXMLDocument_SetAttributeByte  ( CyXMLDocumentH  aHandle,
                                                              const char*     aName,
                                                              unsigned char   aAttrib );
CY_UTILS_LIB_C_API CyResult CyXMLDocument_SetAttributeShort ( CyXMLDocumentH  aHandle,
                                                              const char*     aName,
                                                              short           aAttrib );
CY_UTILS_LIB_C_API CyResult CyXMLDocument_SetAttributeUShort( CyXMLDocumentH  aHandle,
                                                              const char*     aName,
                                                              unsigned short  aAttrib );
CY_UTILS_LIB_C_API CyResult CyXMLDocument_SetAttributeInt   ( CyXMLDocumentH  aHandle,
                                                              const char*     aName,
                                                              int             aAttrib );
CY_UTILS_LIB_C_API CyResult CyXMLDocument_SetAttributeUInt  ( CyXMLDocumentH  aHandle,
                                                              const char*     aName,
                                                              unsigned int    aAttrib );
CY_UTILS_LIB_C_API CyResult CyXMLDocument_SetAttributeLong  ( CyXMLDocumentH  aHandle,
                                                              const char*     aName,
                                                              long            aAttrib );
CY_UTILS_LIB_C_API CyResult CyXMLDocument_SetAttributeULong( CyXMLDocumentH   aHandle,
                                                              const char*     aName,
                                                              unsigned long   aAttrib );
CY_UTILS_LIB_C_API CyResult CyXMLDocument_SetAttributeInt64 ( CyXMLDocumentH   aHandle,
                                                              const char*      aName,
                                                              __int64          aAttrib );
CY_UTILS_LIB_C_API CyResult CyXMLDocument_SetAttributeUInt64( CyXMLDocumentH    aHandle,
                                                              const char*      aName,
                                                              unsigned __int64 aAttrib );
CY_UTILS_LIB_C_API CyResult CyXMLDocument_SetAttributeFloat ( CyXMLDocumentH  aHandle,
                                                              const char*     aName,
                                                              float           aAttrib );
CY_UTILS_LIB_C_API CyResult CyXMLDocument_SetAttributeDouble( CyXMLDocumentH  aHandle,
                                                              const char*     aName,
                                                              double          aAttrib );
CY_UTILS_LIB_C_API CyResult CyXMLDocument_SetAttributeBool  ( CyXMLDocumentH  aHandle,
                                                              const char*     aName,
                                                              int             aAttrib );
CY_UTILS_LIB_C_API CyResult CyXMLDocument_GetAttributeString( CyXMLDocumentH  aHandle,
                                                              const char*     aName,
                                                              char*           aBuffer,
                                                              unsigned long*  aBufferSize );
CY_UTILS_LIB_C_API CyResult CyXMLDocument_GetAttributeChar  ( CyXMLDocumentH  aHandle,
                                                              const char*     aName,
                                                              char*           aAttrib );
CY_UTILS_LIB_C_API CyResult CyXMLDocument_GetAttributeByte  ( CyXMLDocumentH  aHandle,
                                                              const char*     aName,
                                                              unsigned char*  aAttrib );
CY_UTILS_LIB_C_API CyResult CyXMLDocument_GetAttributeShort ( CyXMLDocumentH  aHandle,
                                                              const char*     aName,
                                                              short*          aAttrib );
CY_UTILS_LIB_C_API CyResult CyXMLDocument_GetAttributeUShort( CyXMLDocumentH  aHandle,
                                                              const char*     aName,
                                                              unsigned short* aAttrib );
CY_UTILS_LIB_C_API CyResult CyXMLDocument_GetAttributeInt   ( CyXMLDocumentH  aHandle,
                                                              const char*     aName,
                                                              int*            aAttrib );
CY_UTILS_LIB_C_API CyResult CyXMLDocument_GetAttributeUInt  ( CyXMLDocumentH  aHandle,
                                                              const char*     aName,
                                                              unsigned int*   aAttrib );
CY_UTILS_LIB_C_API CyResult CyXMLDocument_GetAttributeLong  ( CyXMLDocumentH  aHandle,
                                                              const char*     aName,
                                                              long*           aAttrib );
CY_UTILS_LIB_C_API CyResult CyXMLDocument_GetAttributeULong ( CyXMLDocumentH   aHandle,
                                                              const char*     aName,
                                                              unsigned long*  aAttrib );
CY_UTILS_LIB_C_API CyResult CyXMLDocument_GetAttributeInt64 ( CyXMLDocumentH    aHandle,
                                                              const char*       aName,
                                                              __int64*          aAttrib );
CY_UTILS_LIB_C_API CyResult CyXMLDocument_GetAttributeUInt64( CyXMLDocumentH    aHandle,
                                                              const char*       aName,
                                                              unsigned __int64* aAttrib );
CY_UTILS_LIB_C_API CyResult CyXMLDocument_GetAttributeFloat ( CyXMLDocumentH  aHandle,
                                                              const char*     aName,
                                                              float*          aAttrib );
CY_UTILS_LIB_C_API CyResult CyXMLDocument_GetAttributeDouble( CyXMLDocumentH  aHandle,
                                                              const char*     aName,
                                                              double*         aAttrib );
CY_UTILS_LIB_C_API CyResult CyXMLDocument_GetAttributeBool  ( CyXMLDocumentH  aHandle,
                                                              const char*     aName,
                                                              int*            aAttrib );


// Get/Set the value of the current element
CY_UTILS_LIB_C_API CyResult CyXMLDocument_SetValueString  ( CyXMLDocumentH aHandle,
                                                            const char*    aValue );
CY_UTILS_LIB_C_API CyResult CyXMLDocument_SetValueChar    ( CyXMLDocumentH aHandle,
                                                            char           aValue );
CY_UTILS_LIB_C_API CyResult CyXMLDocument_SetValueByte    ( CyXMLDocumentH aHandle,
                                                            unsigned char  aValue );
CY_UTILS_LIB_C_API CyResult CyXMLDocument_SetValueShort   ( CyXMLDocumentH aHandle,
                                                            short          aValue );
CY_UTILS_LIB_C_API CyResult CyXMLDocument_SetValueUShort  ( CyXMLDocumentH aHandle,
                                                            unsigned short aValue );
CY_UTILS_LIB_C_API CyResult CyXMLDocument_SetValueInt     ( CyXMLDocumentH aHandle,
                                                            int            aValue );
CY_UTILS_LIB_C_API CyResult CyXMLDocument_SetValueUInt    ( CyXMLDocumentH aHandle,
                                                            unsigned int   aValue );
CY_UTILS_LIB_C_API CyResult CyXMLDocument_SetValueLong    ( CyXMLDocumentH aHandle,
                                                            long           aValue );
CY_UTILS_LIB_C_API CyResult CyXMLDocument_SetValueULong   ( CyXMLDocumentH aHandle,
                                                            unsigned long aValue );
CY_UTILS_LIB_C_API CyResult CyXMLDocument_SetValueInt64   ( CyXMLDocumentH aHandle,
                                                            __int64         aValue );
CY_UTILS_LIB_C_API CyResult CyXMLDocument_SetValueUInt64  ( CyXMLDocumentH aHandle,
                                                            unsigned __int64 aValue );
CY_UTILS_LIB_C_API CyResult CyXMLDocument_SetValueFloat   ( CyXMLDocumentH aHandle,
                                                            float          aValue );
CY_UTILS_LIB_C_API CyResult CyXMLDocument_SetValueDouble  ( CyXMLDocumentH aHandle,
                                                            double         aValue );
CY_UTILS_LIB_C_API CyResult CyXMLDocument_SetValueBool    ( CyXMLDocumentH aHandle,
                                                            int            aValue );
CY_UTILS_LIB_C_API CyResult CyXMLDocument_GetValueString  ( CyXMLDocumentH  aHandle,
                                                            char*           aBuffer,
                                                            unsigned long   aBufferSize );
CY_UTILS_LIB_C_API CyResult CyXMLDocument_GetValueChar    ( CyXMLDocumentH  aHandle,
                                                            char*           aValue );
CY_UTILS_LIB_C_API CyResult CyXMLDocument_GetValueByte    ( CyXMLDocumentH  aHandle,
                                                            unsigned char*  aValue );
CY_UTILS_LIB_C_API CyResult CyXMLDocument_GetValueShort   ( CyXMLDocumentH  aHandle,
                                                            short*          aValue );
CY_UTILS_LIB_C_API CyResult CyXMLDocument_GetValueUShort  ( CyXMLDocumentH  aHandle,
                                                            unsigned short* aValue );
CY_UTILS_LIB_C_API CyResult CyXMLDocument_GetValueInt     ( CyXMLDocumentH  aHandle,
                                                            int*            aValue );
CY_UTILS_LIB_C_API CyResult CyXMLDocument_GetValueUInt    ( CyXMLDocumentH  aHandle,
                                                            unsigned int*   aValue );
CY_UTILS_LIB_C_API CyResult CyXMLDocument_GetValueLong    ( CyXMLDocumentH  aHandle,
                                                            long*           aValue );
CY_UTILS_LIB_C_API CyResult CyXMLDocument_GetValueULong   ( CyXMLDocumentH  aHandle,
                                                            unsigned long*  aValue );
CY_UTILS_LIB_C_API CyResult CyXMLDocument_GetValueInt64   ( CyXMLDocumentH    aHandle,
                                                            __int64*          aValue );
CY_UTILS_LIB_C_API CyResult CyXMLDocument_GetValueUInt64  ( CyXMLDocumentH    aHandle,
                                                            unsigned __int64* aValue );
CY_UTILS_LIB_C_API CyResult CyXMLDocument_GetValueFloat   ( CyXMLDocumentH  aHandle,
                                                            float*          aValue );
CY_UTILS_LIB_C_API CyResult CyXMLDocument_GetValueDouble  ( CyXMLDocumentH  aHandle,
                                                            double*         aValue );
CY_UTILS_LIB_C_API CyResult CyXMLDocument_GetValueBool    ( CyXMLDocumentH  aHandle,
                                                            int*            aValue );

// Get the value of a chilf element
CY_UTILS_LIB_C_API CyResult CyXMLDocument_GetSubValueString ( CyXMLDocumentH  aHandle,
                                                              const char*     aName,
                                                              char*           aBuffer,
                                                              unsigned long   aBufferSize );
CY_UTILS_LIB_C_API CyResult CyXMLDocument_GetSubValueChar   ( CyXMLDocumentH  aHandle,
                                                              const char*     aName,
                                                              char*           aValue );
CY_UTILS_LIB_C_API CyResult CyXMLDocument_GetSubValueByte   ( CyXMLDocumentH  aHandle,
                                                              const char*     aName,
                                                              unsigned char*  aValue );
CY_UTILS_LIB_C_API CyResult CyXMLDocument_GetSubValueShort  ( CyXMLDocumentH  aHandle,
                                                              const char*     aName,
                                                              short*          aValue );
CY_UTILS_LIB_C_API CyResult CyXMLDocument_GetSubValueUShort ( CyXMLDocumentH  aHandle,
                                                              const char*     aName,
                                                              unsigned short* aValue );
CY_UTILS_LIB_C_API CyResult CyXMLDocument_GetSubValueInt    ( CyXMLDocumentH  aHandle,
                                                              const char*     aName,
                                                              int*            aValue );
CY_UTILS_LIB_C_API CyResult CyXMLDocument_GetSubValueUInt   ( CyXMLDocumentH  aHandle,
                                                              const char*     aName,
                                                              unsigned int*   aValue );
CY_UTILS_LIB_C_API CyResult CyXMLDocument_GetSubValueLong   ( CyXMLDocumentH  aHandle,
                                                              const char*     aName,
                                                              long*           aValue );
CY_UTILS_LIB_C_API CyResult CyXMLDocument_GetSubValueULong  ( CyXMLDocumentH  aHandle,
                                                              const char*     aName,
                                                              unsigned long*  aValue );
CY_UTILS_LIB_C_API CyResult CyXMLDocument_GetSubValueInt64  ( CyXMLDocumentH  aHandle,
                                                              const char*     aName,
                                                              __int64*        aValue );
CY_UTILS_LIB_C_API CyResult CyXMLDocument_GetSubValueUInt64 ( CyXMLDocumentH  aHandle,
                                                              const char*     aName,
                                                              unsigned __int64* aValue );
CY_UTILS_LIB_C_API CyResult CyXMLDocument_GetSubValueFloat  ( CyXMLDocumentH  aHandle,
                                                              const char*     aName,
                                                              float*          aValue );
CY_UTILS_LIB_C_API CyResult CyXMLDocument_GetSubValueDouble ( CyXMLDocumentH  aHandle,
                                                              const char*     aName,
                                                              double*         aValue );
CY_UTILS_LIB_C_API CyResult CyXMLDocument_GetSubValueBool   ( CyXMLDocumentH  aHandle,
                                                              const char*     aName,
                                                              int*            aValue );

// Document traversing
CY_UTILS_LIB_C_API CyResult CyXMLDocument_GotoParentElement  ( CyXMLDocumentH aHandle );
CY_UTILS_LIB_C_API int      CyXMLDocument_HasChildElements   ( CyXMLDocumentH aHandle );
CY_UTILS_LIB_C_API CyResult CyXMLDocument_GotoElement        ( CyXMLDocumentH aHandle,
                                                               const char*    aName );
CY_UTILS_LIB_C_API CyResult CyXMLDocument_GotoElementAttrib  ( CyXMLDocumentH aHandle,
                                                               const char*    aName,
                                                               const char*    aAttrib,
                                                               const char*    aValue );
CY_UTILS_LIB_C_API CyResult CyXMLDocument_GotoPreviousElement( CyXMLDocumentH aHandle );
CY_UTILS_LIB_C_API CyResult CyXMLDocument_GotoNextElement    ( CyXMLDocumentH aHandle );
CY_UTILS_LIB_C_API CyResult CyXMLDocument_GotoFirstChild     ( CyXMLDocumentH aHandle );
CY_UTILS_LIB_C_API CyResult CyXMLDocument_GotoLastChild      ( CyXMLDocumentH aHandle );


#endif // _CY_XML_DOCUMENT_H__
