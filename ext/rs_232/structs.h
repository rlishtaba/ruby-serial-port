/*
 * Copyright (c) 2013, Ingenico Inc.
 *
 * Permission to use, copy, modify, and/or distribute this software for any purpose with or without fee is hereby granted,
 * provided that the above copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES WITH REGARD TO THIS SOFTWARE INCLUDING ALL
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY SPECIAL, DIRECT,
 * INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER
 * IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR
 * PERFORMANCE OF THIS SOFTWARE.
 *
**/

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
