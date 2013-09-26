//
//  initializer.c
//  rs-232
//
//  Created by Roman Lishtaba on 9/2/13.
//  Copyright (c) 2013 Roman Lishtaba. All rights reserved.
//

#include "initializer.h"

static void destructor(PortDescriptor *port)
{
    xfree(port);
}


static void markDescriptor(PortDescriptor *port)
{
}


static VALUE allocateStruct(VALUE self)
{
    PortDescriptor *port;

    rb_iv_set(self, "@port", Qnil);

    return Data_Make_Struct(self, PortDescriptor, markDescriptor, destructor, port);
}


void setBaudRate(VALUE self, VALUE int_baudRate)
{
    PortDescriptor *port;

    {
        Check_Type(int_baudRate, T_FIXNUM);
    }

    int baudRate = FIX2INT(int_baudRate);

    Data_Get_Struct(self, PortDescriptor, port);

    int baud = 110;

    switch (baudRate)
    {
        case BAUD110:
            baud = 110;
            break;
        case BAUD300:
            baud = 300;
            break;
        case BAUD1200:
            baud = 1200;
            break;
        case BAUD2400:
            baud = 2400;
            break;
        case BAUD4800:
            baud = 4800;
            break;
        case BAUD9600:
            baud = 9600;
            break;
        case BAUD38400:
            baud = 38400;
            break;
        case BAUD57600:
            baud = 57600;
            break;
        case BAUD115200:
            baud = 115200;
            break;
        case BAUD19200:
            baud = 19200;
            break;
        default:
            rb_raise(rb_eException, "BaudRate value does not match specification, current: %d", baudRate);
            break;
    }

    port->settings.BaudRate = (enum BaudRateType) baud;
    port->toBeUpdated |= T_BaudRate;

    updateSettings(port);
}


VALUE getBaudRate(VALUE self)
{
    PortDescriptor *port;

    Data_Get_Struct(self, PortDescriptor, port);

    return INT2FIX(port->settings.BaudRate);
}


void setParity(VALUE self, VALUE int_parity)
{

    {
        Check_Type(int_parity, T_FIXNUM);
    }

    int parity = FIX2INT(int_parity);

    PortDescriptor *port;

    Data_Get_Struct(self, PortDescriptor, port);

    enum ParityType parity_type = PAR_NONE;

    switch (parity)
    {
        case PAR_NONE:
            parity_type = PAR_NONE;
            break;
        case PAR_ODD:
            parity_type = PAR_ODD;
            break;
        case PAR_EVEN:
            parity_type = PAR_EVEN;
            break;
        default:
            rb_raise(rb_eException, "Parity value does not match specification, current: %d", parity);
            break;
    }

    port->settings.Parity = parity_type;
    port->toBeUpdated |= T_Parity;

    updateSettings(port);
}


VALUE getParity(VALUE self)
{

    PortDescriptor *port;

    Data_Get_Struct(self, PortDescriptor, port);

    return INT2FIX(port->settings.Parity);
}


void setDataBits(VALUE self, VALUE intDataBits)
{

    {
        Check_Type(intDataBits, T_FIXNUM);
    }

    int dataBits = FIX2INT(intDataBits);

    PortDescriptor *port;

    Data_Get_Struct(self, PortDescriptor, port);

    enum DataBitsType dataBitsType = DATA_8;

    switch (dataBits)
    {
        case DATA_5:
            dataBitsType = DATA_5;
            break;
        case DATA_6:
            dataBitsType = DATA_6;
            break;
        case DATA_7:
            dataBitsType = DATA_7;
            break;
        case DATA_8:
            dataBitsType = DATA_8;
            break;
        default:
            rb_raise(rb_eException, "DataBits value does not match specification, current: %d", dataBits);
            break;
    }

    port->settings.DataBits = dataBitsType;
    port->toBeUpdated |= T_DataBits;

    updateSettings(port);
}


VALUE getDataBits(VALUE self)
{

    PortDescriptor *port;

    Data_Get_Struct(self, PortDescriptor, port);

    return INT2FIX(port->settings.DataBits);
}


void setStopBits(VALUE self, VALUE intStopBits)
{

    {
        Check_Type(intStopBits, T_FIXNUM);
    }

    int stopBits = FIX2INT(intStopBits);

    PortDescriptor *port;

    Data_Get_Struct(self, PortDescriptor, port);

    enum StopBitsType stopBitsType = STOP_1;

    switch (stopBits)
    {
        case STOP_1:
            stopBitsType = STOP_1;
            break;
        case STOP_2:
            stopBitsType = STOP_2;
            break;
        default:
            rb_raise(rb_eException, "StopBits value does not match specification, current: %d", stopBits);
            break;
    }

    port->settings.StopBits = stopBitsType;
    port->toBeUpdated |= T_StopBits;

    updateSettings(port);
}


VALUE getStopBits(VALUE self)
{

    PortDescriptor *port;

    Data_Get_Struct(self, PortDescriptor, port);

    return INT2FIX(port->settings.StopBits);
}


