//
//  constants.h
//  rs-232
//
//  Created by Roman Lishtaba on 09/02/13.
//  Copyright (c) 2013 Roman Lishtaba. All rights reserved.
//

#ifndef constants____FILEEXTENSION___
#define constants____FILEEXTENSION___

#include <ruby.h>


#define VERSION "3.0.0"


#define LS_CTS  0x01
#define LS_DSR  0x02
#define LS_DCD  0x04
#define LS_RI   0x08
#define LS_RTS  0x10
#define LS_DTR  0x20
#define LS_ST   0x40
#define LS_SR   0x80


// TODO: not implemented yet
enum CommErrorNo {
    E_NO_ERROR,
    E_INVALID_FD,
    E_NO_MEMORY,
    E_CAUGHT_NON_BLOCKED_SIGNAL,
    E_PORT_TIMEOUT,
    E_INVALID_DEVICE,
    E_BREAK_CONDITION,
    E_FRAMING_ERROR,
    E_IO_ERROR,
    E_BUFFER_OVERRUN,
    E_RECEIVE_OVERFLOW,
    E_RECEIVE_PARITY_ERROR,
    E_TRANSMIT_OVERFLOW,
    E_READ_FAILED,
    E_WRITE_FAILED,
    E_FILE_NOT_FOUND,
    E_PERMISSION_DENIED,
    E_AGAIN
};


enum BaudRateType
{

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)

    BAUD14400 = 14400,
    BAUD56000 = 56000,
    BAUD128000 = 128000,
    BAUD256000 = 256000,

#endif

    BAUD110    = 110,
    BAUD300    = 300,
    BAUD600    = 600,
    BAUD1200   = 1200,
    BAUD2400   = 2400,
    BAUD4800   = 4800,
    BAUD9600   = 9600,
    BAUD19200  = 19200,
    BAUD38400  = 38400,
    BAUD57600  = 57600,
    BAUD115200 = 115200

};


enum DataBitsType
{
    DATA_5 = 5,
    DATA_6 = 6,
    DATA_7 = 7,
    DATA_8 = 8
};


enum ParityType
{
    PAR_NONE,
    PAR_ODD,
    PAR_EVEN,
};


enum StopBitsType
{
    STOP_1,
#   if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
    STOP_1_5,
#   endif
    STOP_2
};


enum FlowType
{
    FLOW_OFF,
    FLOW_HARDWARE,
    FLOW_XONXOFF
};


enum SettingsFlags
{
    T_BaudRate     = 0x0001,
    T_Parity       = 0x0002,
    T_StopBits     = 0x0004,
    T_DataBits     = 0x0008,
    T_Flow         = 0x0010,
    T_TimeOut      = 0x0100,
    T_ALL          = 0x0fff,
    T_SettingsDone = 0x00ff,
};


void Constants_Init(VALUE);

#endif
