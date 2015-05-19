// *****************************************************************************
//
// $Id$
//
// cy1h02b1
//
// *****************************************************************************
//
//     Copyright (c) 2003, Pleora Technologies Inc., All rights reserved.
//
// *****************************************************************************
//
// File Name....: CyDeviceFinder.h
//
// Description..: Utility class that searches for devices on the network, either
//                by UDP or Driver                
//
// *****************************************************************************
//
// $Log$
//
// *****************************************************************************

#ifndef _CY_DEVICE_FINDER_H_
#define _CY_DEVICE_FINDER_H_

// Includes
/////////////////////////////////////////////////////////////////////////////

#include <CyTypes.h>
#include <CyErrorInterface.h>
#include "CyComLib.h"
#include "CyConfig.h"
#include "CyAdapterID.h"
#include <CyString.h>

// Class
/////////////////////////////////////////////////////////////////////////////

// Device Entry used for the C wrapping functions
struct CyDeviceEntry
#ifdef __cplusplus
    : public CyObject
#endif
{
    unsigned long mMode;     // access mode
    char          mAdapterID[ 256 ];
    char          mAddressIP[ 256 ];
    char          mAddressMAC[ 256 ];
    unsigned char mDeviceID;
    unsigned char mModuleID;
    unsigned char mSubID;
    unsigned char mVendorID;
    unsigned char mSoftVerMaj;
    unsigned char mSoftVerMin;
    char          mMulticastAddress[ 256 ];
    char          mDeviceName[ 256 ];
    unsigned char mChannelCount;
    unsigned long mSendingMode; // CY_DEVICE_DSM_XXX
};


// Finder callback function for the C Wrapping functions
typedef int (CY_CALLING_CONV * CyDeviceFinderCallback )( struct CyDeviceEntry* aDevice,
                                                         void*                 aContext );


// Class
/////////////////////////////////////////////////////////////////////////////

#ifdef __cplusplus
class CyDeviceFinder : public CyErrorInterface
{
// Types
public:
    // Data for an entry
    struct DeviceEntry
    {
        CyConfig::AccessMode mMode; // access mode
        CyAdapterID          mAdapterID;
        CyString             mAddressIP;
        CyString             mAddressMAC;
        unsigned char        mDeviceID;
        unsigned char        mModuleID;
        unsigned char        mSubID;
        unsigned char        mVendorID;
        unsigned char        mSoftVerMaj;
        unsigned char        mSoftVerMin;
        CyString             mMulticastAddress;
        CyString             mDeviceName;
        unsigned char        mChannelCount;
        unsigned long        mSendingMode; // CY_DEVICE_DSM_XXX

        CY_COM_LIB_API DeviceEntry();
        CY_COM_LIB_API DeviceEntry( const DeviceEntry& aEntry );
        CY_COM_LIB_API DeviceEntry& operator=( const DeviceEntry& aEntry );
        CY_COM_LIB_API bool operator==( const DeviceEntry& aEntry ) const;
    };

    // List of entries found
    struct DeviceListInternal;
    class CY_COM_LIB_API DeviceList : public CyObject
    {
        // Iterator
        public:
            struct IteratorInternal;
            class CY_COM_LIB_API Iterator : public CyObject
            {
                public:
                    typedef DeviceEntry value_type;
                    typedef value_type& reference;
                    typedef value_type* pointer;
                    Iterator();
                    Iterator( const Iterator& aItr );
                    ~Iterator();
                    const Iterator& operator=( const Iterator& aItr ) const;

                    reference operator*() const;
                    Iterator& operator++();
                    Iterator  operator++(int);
                    const Iterator& operator++() const;
                    const Iterator  operator++(int) const;

                    bool operator==( const Iterator& aItr ) const;
                    bool operator!=( const Iterator& aItr ) const;
                    bool operator<( const Iterator& aItr ) const;

                private:
                    friend class DeviceList;
                    struct IteratorInternal* mInternal;
            };


        // types
            typedef Iterator iterator;
            typedef const Iterator const_iterator;


