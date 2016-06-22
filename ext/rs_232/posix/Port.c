/*
 * Copyright (c) 2013, Roman Lishtaba.
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

/*
 * @author Roman Lishtaba
 */

#include "Port.h"


VALUE setDtrIO(VALUE self, VALUE rb_int)
{
    Check_Type(rb_int, T_FIXNUM);
    const int boolean = FIX2INT(rb_int);
    int status;
    PortDescriptor *port = NULL;
    Data_Get_Struct(self, PortDescriptor, port);
    
    ioctl(port->fd, TIOCMGET, &status);
    if (boolean == 1)
        status |= TIOCM_DTR;
    else
        status &= ~TIOCM_DTR;
    ioctl(port->fd, TIOCMSET, &status);
    
    return INT2FIX(status);
}


VALUE setRtsIO(VALUE self, VALUE rb_int)
{
    Check_Type(rb_int, T_FIXNUM);
    const int boolean = FIX2INT(rb_int);
    PortDescriptor *port = NULL;
    Data_Get_Struct(self, PortDescriptor, port);
    int status;
    
    ioctl(port->fd, TIOCMGET, &status);
    if (boolean == 1)
        status |= TIOCM_RTS;
    else
        status &= ~TIOCM_RTS;
    ioctl(port->fd, TIOCMSET, &status);
    
    return INT2FIX(status);
}


VALUE lineStatusIO(VALUE self)
{
    PortDescriptor *port = NULL;
    Data_Get_Struct(self, PortDescriptor, port);
    unsigned long Status = 0, Temp = 0;
    
    ioctl(port->fd, TIOCMGET, &Temp);
    if (Temp & TIOCM_CTS) Status |= LS_CTS;
    if (Temp & TIOCM_DSR) Status |= LS_DSR;
    if (Temp & TIOCM_RI ) Status |= LS_RI;
    if (Temp & TIOCM_CD ) Status |= LS_DCD;
    if (Temp & TIOCM_DTR) Status |= LS_DTR;
    if (Temp & TIOCM_RTS) Status |= LS_RTS;
    if (Temp & TIOCM_ST ) Status |= LS_ST;
    if (Temp & TIOCM_SR ) Status |= LS_SR;
    
    return LONG2FIX(Status);
}


static void platformInitIO(PortDescriptor *port)
{
    port->fd     = -1;
    port->status = PORT_CLOSED;
}


static void setPosixBaudRate(PortDescriptor *port)
{
#ifdef CBAUD
    port->posixConfig.c_cflag &= (~CBAUD);
    port->posixConfig.c_cflag |= port->settings.BaudRate;
#else
    cfsetispeed(&port->posixConfig, port->settings.BaudRate);
    cfsetospeed(&port->posixConfig, port->settings.BaudRate);
#endif
}


void updateSettings(PortDescriptor *port)
{
    if (PORT_OPEN != port->status)
        rb_raise(rb_eException, "Can not set due to comport is not open, status: %d\n", port->status);
    
    /*
     * BaudRate clause
     */
    if (port->toBeUpdated & T_BaudRate)
        setPosixBaudRate(port);
    
    /*
     * Parity clause
     */
    if (port->toBeUpdated & T_Parity)
    {
        switch (port->settings.Parity)
        {
            case PAR_NONE:
                port->posixConfig.c_cflag &= (~PARENB);
                break;
            case PAR_EVEN:
                port->posixConfig.c_cflag &= (~PARODD);
                port->posixConfig.c_cflag |= PARENB;
                break;
            case PAR_ODD:
                port->posixConfig.c_cflag |= (PARENB| PARODD);
                break;
        }
    }
    
    /*
     * Data Bits clause
     */
    if (port->toBeUpdated & T_DataBits)
    {
        port->posixConfig.c_cflag &= (~CSIZE);
        switch (port->settings.DataBits)
        {
            case DATA_5:
                port->posixConfig.c_cflag |= CS5;
                break;
            case DATA_6:
                port->posixConfig.c_cflag |= CS6;
                break;
            case DATA_7:
                port->posixConfig.c_cflag |= CS7;
                break;
            case DATA_8:
                port->posixConfig.c_cflag |= CS8;
                break;
        }
    }
    
    /*
     * StopBits clause
     */
    
    if (port->toBeUpdated & T_StopBits)
    {
        switch (port->settings.StopBits)
        {
            case STOP_1:
                port->posixConfig.c_cflag &= (~CSTOPB);
                break;
            case STOP_2:
                port->posixConfig.c_cflag |= CSTOPB;
                break;
        }
    }
    
    /*
     * FlowControl clause
     */
    
    if (port->toBeUpdated & T_Flow)
    {
        switch (port->settings.FlowControl)
        {
            case FLOW_OFF:
                port->posixConfig.c_cflag &= (~CRTSCTS);
                port->posixConfig.c_iflag &= (~(IXON| IXOFF| IXANY));
                break;
            case FLOW_XONXOFF:
                /*software (XON/XOFF) flow control*/
                port->posixConfig.c_cflag &= (~CRTSCTS);
                port->posixConfig.c_iflag |= (IXON| IXOFF| IXANY);
                break;
            case FLOW_HARDWARE:
                port->posixConfig.c_cflag |= CRTSCTS;
                port->posixConfig.c_iflag &= (~(IXON| IXOFF| IXANY));
                break;
        }
    }
    
    
    /*
     * In case of update flush IO
     */
    
    if (port->toBeUpdated & T_SettingsDone)
    {
        tcsetattr(port->fd, TCSAFLUSH, &port->posixConfig);
    }
    
    /*
     * Timeout clause
     */
    
    if (port->toBeUpdated & T_TimeOut)
    {
        int timeout = port->settings.Timeout_Millisec;
        
        if (timeout == -1)
        {
            fcntl(port->fd, F_SETFL, O_NDELAY); /* O_NDELAY should release if no any data here */
        }
        else
        {
            fcntl(port->fd, F_SETFL, O_SYNC); /* O_SYNC should enable blocking function */
        }
        tcgetattr(port->fd, &port->posixConfig);
        port->posixConfig.c_cc[VTIME] = (timeout / 100);
        
        tcsetattr(port->fd, TCSAFLUSH, &port->posixConfig);
    }
    
    port->toBeUpdated = 0;
}


