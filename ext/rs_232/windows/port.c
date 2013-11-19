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

#include "port.h"

VALUE setDtrIO(VALUE self, VALUE rb_int)
{
    {
        Check_Type(rb_int, T_FIXNUM);
    }

    int boolean = FIX2INT(rb_int);

    PortDescriptor *port;

    Data_Get_Struct(self, PortDescriptor, port);

    return INT2FIX( EscapeCommFunction(port->fd, boolean == 1 ? SETDTR : CLRDTR) );
}


VALUE setRtsIO(VALUE self, VALUE rb_int)
{
    {
        Check_Type(rb_int, T_FIXNUM);
    }

    int boolean = FIX2INT(rb_int);

    PortDescriptor *port;

    Data_Get_Struct(self, PortDescriptor, port);

    return INT2FIX( EscapeCommFunction(port->fd, boolean == 1 ? SETRTS : CLRRTS) );
}


VALUE lineStatusIO(VALUE self)
{

    PortDescriptor *port;

    Data_Get_Struct(self, PortDescriptor, port);

    unsigned long Status = 0, Temp = 0;

    GetCommModemStatus(port->fd, &Temp);

    if (Temp & MS_CTS_ON) Status |= LS_CTS;
    if (Temp & MS_DSR_ON) Status |= LS_DSR;
    if (Temp & MS_RING_ON) Status |= LS_RI;
    if (Temp & MS_RLSD_ON) Status |= LS_DCD;

    return LONG2FIX(Status);
}


static void platformInitIO(PortDescriptor *port)
{
    port->fd     = INVALID_HANDLE_VALUE;
    port->status = 1;
    port->error = E_NO_ERROR;
}


void updateSettings(PortDescriptor *port)
{

    if (port->status != 0)
        rb_raise(rb_eException, "Can not set due to comport is not open, status: %d\n", port->status);


    if (port->toBeUpdated & T_BaudRate)
        port->commConfig.dcb.BaudRate = port->settings.BaudRate;


    if (port->toBeUpdated & T_Parity)
    {
        port->commConfig.dcb.Parity  = (BYTE) port->settings.Parity;
        port->commConfig.dcb.fParity = (port->settings.Parity == PAR_NONE) ? 0 : 1;
    }


    if (port->toBeUpdated & T_DataBits)
    {
        port->commConfig.dcb.ByteSize = (BYTE) port->settings.DataBits;
    }


    if (port->toBeUpdated & T_StopBits)
    {
        switch (port->settings.StopBits)
        {
            case STOP_1:
                port->commConfig.dcb.StopBits = ONESTOPBIT;
                break;
            case STOP_2:
                port->commConfig.dcb.StopBits = TWOSTOPBITS;
                break;
        }
    }

    if (port->toBeUpdated & T_Flow)
    {
        switch (port->settings.FlowControl)
        {
            case FLOW_OFF:
                port->commConfig.dcb.fOutxCtsFlow = 0;
                port->commConfig.dcb.fRtsControl  = RTS_CONTROL_DISABLE;
                port->commConfig.dcb.fInX         = 0;
                port->commConfig.dcb.fOutX        = 0;
                break;
            case FLOW_XONXOFF:
                port->commConfig.dcb.fOutxCtsFlow = 0;
                port->commConfig.dcb.fRtsControl  = RTS_CONTROL_DISABLE;
                port->commConfig.dcb.fInX         = 1;
                port->commConfig.dcb.fOutX        = 1;
                break;
            case FLOW_HARDWARE:
                port->commConfig.dcb.fOutxCtsFlow = 1;
                port->commConfig.dcb.fRtsControl  = RTS_CONTROL_HANDSHAKE;
                port->commConfig.dcb.fInX         = 0;
                port->commConfig.dcb.fOutX        = 0;
                break;
        }
    }

    if (port->toBeUpdated & T_TimeOut)
    {
        int millisec                             = port->settings.Timeout_Millisec;

        if (millisec == -1)
        {
            port->commTimeouts.ReadIntervalTimeout      = MAXDWORD;
            port->commTimeouts.ReadTotalTimeoutConstant = 0;
        } else
        {
            port->commTimeouts.ReadIntervalTimeout      = MAXDWORD;
            port->commTimeouts.ReadTotalTimeoutConstant = millisec;
        }
        port->commTimeouts.ReadTotalTimeoutMultiplier  = 0;
        port->commTimeouts.WriteTotalTimeoutMultiplier = millisec;
        port->commTimeouts.WriteTotalTimeoutConstant   = 0;
    }


    if (port->toBeUpdated & T_SettingsDone)
        SetCommConfig(port->fd, &port->commConfig, sizeof(COMMCONFIG));

    if ((port->toBeUpdated & T_TimeOut))
        SetCommTimeouts(port->fd, &port->commTimeouts);

    port->toBeUpdated = 0;
}


