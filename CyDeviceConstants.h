// *****************************************************************************
//
// $Id$
//
// cy1h02b1
//
// *****************************************************************************
//
//     Copyright (c) 2002-2003, Pleora Technologies Inc., All rights reserved.
//
// *****************************************************************************
//
// File Name....: CyDeviceConstants.h
//
// Description..: 
//
// *****************************************************************************
//
// $Log$
//
// *****************************************************************************

#ifndef _CY_DEVICE_CONSTANTS_H_
#define _CY_DEVICE_CONSTANTS_H_

// Callback Identifiers
/////////////////////////////////////////////////////////////////////////////

enum CyDeviceCallbackIDs
{

    CY_DEVICE_CB_ON_DEVICE_RESET   = 0,
    CY_DEVICE_CB_ON_INTERRUPT_GPIO = 1,

};


// Port Identifiers
/////////////////////////////////////////////////////////////////////////////

enum CyDevicePorts
{

    CY_DEVICE_PORT_INTERNAL = 0,
    CY_DEVICE_PORT_SERIAL_0 = 1,
    CY_DEVICE_PORT_SERIAL_1 = 2,
    CY_DEVICE_PORT_I2C      = 3,
    CY_DEVICE_PORT_USRT_0   = 4, // deprecated, replaced with BULK_0
    CY_DEVICE_PORT_BULK_0   = 4,
    CY_DEVICE_PORT_BUS_0    = 5,
    CY_DEVICE_PORT_BULK_1   = 6,
    CY_DEVICE_PORT_BULK_2   = 7,
    CY_DEVICE_PORT_BULK_3   = 8,

};



// Flags
/////////////////////////////////////////////////////////////////////////////

enum CyDeviceFlags
{

    CY_DEVICE_FLAG_COMMAND_ONLY                 = 0x00000001,
    CY_DEVICE_FLAG_SET_IP_ON_CONNECT            = 0x00000002,
    CY_DEVICE_FLAG_BAD_IMAGE_PASSTHROUGH        = 0x00000004,
    CY_DEVICE_FLAG_DATA_ONLY                    = 0x00000008,
    CY_DEVICE_FLAG_NO_RESEND_PACKETS            = 0x00000010,
    CY_DEVICE_FLAG_MULTICAST_NO_DATA            = 0x00000020,
    CY_DEVICE_FLAG_NO_DATA_LINK_CHECK_ON_ERROR  = 0x00000040,
    CY_DEVICE_FLAG_NO_LOAD_EXTENSION_ON_CONNECT = 0x00000100,
    CY_DEVICE_FLAG_NO_INTERRUPT_PORT_KEEP_ALIVE = 0x00000200,

};


// Device Access modes
/////////////////////////////////////////////////////////////////////////////

enum CyDeviceAccessModes
{

    CY_DEVICE_ACCESS_MODE_DRV    = 0,
    CY_DEVICE_ACCESS_MODE_UDP    = 1,
    CY_DEVICE_ACCESS_MODE_TCP    = 2,
    CY_DEVICE_ACCESS_MODE_FILTER = 3,

};

// Data Sending Modes
/////////////////////////////////////////////////////////////////////////////

enum CyDeviceDataSendingModes
{

    CY_DEVICE_DSM_UNICAST       = 0,
    CY_DEVICE_DSM_MULTICAST	    = 1,
    CY_DEVICE_DSM_MULTI_UNICAST = 2,
    CY_DEVICE_DSM_ROUND_ROBIN   = 3,
    CY_DEVICE_DSM_TRIGGER_QUEUE = 4,

};


// Miscellaneous
/////////////////////////////////////////////////////////////////////////////

    // Maximum pending receive data
    #define CY_DEVICE_MAX_PENDING_RECEIVE_DATA      4


// Parameters for the CyDevice object
/////////////////////////////////////////////////////////////////////////////

