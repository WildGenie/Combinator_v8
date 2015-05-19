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
// File Name....: CyDeviceExtensionConstants.h
//
// Description..: 
//
// *****************************************************************************
//
// $Log$
//
// *****************************************************************************

#ifndef _CY_DEVICE_EXTENSION_CONSTANTS_H_
#define _CY_DEVICE_EXTENSION_CONSTANTS_H_


// Pulse Generator Extension
/////////////////////////////////////////////////////////////////////////////

// Identifier of the extensions
// Range 0x00000000 - 0x0000000F are reserved for up to 16 pulse generators

#define CY_DEVICE_EXT_PULSE_GENERATOR           0x00000000

    // 
    #define CY_PULSE_GEN_PARAM_WIDTH                0x00000000
    #define CY_PULSE_GEN_PARAM_WIDTH_LABEL          "Width"

    #define CY_PULSE_GEN_PARAM_DELAY                0x00000001
    #define CY_PULSE_GEN_PARAM_DELAY_LABEL          "Delay"

    #define CY_PULSE_GEN_PARAM_GRANULARITY          0x00000002
    #define CY_PULSE_GEN_PARAM_GRANULARITY_LABEL    "Granularity"

    #define CY_PULSE_GEN_PARAM_PERIODIC             0x00000003
    #define CY_PULSE_GEN_PARAM_PERIODIC_LABEL       "Periodic"

    #define CY_PULSE_GEN_PARAM_TRIGGER_MODE         0x00000004
    #define CY_PULSE_GEN_PARAM_TRIGGER_MODE_LABEL   "Trigger Mode"

    // This parameter is read-only
    #define CY_PULSE_GEN_PARAM_PERIOD               0x00000005
    #define CY_PULSE_GEN_PARAM_PERIOD_LABEL         "Pulse Period (ns)"

    // This parameter is read-only
    #define CY_PULSE_GEN_PARAM_FREQUENCY            0x00000006
    #define CY_PULSE_GEN_PARAM_FREQUENCY_LABEL      "Pulse Frequency (Hz)"


// Rescaler Extension
/////////////////////////////////////////////////////////////////////////////

// Identifier of the extensions
// Range 0x00000010 - 0x0000001F are reserved for up to 16 rescalers

#define CY_DEVICE_EXT_RESCALER                  0x00000010

    #define CY_RESCALER_PARAM_GRANULARITY           0x00000000
    #define CY_RESCALER_PARAM_GRANULARITY_LABEL     "Granularity"

    #define CY_RESCALER_PARAM_MULTIPLIER            0x00000001
    #define CY_RESCALER_PARAM_MULTIPLIER_LABEL      "Multiplier"

    #define CY_RESCALER_PARAM_DIVIDER               0x00000002
    #define CY_RESCALER_PARAM_DIVIDER_LABEL         "Divider"
                                                    
    #define CY_RESCALER_PARAM_INPUT                 0x00000003
    #define CY_RESCALER_PARAM_INPUT_LABEL           "Input Selection"
                                                    
    #define CY_RESCALER_PARAM_BACKUP_ENABLED        0x00000004
    #define CY_RESCALER_PARAM_BACKUP_ENABLED_LABEL  "Backup Enabled"
                                                    
    #define CY_RESCALER_PARAM_BACKUP_WINDOW         0x00000005
    #define CY_RESCALER_PARAM_BACKUP_WINDOW_LABEL   "Backup Window"
                                                    
    #define CY_RESCALER_PARAM_BACKUP_INPUT          0x00000006
    #define CY_RESCALER_PARAM_BACKUP_INPUT_LABEL    "Backup Input"
                                                    
    // This parameter is read-only                                                    
    #define CY_RESCALER_PARAM_INPUT_FREQUENCY       0x00000007
    #define CY_RESCALER_PARAM_INPUT_FREQUENCY_LABEL "Input Frequency"

    // This parameter is read-only                                                    
    #define CY_RESCALER_PARAM_OUTPUT_FREQUENCY       0x00000008
    #define CY_RESCALER_PARAM_OUTPUT_FREQUENCY_LABEL "Output Frequency"

    // For the best rescaler settings:
    //      Set the target frequency after SetParameter for the target,
    //      the recommended granularity, multiplier and divider will be available

    #define CY_RESCALER_PARAM_TARGET_FREQUENCY          0x00000009
    #define CY_RESCALER_PARAM_TARGET_FREQUENCY_LABEL    "Target Frequency"

    // The following parameters are read-only
    #define CY_RESCALER_PARAM_BEST_GRANULARITY          0x0000000A
    #define CY_RESCALER_PARAM_BEST_GRANULARITY_LABEL    "Recommended Granularity"
    #define CY_RESCALER_PARAM_BEST_MULTIPLIER           0x0000000B
    #define CY_RESCALER_PARAM_BEST_MULTIPLIER_LABEL     "Recommended Multiplier"
    #define CY_RESCALER_PARAM_BEST_DIVIDER              0x0000000C
    #define CY_RESCALER_PARAM_BEST_DIVIDER_LABEL        "Recommended Divider"

    #define CY_RESCALER_PARAM_RESCALER_SIZE             0x0000000D
    #define CY_RESCALER_PARAM_RESCALER_SIZE_LABEL       "Rescaler Size"