static int queryStatusIO(VALUE self)
{
    PortDescriptor *port;

    Data_Get_Struct(self, PortDescriptor, port);

    return port->status;
}


VALUE isClosedIO(VALUE self)
{
    return queryStatusIO(self) != 0 ? Qtrue : Qfalse;
}


VALUE flushIO(VALUE self)
{
    PortDescriptor *port;

    Data_Get_Struct(self, PortDescriptor, port);

    return (INT2FIX(FlushFileBuffers(port->fd)));
}


VALUE bytesAvailableIO(VALUE self)
{
    PortDescriptor *port;

    Data_Get_Struct(self, PortDescriptor, port);

    DWORD   Errors;
    COMSTAT Status;
    if (ClearCommError(port->fd, &Errors, &Status))
    {
        return INT2FIX(Status.cbInQue);
    }
    return INT2FIX(0);
}


VALUE openIO(VALUE self)
{

    PortDescriptor *port;

    Data_Get_Struct(self, PortDescriptor, port);

    if (port->status == 0)
        return INT2FIX(port->status);

    DWORD conf_length = sizeof(COMMCONFIG);
    port->commConfig.dwSize = conf_length;
    DWORD threading = 0;

    port->fd = CreateFileA(port->settings.ComPort,
            GENERIC_READ | GENERIC_WRITE,
            0,
            NULL,
            OPEN_EXISTING,
            threading,
            NULL);

    if (port->fd == INVALID_HANDLE_VALUE)
    {

        port->status = 1;
        port->error = E_FILE_NOT_FOUND;
        rb_raise(rb_eException, "Unable to open comport: %s\n", port->settings.ComPort);

    } else
    {

        port->status = 0;
        rb_iv_set(self, "@open", INT2FIX(port->status));

        GetCommConfig(port->fd, &port->commConfig, &conf_length);
        GetCommState(port->fd, &(port->commConfig.dcb));

        port->commConfig.dcb.fBinary       = 1;
        port->commConfig.dcb.fInX          = 0;
        port->commConfig.dcb.fOutX         = 0;
        port->commConfig.dcb.fAbortOnError = 0;
        port->commConfig.dcb.fNull         = 0;

        port->commConfig.dcb.fDtrControl = 1;

        port->toBeUpdated = T_ALL;

        setSettings(self);

    }

    return INT2FIX(port->status);
}


VALUE writeIO(VALUE self, VALUE message)
{

    int recv;
    int len;
    PortDescriptor *port;

    Data_Get_Struct(self, PortDescriptor, port);

    Check_Type(message, T_STRING);

    len = RSTRING_LEN(message);
    char cStr[len];
    strcpy(cStr, RSTRING_PTR(message));

    if (!WriteFile(port->fd, cStr, len, (LPDWORD)((void *) &recv), NULL))
    {
        port->error = E_WRITE_FAILED;
        rb_raise(rb_eIOError, "IO: writing of the %d bytes has been failed", len);
    }

    return (INT2FIX(recv));

}


VALUE readIO(VALUE self, VALUE rb_int)
{

    {
        Check_Type(rb_int, T_FIXNUM);
    }

    PortDescriptor *port;

    Data_Get_Struct(self, PortDescriptor, port);

    int n;
    int len = FIX2INT(rb_int);
    char buf[len];

    ReadFile(port->fd, &buf, len, (LPDWORD)((void *) &n), NULL);

    if (n > 0)
    {
        int i;
        char *reply[n];
        for (i = 0; i < n; i++)
            reply[i] = &buf[i];

        return rb_str_new(*reply, n);
    }

    return Qnil;
}


VALUE closeIO(VALUE self)
{

    PortDescriptor *port;

    Data_Get_Struct(self, PortDescriptor, port);

    flushIO(self);
    port->status = CloseHandle(port->fd);
    port->fd     = INVALID_HANDLE_VALUE;

    rb_iv_set(self, "@open", INT2FIX(port->status));

    return INT2FIX(port->status);

}


VALUE initializeStruct(VALUE self, VALUE portName)
{

    {
        Check_Type(portName, T_STRING);
    }

    PortDescriptor *port;

    Data_Get_Struct(self, PortDescriptor, port);

    port->settings.BaudRate         = BAUD115200;
    port->settings.Parity           = PAR_NONE;
    port->settings.FlowControl      = FLOW_OFF;
    port->settings.DataBits         = DATA_8;
    port->settings.StopBits         = STOP_1;
    port->settings.Timeout_Millisec = 0;

    snprintf(port->settings.ComPort, sizeof(port->settings.ComPort) - 1, WIN_PATTERN, RSTRING_PTR(portName));

    platformInitIO(port);

    rb_iv_set(self, "@port", portName);

    return self;
}