//     
//  IMPORTANT: The parameter identifiers 0x00000000 - 0x0000fff are reserved.
//             Do not use in your own applications
//
// Each parameter is defined by an identifier and a label, where
//
//  CY_DEVICE_PARAM_name is the identifier
//  CY_DEVICE_PARAM_name_LABEL is the label
//
// These constant can be used with the Set/GetParameter functions (as derived
// from CyParameterRepository).
//

    // This parameter is read-only when the device is connected
    #define CY_DEVICE_PARAM_DEVICE_ID                           0x00000000
    #define CY_DEVICE_PARAM_DEVICE_ID_LABEL                     "Device ID"

    // This parameter is read-only when the device is connected
    #define CY_DEVICE_PARAM_MODULE_ID                           0x00000001
    #define CY_DEVICE_PARAM_MODULE_ID_LABEL                     "Module ID"

    // This parameter is read-only when the device is connected
    #define CY_DEVICE_PARAM_SUB_MODULE_ID                       0x00000002
    #define CY_DEVICE_PARAM_SUB_MODULE_ID_LABEL                 "Sub Module ID"

    // This parameter is read-only when the device is connected
    #define CY_DEVICE_PARAM_VENDOR_ID                           0x00000003
    #define CY_DEVICE_PARAM_VENDOR_ID_LABEL                     "Vendor ID"

    // This parameter is read-only when the device is connected
    #define CY_DEVICE_PARAM_VERSION_MAJ                         0x00000004
    #define CY_DEVICE_PARAM_VERSION_MAJ_LABEL                   "Version Major"

    // This parameter is read-only when the device is connected
    #define CY_DEVICE_PARAM_VERSION_MIN                         0x00000005
    #define CY_DEVICE_PARAM_VERSION_MIN_LABEL                   "Version Minor"

    #define CY_DEVICE_PARAM_ANSWER_TIMEOUT                      0x00000006
    #define CY_DEVICE_PARAM_ANSWER_TIMEOUT_LABEL                "Answer Timeout"

    #define CY_DEVICE_PARAM_FIRST_PACKET_TIMEOUT                0x00000007
    #define CY_DEVICE_PARAM_FIRST_PACKET_TIMEOUT_LABEL          "First Packet Timeout"

    #define CY_DEVICE_PARAM_PACKET_TIMEOUT                      0x00000008
    #define CY_DEVICE_PARAM_PACKET_TIMEOUT_LABEL                "Packet Timeout"

    #define CY_DEVICE_PARAM_REQUEST_TIMEOUT                     0x00000009
    #define CY_DEVICE_PARAM_REQUEST_TIMEOUT_LABEL               "Request Timeout"

    #define CY_DEVICE_PARAM_COMMAND_RETRY_COUNT                 0x0000000A
    #define CY_DEVICE_PARAM_COMMAND_RETRY_COUNT_LABEL           "Command Retry Count"

    #define CY_DEVICE_PARAM_PACKET_SIZE                         0x0000000B
    #define CY_DEVICE_PARAM_PACKET_SIZE_LABEL                   "Packet Size"

    // This parameter is read-only when the device is connected
    #define CY_DEVICE_PARAM_ADAPTER_ID                          0x0000000C
    #define CY_DEVICE_PARAM_ADAPTER_ID_LABEL                    "Adapter ID"

    // This parameter is read-only when the device is connected
    #define CY_DEVICE_PARAM_IP                                  0x0000000D
    #define CY_DEVICE_PARAM_IP_LABEL                            "IP Address"

    // This parameter is read-only when the device is connected
    #define CY_DEVICE_PARAM_MAC                                 0x0000000E
    #define CY_DEVICE_PARAM_MAC_LABEL                           "MAC Address"

    // This parameter is read-only when the device is connected
    #define CY_DEVICE_PARAM_DEVICE_MODE                         0x0000000F
    #define CY_DEVICE_PARAM_DEVICE_MODE_LABEL                   "Device Mode"

    // This parameter is read-only when the device is connected
    #define CY_DEVICE_PARAM_DEVICE_NAME                         0x00000010
    #define CY_DEVICE_PARAM_DEVICE_NAME_LABEL                   "Device Name"
    
    // This parameter is read-only when the device is connected
    #define CY_DEVICE_PARAM_DEVICE_TYPE                         0x00000011
    #define CY_DEVICE_PARAM_DEVICE_TYPE_LABEL                   "Device Type"

    // This parameter is read-only and indicates if the device supports
    // a hearbeat or not
    #define CY_DEVICE_PARAM_SUPPORTS_HEARTBEAT                  0x00000012
    #define CY_DEVICE_PARAM_SUPPORTS_HEARTBEAT_LABEL            "Supports Heartbeat"

    #define CY_DEVICE_PARAM_ENABLE_HEARTBEAT                    0x00000013
    #define CY_DEVICE_PARAM_ENABLE_HEARTBEAT_LABEL              "Enable Heartbeat"
                                                        
    // This parameter is read-only when the device is connected
    #define CY_DEVICE_PARAM_HEARTBEAT_INTERVAL                  0x00000014
    #define CY_DEVICE_PARAM_HEARTBEAT_INTERVAL_LABEL            "Heartbeat Interval"
                                                        
    // This parameter is read-only when the device is connected
    #define CY_DEVICE_PARAM_HEARTBEAT_EXPIRATION                0x00000015
    #define CY_DEVICE_PARAM_HEARTBEAT_EXPIRATION_LABEL          "Heartbeat Expiration"

    // This parameter is read-only when the device is connected
    #define CY_DEVICE_PARAM_DATA_SENDING_MODE                   0x00000017
    #define CY_DEVICE_PARAM_DATA_SENDING_MODE_LABEL             "Data Sending Mode"

    // This parameter is read-only when the device is connected
    #define CY_DEVICE_PARAM_DATA_SENDING_MODE_MASTER            0x00000018
    #define CY_DEVICE_PARAM_DATA_SENDING_MODE_MASTER_LABEL      "Data Sending Mode Master"

    // This parameter is read-only when the device is connected
    #define CY_DEVICE_PARAM_DATA_SENDING_MODE_ADDRESS           0x00000019
    #define CY_DEVICE_PARAM_DATA_SENDING_MODE_ADDRESS_LABEL     "Data Sending Mode Address"

    // This parameter is read-only when the device is connected
    #define CY_DEVICE_PARAM_CHANNEL_COUNT                       0x0000001A
    #define CY_DEVICE_PARAM_CHANNEL_COUNT_LABEL                 "Channel Count"

    #define CY_DEVICE_PARAM_DATA_GENERATOR                      0x0000001B
    #define CY_DEVICE_PARAM_DATA_GENERATOR_LABEL                "Data Generator"

    #define CY_DEVICE_PARAM_RECEIVE_ANSWER_BEHAVIOUR            0x0000001C
    #define CY_DEVICE_PARAM_RECEIVE_ANSWER_BEHAVIOUR_LABEL      "ReceiveAnswer Behaviour"

    // The following parameters controls the socket ports used when using the
    // Netword Stack.  There are 3 ports to configure: command, interrupt and
    // data.  A value of 0 indicates that the network stack can use any 
    // available port
    #define CY_DEVICE_PARAM_STACK_COMMAND_PORT                  0x00000020
    #define CY_DEVICE_PARAM_STACK_COMMAND_PORT_LABEL            "Network Stack UDP Command Port"
    #define CY_DEVICE_PARAM_STACK_INTERRUPT_PORT                0x00000021
    #define CY_DEVICE_PARAM_STACK_INTERRUPT_PORT_LABEL          "Network Stack UDP Interrupt Port"
    #define CY_DEVICE_PARAM_STACK_DATA_PORT                     0x00000022
    #define CY_DEVICE_PARAM_STACK_DATA_PORT_LABEL               "Network Stack UDP Data Port"

#endif // _CY_DEVICE_CONSTANTS_H_