        // Construction/Destruction
        public:
            DeviceList();
            ~DeviceList();

        // clear the list
            void clear();

        // Iterating the list
            iterator begin();
            iterator end();
            const_iterator begin() const;
            const_iterator end() const;

        // entry access
            bool empty() const;
            unsigned long size() const;
            const DeviceEntry& operator[]( int aIndex ) const;

        // Entry addition
            void push_back( const DeviceEntry& aEntry );

        private:
            friend class CyDeviceFinder;
            struct DeviceListInternal* mInternal;
    };

    // Callback when a device is found
    typedef bool (CY_CALLING_CONV * Callback )( const DeviceEntry&   aDevice,
                                                void*                aContext );

// Construction/Destruction
public:
    CY_COM_LIB_API CyDeviceFinder( );
    CY_COM_LIB_API virtual ~CyDeviceFinder();


// Select a device, using a user interface
public:
    CY_COM_LIB_API virtual  CyResult SelectDevice( DeviceEntry& aEntry,
                                                   void*        aParent = NULL,
                                                   const char*  aTitle = NULL );


// methods
public:

    // Find the devices
    CY_COM_LIB_API virtual  CyResult Find( CyConfig::AccessMode aAccessMode,
                                           DeviceList&          aList,
                                           unsigned int         aTimeOut,
                                           bool                 aFlushList,
                                           Callback             aCallback = 0,
                                           void*                aContext = 0 ) const;

    // Apply an IP to a device
    CY_COM_LIB_API virtual  CyResult SetIP( CyConfig::AccessMode aAccessMode,
                                            const CyAdapterID&   aAdapterID,
                                            const CyString&      aMAC,
                                            const CyString&      aIP,
                                            const CyString&      aSubnetMask = CyString(),
                                            const CyString&      aGateway  = CyString() ) const;

    // Give a local device name to a device based on MAC address
    CY_COM_LIB_API virtual  CyResult SetName( const CyString& aMAC,
                                              const CyString& aName ) const;
    CY_COM_LIB_API virtual  CyResult GetName( const CyString& aMAC,
                                              CyString&       aName ) const;
};
#endif // __cplusplus


// Standard C Wrapper
/////////////////////////////////////////////////////////////////////////////

// CyDeviceFinder handles
typedef void* CyDeviceFinderH;

// Constructor/Destructor
CY_COM_LIB_C_API CyDeviceFinderH CyDeviceFinder_Init();
CY_COM_LIB_C_API void CyDeviceFinder_Destroy( CyDeviceFinderH aHandle );

// Select a device using the built-in UI.  The aParent is used as a HWND internally on Windows
CY_COM_LIB_C_API CyResult CyDeviceFinder_SelectDevice( CyDeviceFinderH        aHandle,
                                                       struct CyDeviceEntry*  aEntry,
                                                       void*                  aParent );

// Find available devices and invokes the specified callback for each item that is found
CY_COM_LIB_C_API CyResult CyDeviceFinder_Find( CyDeviceFinderH        aHandle,
                                               unsigned long          aAccessMode,
                                               unsigned int           aTimeOut,
                                               CyDeviceFinderCallback aCallback,
                                               void*                  aContext );

// Changes the IP of a device
CY_COM_LIB_C_API CyResult CyDeviceFinder_SetIP  ( CyDeviceFinderH  aHandle,
                                                  unsigned long    aAccessMode,
                                                  CyAdapterIDH     aAdapterID,
                                                  const char*      aMAC,
                                                  const char*      aIP,
                                                  const char*      aSubnetMask,
                                                  const char*      aGateway );

// Changes or gets the name of a device
CY_COM_LIB_C_API CyResult CyDeviceFinder_SetName( CyDeviceFinderH  aHandle,
                                                  const char*      aMAC,
                                                  const char*      aName );
CY_COM_LIB_C_API CyResult CyDeviceFinder_GetName( CyDeviceFinderH  aHandle,
                                                  const char*      aMAC,
                                                  char*            aBuffer,
                                                  unsigned long    aBufferSize );
#endif