void setFlowControl(VALUE self, VALUE intFlow)
{

    {
        Check_Type(intFlow, T_FIXNUM);
    }

    int flow = FIX2INT(intFlow);

    PortDescriptor *port;

    Data_Get_Struct(self, PortDescriptor, port);

    enum FlowType flowType = FLOW_OFF;

    switch (flow)
    {
        case FLOW_OFF:
            flowType = FLOW_OFF;
            break;
        case FLOW_HARDWARE:
            flowType = FLOW_HARDWARE;
            break;
        case FLOW_XONXOFF:
            flowType = FLOW_XONXOFF;
            break;
        default:
            rb_raise(rb_eException, "FlowControl value does not match specification, current: %d", flow);
            break;
    }

    port->settings.FlowControl = flowType;
    port->toBeUpdated |= T_StopBits;

    updateSettings(port);
}


VALUE getFlowControl(VALUE self)
{

    PortDescriptor *port;

    Data_Get_Struct(self, PortDescriptor, port);

    return INT2FIX(port->settings.FlowControl);
}


void setTimeout(VALUE self, VALUE rb_timeout)
{

    {
        Check_Type(rb_timeout, T_FIXNUM);
    }

    PortDescriptor *port;

    Data_Get_Struct(self, PortDescriptor, port);

    long timeout = FIX2LONG(rb_timeout);

    port->settings.Timeout_Millisec = timeout;
    port->toBeUpdated |= T_TimeOut;

    updateSettings(port);
}


VALUE getTimeout(VALUE self)
{

    PortDescriptor *port;

    Data_Get_Struct(self, PortDescriptor, port);

    return INT2FIX(port->settings.Timeout_Millisec);
}


VALUE readErrorNo(VALUE self)
{

    PortDescriptor *port;

    Data_Get_Struct(self, PortDescriptor, port);

    return LONG2FIX(port->error);
}


void setSettings(VALUE self)
{

    PortDescriptor *port;

    Data_Get_Struct(self, PortDescriptor, port);

    setBaudRate(self, INT2FIX(port->settings.BaudRate));
    setParity(self, INT2FIX(port->settings.Parity));
    setDataBits(self, INT2FIX(port->settings.DataBits));
    setStopBits(self, INT2FIX(port->settings.StopBits));
    setFlowControl(self, INT2FIX(port->settings.FlowControl));
    setTimeout(self, LONG2FIX(port->settings.Timeout_Millisec));

    port->toBeUpdated = T_ALL;

    updateSettings(port);
}


void Init_rs_232(void)
{


    VALUE root, rb_cPort;

    root = rb_define_module("CommPort");

    Constants_Init(root);

    rb_cPort = rb_define_class_under(root, "Rs232", rb_cObject);
    rb_define_alloc_func(rb_cPort, allocateStruct);
    rb_define_method(rb_cPort, "initialize", (VALUE ( *)()) initializeStruct, 1);

    rb_define_method(rb_cPort, "baud_rate=", (VALUE ( *)()) setBaudRate, 1);
    rb_define_method(rb_cPort, "baud_rate", (VALUE ( *)()) getBaudRate, 0);

    rb_define_method(rb_cPort, "parity=", (VALUE ( *)()) setParity, 1);
    rb_define_method(rb_cPort, "parity", (VALUE ( *)()) getParity, 0);

    rb_define_method(rb_cPort, "data_bits=", (VALUE ( *)()) setDataBits, 1);
    rb_define_method(rb_cPort, "data_bits", (VALUE ( *)()) getDataBits, 0);

    rb_define_method(rb_cPort, "stop_bits=", (VALUE ( *)()) setStopBits, 1);
    rb_define_method(rb_cPort, "stop_bits", (VALUE ( *)()) getStopBits, 0);

    rb_define_method(rb_cPort, "flow_control=", (VALUE ( *)()) setFlowControl, 1);
    rb_define_method(rb_cPort, "flow_control", (VALUE ( *)()) getFlowControl, 0);

    rb_define_method(rb_cPort, "timeout=", (VALUE ( *)()) setTimeout, 1);
    rb_define_method(rb_cPort, "timeout", (VALUE ( *)()) getTimeout, 0);

    rb_define_method(rb_cPort, "open", (VALUE ( *)()) openIO, 0);
    rb_define_method(rb_cPort, "close", (VALUE ( *)()) closeIO, 0);
    rb_define_method(rb_cPort, "flush", (VALUE ( *)()) flushIO, 0);
    rb_define_method(rb_cPort, "closed?", (VALUE ( *)()) isClosedIO, 0);


    rb_define_method(rb_cPort, "write", (VALUE ( *)()) writeIO, 1);
    rb_define_method(rb_cPort, "read", (VALUE ( *)()) readIO, 1);
    rb_define_method(rb_cPort, "available?", (VALUE ( *)()) bytesAvailableIO, 0);

    rb_define_method(rb_cPort, "line_status", (VALUE ( *)()) lineStatusIO, 0);
    rb_define_method(rb_cPort, "set_rts", (VALUE ( *)()) setRtsIO, 1);
    rb_define_method(rb_cPort, "set_dtr", (VALUE ( *)()) setDtrIO, 1);

    rb_define_method(rb_cPort, "read_error_no", (VALUE ( *)()) readErrorNo, 0);

}