// Counter Extension
/////////////////////////////////////////////////////////////////////////////

// Identifier of the extensions
// Range 0x00000020 - 0x0000002F are reserved for up to 16 Counters

#define CY_DEVICE_EXT_COUNTER                   0x00000020

    #define CY_COUNTER_PARAM_UP_EVENT               0x00000000
    #define CY_COUNTER_PARAM_UP_EVENT_LABEL         "Up Event"

    #define CY_COUNTER_PARAM_DOWN_EVENT             0x00000001
    #define CY_COUNTER_PARAM_DOWN_EVENT_LABEL       "Down Event"

    #define CY_COUNTER_PARAM_CLEAR_EVENT            0x00000002
    #define CY_COUNTER_PARAM_CLEAR_EVENT_LABEL      "Clear Event"

    #define CY_COUNTER_PARAM_CLEAR_INPUT            0x00000003
    #define CY_COUNTER_PARAM_CLEAR_INPUT_LABEL      "Input"

    #define CY_COUNTER_PARAM_COMPARE_VALUE          0x00000004
    #define CY_COUNTER_PARAM_COMPARE_VALUE_LABEL    "Compare Value"

    // The following parameter is read-only!
    #define CY_COUNTER_PARAM_CURRENT_VALUE          0x00000005
    #define CY_COUNTER_PARAM_CURRENT_VALUE_LABEL    "Current Counter Value"


// Delayer Extension
/////////////////////////////////////////////////////////////////////////////

// Identifier of the extensions
// Range 0x00000030 - 0x0000003f are reserved for up to 16 Delayers

#define CY_DEVICE_EXT_DELAYER                   0x00000030

    #define CY_DELAYER_PARAM_DELAY                  0x00000000
    #define CY_DELAYER_PARAM_DELAY_LABEL            "Delay"

    #define CY_DELAYER_PARAM_REFERENCE              0x00000001
    #define CY_DELAYER_PARAM_REFERENCE_LABEL        "Reference"

    #define CY_DELAYER_PARAM_INPUT                  0x00000002
    #define CY_DELAYER_PARAM_INPUT_LABEL            "Input"


// GPIO Look-Up Table Extension
// Includes the GPIO Configuration
/////////////////////////////////////////////////////////////////////////////

// Identifier of extension
#define CY_DEVICE_EXT_GPIO_LUT                  0x00001000

    #define CY_GPIO_LUT_PARAM_INPUT_CONFIG0             0x00000000
    #define CY_GPIO_LUT_PARAM_INPUT_CONFIG0_LABEL       "Input 0 Configuration"

    #define CY_GPIO_LUT_PARAM_INPUT_CONFIG1             0x00000001
    #define CY_GPIO_LUT_PARAM_INPUT_CONFIG1_LABEL       "Input 1 Configuration"

    #define CY_GPIO_LUT_PARAM_INPUT_CONFIG2             0x00000002
    #define CY_GPIO_LUT_PARAM_INPUT_CONFIG2_LABEL       "Input 2 Configuration"

    #define CY_GPIO_LUT_PARAM_INPUT_CONFIG3             0x00000003
    #define CY_GPIO_LUT_PARAM_INPUT_CONFIG3_LABEL       "Input 3 Configuration"

    #define CY_GPIO_LUT_PARAM_INPUT_CONFIG4             0x00000004
    #define CY_GPIO_LUT_PARAM_INPUT_CONFIG4_LABEL       "Input 4 Configuration"

    #define CY_GPIO_LUT_PARAM_INPUT_CONFIG5             0x00000005
    #define CY_GPIO_LUT_PARAM_INPUT_CONFIG5_LABEL       "Input 5 Configuration"

    #define CY_GPIO_LUT_PARAM_INPUT_CONFIG6             0x00000006
    #define CY_GPIO_LUT_PARAM_INPUT_CONFIG6_LABEL       "Input 6 Configuration"

    #define CY_GPIO_LUT_PARAM_INPUT_CONFIG7             0x00000007
    #define CY_GPIO_LUT_PARAM_INPUT_CONFIG7_LABEL       "Input 7 Configuration"

    #define CY_GPIO_LUT_PARAM_GPIO_LUT_PROGRAM          0x00000008
    #define CY_GPIO_LUT_PARAM_GPIO_LUT_PROGRAM_LABEL    "LUT Program"


