//
//  structs.h
//  rs-232
//
//  Created by Roman Lishtaba on 9/2/13.
//  Copyright (c) 2013 Roman Lishtaba. All rights reserved.
//


#ifndef rs_232_structs_h
#define rs_232_structs_h

#include "constants.h"

/*
 * structure to contain port settings
 */

typedef struct PortSettings_T
{
    char              ComPort[40];
    enum BaudRateType BaudRate;
    enum DataBitsType DataBits;
    enum ParityType   Parity;
    enum StopBitsType StopBits;
    enum FlowType     FlowControl;
    long              Timeout_Millisec;
} PortSettings;


/*
 * port descriptor structure
 */

typedef struct portDescriptor_T
{
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)

    HANDLE       fd;
    COMMCONFIG   commConfig;
    COMMTIMEOUTS commTimeouts;

#else

    int            fd;
    struct termios posixConfig;
    struct termios previousPosixConfig;

#endif

    int          status;
    PortSettings settings;
    int          toBeUpdated;
    enum         CommErrorNo error;

} PortDescriptor;

#endif