int queryStatusIO(VALUE self)
{
    PortDescriptor *port = NULL;
    Data_Get_Struct(self, PortDescriptor, port);
    
    return port->status;
}


VALUE isOpenIO(VALUE self)
{
    return queryStatusIO(self) == PORT_OPEN ? Qtrue : Qfalse;
}


VALUE flushIO(VALUE self)
{
    PortDescriptor *port = NULL;
    Data_Get_Struct(self, PortDescriptor, port);
    
    return INT2FIX( tcdrain(port->fd) );
}


VALUE bytesAvailableIO(VALUE self)
{
    PortDescriptor *port = NULL;
    Data_Get_Struct(self, PortDescriptor, port);
    int bytesQueued;
    
    if (ioctl(port->fd, FIONREAD, &bytesQueued) == -1)
        return INT2FIX(0);
    
    return INT2FIX(bytesQueued);
}


VALUE openIO(VALUE self)
{
    PortDescriptor *port = NULL;
    Data_Get_Struct(self, PortDescriptor, port);
    
    if ((port->fd = open(port->settings.ComPort, O_RDWR | O_NOCTTY | O_NDELAY)) != -1)
    {
        port->status = PORT_OPEN;
        rb_iv_set(self, "@open", INT2FIX(port->status));
        
        tcgetattr(port->fd, &port->previousPosixConfig);
        port->posixConfig = port->previousPosixConfig;
        cfmakeraw(&port->posixConfig);
        
        port->posixConfig.c_cflag |= CREAD | CLOCAL;
        port->posixConfig.c_lflag &= (~(ICANON| ECHO| ECHOE| ECHOK| ECHONL| ISIG));
        port->posixConfig.c_iflag &= (~(INPCK| IGNPAR| PARMRK| ISTRIP| ICRNL| IXANY));
        port->posixConfig.c_oflag &= (~OPOST);
        port->posixConfig.c_cc[VMIN]  = 0;
        port->posixConfig.c_cc[VTIME] = 0;
        
        port->toBeUpdated = T_ALL;
        
        setSettings(self);
    } else
    {
        port->status = PORT_CLOSED;
        rb_raise(rb_eRuntimeError, "Unable to open comport: `%s`", port->settings.ComPort);
    }
    
    return self;
}


VALUE writeIO(VALUE self, VALUE message)
{
    Check_Type(message, T_STRING);
    PortDescriptor *port = NULL;
    Data_Get_Struct(self, PortDescriptor, port);
    
    const int len = (int) RSTRING_LEN(message);
    char cStr[len];
    strcpy(cStr, RSTRING_PTR(message));
    
    const int recv = (int) write(port->fd, cStr, (size_t) sizeof(cStr));
    
    if (recv < 0)
        rb_raise(rb_eEOFError, "TX: writing of the %d bytes has failed", len);
    
    return INT2FIX(recv);
}


VALUE readIO(VALUE self, VALUE rb_int)
{
    Check_Type(rb_int, T_FIXNUM);
    int recv;
    PortDescriptor *port = NULL;
    Data_Get_Struct(self, PortDescriptor, port);
    const int len = FIX2INT(rb_int);
    char in[len];
    
    recv = (int) read(port->fd, in, sizeof(in));
    if (recv > 0)
        return rb_str_new(in, recv);
    
    return Qnil;
}


VALUE closeIO(VALUE self)
{
    PortDescriptor *port = NULL;
    Data_Get_Struct(self, PortDescriptor, port);
    flushIO(self);
    tcsetattr(port->fd, TCSAFLUSH | TCSANOW, &port->previousPosixConfig);
    
    const int state = close(port->fd);
    
    port->status = (state == 0 ? PORT_CLOSED : PORT_OPEN);
    
    rb_iv_set(self, "@open", INT2FIX(port->status));
    rb_iv_set(self, "@fd", INT2FIX(port->fd));
    
    return INT2FIX(state);
}


VALUE initializeStruct(VALUE self, VALUE portName)
{
    Check_Type(portName, T_STRING);
    PortDescriptor *port = NULL;
    Data_Get_Struct(self, PortDescriptor, port);
    
    port->settings.BaudRate         = BAUD115200;
    port->settings.Parity           = PAR_NONE;
    port->settings.FlowControl      = FLOW_OFF;
    port->settings.DataBits         = DATA_8;
    port->settings.StopBits         = STOP_1;
    port->settings.Timeout_Millisec = 0;
    
    strcpy(port->settings.ComPort, RSTRING_PTR(portName));
    platformInitIO(port);
    rb_iv_set(self, "@port", portName);
    
    return self;
}