// Debouncer Extension
////////////////////////////////////////////////////////////////////////////////

// Identifier of extension
#define CY_DEVICE_EXT_DEBOUNCING                0x00001001

    #define CY_DEBOUNCING_PARAM_INPUT0                  0x00000000
    #define CY_DEBOUNCING_PARAM_INPUT0_LABEL            "Input 0"

    #define CY_DEBOUNCING_PARAM_INPUT1                  0x00000001
    #define CY_DEBOUNCING_PARAM_INPUT1_LABEL            "Input 1"

    #define CY_DEBOUNCING_PARAM_INPUT2                  0x00000002
    #define CY_DEBOUNCING_PARAM_INPUT2_LABEL            "Input 2"

    #define CY_DEBOUNCING_PARAM_INPUT3                  0x00000003
    #define CY_DEBOUNCING_PARAM_INPUT3_LABEL            "Input 3"


// GPIO Configuration
////////////////////////////////////////////////////////////////////////////////

// Identifier of extension
#define CY_DEVICE_EXT_GPIO_FUNCTION_SELECT      0x00001002

    #define CY_GPIO_FUNCTION_SELECT_INPUT0              0x00000000
    #define CY_GPIO_FUNCTION_SELECT_INPUT0_LABEL        "Input 0 Configuration"

    #define CY_GPIO_FUNCTION_SELECT_INPUT1              0x00000001
    #define CY_GPIO_FUNCTION_SELECT_INPUT1_LABEL        "Input 1 Configuration"

    #define CY_GPIO_FUNCTION_SELECT_INPUT2              0x00000002
    #define CY_GPIO_FUNCTION_SELECT_INPUT2_LABEL        "Input 2 Configuration"

    #define CY_GPIO_FUNCTION_SELECT_INPUT3              0x00000003
    #define CY_GPIO_FUNCTION_SELECT_INPUT3_LABEL        "Input 3 Configuration"

    #define CY_GPIO_FUNCTION_SELECT_OUTPUT0             0x00000004
    #define CY_GPIO_FUNCTION_SELECT_OUTPUT0_LABEL       "Output 0 Configuration"

    #define CY_GPIO_FUNCTION_SELECT_OUTPUT1             0x00000005
    #define CY_GPIO_FUNCTION_SELECT_OUTPUT1_LABEL       "Output 1 Configuration"

    #define CY_GPIO_FUNCTION_SELECT_OUTPUT2             0x00000006
    #define CY_GPIO_FUNCTION_SELECT_OUTPUT2_LABEL       "Output 2 Configuration"

    #define CY_GPIO_FUNCTION_SELECT_OUTPUT3             0x00000007
    #define CY_GPIO_FUNCTION_SELECT_OUTPUT3_LABEL       "Output 3 Configuration"

    #define CY_GPIO_FUNCTION_SELECT_SYNCHRO             0x00000008
    #define CY_GPIO_FUNCTION_SELECT_SYNCHRO_LABEL       "GPIO Synchronization Mode"

    #define CY_GPIO_FUNCTION_SELECT_CC1                 0x00000009
    #define CY_GPIO_FUNCTION_SELECT_CC1_LABEL           "CC1 Configuration"

    #define CY_GPIO_FUNCTION_SELECT_CC2                 0x0000000A
    #define CY_GPIO_FUNCTION_SELECT_CC2_LABEL           "CC2 Configuration"

    #define CY_GPIO_FUNCTION_SELECT_CC3                 0x0000000B
    #define CY_GPIO_FUNCTION_SELECT_CC3_LABEL           "CC3 Configuration"

    #define CY_GPIO_FUNCTION_SELECT_CC4                 0x0000000C
    #define CY_GPIO_FUNCTION_SELECT_CC4_LABEL           "CC4 Configuration"


