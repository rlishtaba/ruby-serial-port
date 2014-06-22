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

#ifndef constants____FILEEXTENSION___
#define constants____FILEEXTENSION___

#include <ruby.h>


#define LS_CTS  0x01
#define LS_DSR  0x02
#define LS_DCD  0x04
#define LS_RI   0x08
#define LS_RTS  0x10
#define LS_DTR  0x20
#define LS_ST   0x40
#define LS_SR   0x80


enum BaudRateType
{
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
    DATA_6,
    DATA_7,
    DATA_8
};


enum ParityType
{
    PAR_NONE,
    PAR_ODD,
    PAR_EVEN,
};


enum StopBitsType
{
    STOP_1 = 1,
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