// Timestamp Counter Extension
/////////////////////////////////////////////////////////////////////////////

// Identifier of extension
#define CY_DEVICE_EXT_TIMESTAMP_COUNTER         0x00001003

    #define CY_TIMESTAMP_PARAM_GRANULARITY              0x00000000
    #define CY_TIMESTAMP_PARAM_GRANULARITY_LABEL        "Granularity"

    #define CY_TIMESTAMP_PARAM_SET_MODE                 0x00000001
    #define CY_TIMESTAMP_PARAM_SET_MODE_LABEL           "Set Mode"

    #define CY_TIMESTAMP_PARAM_SET_INPUT                0x00000002
    #define CY_TIMESTAMP_PARAM_SET_INPUT_LABEL          "Set Input"

    #define CY_TIMESTAMP_PARAM_CLEAR_MODE               0x00000003
    #define CY_TIMESTAMP_PARAM_CLEAR_MODE_LABEL         "Clear Mode"

    #define CY_TIMESTAMP_PARAM_CLEAR_INPUT              0x00000004
    #define CY_TIMESTAMP_PARAM_CLEAR_INPUT_LABEL        "Clear Input"

    #define CY_TIMESTAMP_PARAM_COUNTER_SELECT           0x00000005
    #define CY_TIMESTAMP_PARAM_COUNTER_SELECT_LABEL     "Counter Select"

    #define CY_TIMESTAMP_PARAM_BROADCAST                0x00000007
    #define CY_TIMESTAMP_PARAM_BROADCAST_LABEL          "Broadcast"

    #define CY_TIMESTAMP_PARAM_SET_VALUE                0x00000008
    #define CY_TIMESTAMP_PARAM_SET_VALUE_LABEL          "Set Value"

    // this parameter is read-only
    #define CY_TIMESTAMP_PARAM_CURRENT_VALUE            0x00000009
    #define CY_TIMESTAMP_PARAM_CURRENT_VALUE_LABEL      "Current Value"


// Timestamp Triggers Extension
/////////////////////////////////////////////////////////////////////////////

// Identifier of extension
#define CY_DEVICE_EXT_TIMESTAMP_TRIGGERS        0x00001004

    // This parameter is read-only
    #define CY_TIMESTAMP_TRIG_PARAM_FIFO_FULL           0x00000000
    #define CY_TIMESTAMP_TRIG_PARAM_FIFO_FULL_LABEL     "Trigger Fifo Full"

    // This parameter is read-only
    #define CY_TIMESTAMP_TRIG_PARAM_FIFO_EMPTY          0x00000001
    #define CY_TIMESTAMP_TRIG_PARAM_FIFO_EMPTY_LABEL    "Trigger Fifo Empty"

    // When adding a trigger, you need to set the following three parameters,
    // then set the "CY_TIMESTAMP_TRIG_PARAM_ARM" parameter to 1 to arm the trigger.
    // When MASK is 0, all the triggers are cleared.

    #define CY_TIMESTAMP_TRIG_PARAM_MASK                0x00000002
    #define CY_TIMESTAMP_TRIG_PARAM_MASK_LABEL          "Trigger Mask"

    #define CY_TIMESTAMP_TRIG_PARAM_COUNTER_SELECT       0x00000003
    #define CY_TIMESTAMP_TRIG_PARAM_COUNTER_SELECT_LABEL "Counter Select"

    #define CY_TIMESTAMP_TRIG_PARAM_TIME                0x00000004
    #define CY_TIMESTAMP_TRIG_PARAM_TIME_LABEL          "Trigger Time"

    // The following is used to arm a trig with the current mask, counter and time values
    #define CY_TIMESTAMP_TRIG_PARAM_ARM                 0x00000005
    #define CY_TIMESTAMP_TRIG_PARAM_ARM_LABEL           "Trigger Arm"


// GPIO Control Bit Extension
/////////////////////////////////////////////////////////////////////////////

// Identifier of extension
#define CY_DEVICE_EXT_GPIO_CONTROL_BITS         0x00001005

    // This value is applied with CY_GPIO_CONTROL_BITS_WRITE is set
    #define CY_GPIO_CONTROL_BITS_SET                    0x00000000
    #define CY_GPIO_CONTROL_BITS_SET_LABEL              "Set Bits"

    // This value is applied with CY_GPIO_CONTROL_BITS_WRITE is set
    #define CY_GPIO_CONTROL_BITS_CLEAR                  0x00000001
    #define CY_GPIO_CONTROL_BITS_CLEAR_LABEL            "Clear Bits"

    #define CY_GPIO_CONTROL_BITS_BROADCAST              0x00000002
    #define CY_GPIO_CONTROL_BITS_BROADCAST_LABEL        "Broadcast"

    #define CY_GPIO_CONTROL_BITS_WRITE                  0x00000003
    #define CY_GPIO_CONTROL_BITS_WRITE_LABEL            "Write current values"

    // The following parameter is read-only
    #define CY_GPIO_CONTROL_BITS_CURRENT_VALUE          0x00000004
    #define CY_GPIO_CONTROL_BITS_CURRENT_VALUE_LABEL    "Current Control Bits Value"

    // The following parameter is read-only
    #define CY_GPIO_CONTROL_BITS_INPUTS_VALUE           0x00000005
    #define CY_GPIO_CONTROL_BITS_INPUTS_VALUE_LABEL     "Current GPIO Inputs Value"


// GPIO Interrupts
/////////////////////////////////////////////////////////////////////////////

// Identifier of extension
#define CY_DEVICE_EXT_GPIO_INTERRUPTS           0x00001006

    #define CY_DEVICE_GPIO_INTERRUPTS_Q15           0x00000000
    #define CY_DEVICE_GPIO_INTERRUPTS_Q15_LABEL     "Q15 Enabled"

    #define CY_DEVICE_GPIO_INTERRUPTS_Q3            0x00000001
    #define CY_DEVICE_GPIO_INTERRUPTS_Q3_LABEL      "Q3 Enabled"

    #define CY_DEVICE_GPIO_INTERRUPTS_Q7            0x00000002
    #define CY_DEVICE_GPIO_INTERRUPTS_Q7_LABEL      "Q7 Enabled"

    #define CY_DEVICE_GPIO_INTERRUPTS_Q10           0x00000003
    #define CY_DEVICE_GPIO_INTERRUPTS_Q10_LABEL     "Q10 Enabled"


// Flow Control Extension
/////////////////////////////////////////////////////////////////////////////

// Identifier of extension
#define CY_DEVICE_EXT_FLOW_CONTROL              0x00001007
    
    #define CY_DEVICE_FLOW_INTER_PACKET_DELAY       0x00000000
    #define CY_DEVICE_FLOW_INTER_PACKET_DELAY_LABEL "Inter Packet Delay"

    #define CY_DEVICE_FLOW_IPD_NANOSECONDS          0x00000001
    #define CY_DEVICE_FLOW_IPD_NANOSECONDS_LABEL    "Inter Packet Delay (ns)"

    // The following parameter are use to compute the inter-packet delay.
    #define CY_DEVICE_FLOW_IPD_DATA_RATE            0x00000002
    #define CY_DEVICE_FLOW_IPD_DATA_RATE_LABEL      "Expected Data Rate (bytes/s)"
    
    // The following parameter are use to compute the inter-packet delay.
    #define CY_DEVICE_FLOW_IPD_LINK_SPEED           0x00000003
    #define CY_DEVICE_FLOW_IPD_LINK_SPEED_LABEL     "Link Speed"

    // The following parameter is read-only and indicates the expected result
    // of changed CY_DEVICE_FLOW_IPD_DATA_RATE or CY_DEVICE_FLOW_IPD_LINK_SPEED
    #define CY_DEVICE_FLOW_IPD_CALCULATED           0x00000004
    #define CY_DEVICE_FLOW_IPD_CALCULATED_LABEL     "Resulting Inter-Packet Delay"


// Streaming Interface Selection Extension
/////////////////////////////////////////////////////////////////////////////

// Identifier of extension
#define CY_DEVICE_EXT_STREAMING_INT_SELECTION   0x00001008

    #define CY_DEVICE_STREAMING_INT_0               0x00000000
    #define CY_DEVICE_STREAMING_INT_0_LABEL         "Streaming Interface 0 Selection"


#endif // _CY_DEVICE_EXTENSION_CONSTANTS_H_


