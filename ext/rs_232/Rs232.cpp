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
 */

/*
 * @author Roman Lishtaba
 */

#include "Rs232.h"

static void destructor(PortDescriptor *port)
{
    xfree(port);
}

static void markDescriptor(PortDescriptor *port)
{
    //noop
}


static VALUE allocateStruct(VALUE self)
{
    PortDescriptor *port = NULL;
    rb_iv_set(self, "@port", Qnil);
    
    return Data_Make_Struct(self, PortDescriptor, markDescriptor, destructor, port);
}


void setBaudRate(VALUE self, VALUE int_baudRate)
{
    Check_Type(int_baudRate, T_FIXNUM);
    
    PortDescriptor *port;
    int baudRate = FIX2INT(int_baudRate);
    int baud = 110;
    
    Data_Get_Struct(self, PortDescriptor, port);
    
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
    Check_Type(int_parity, T_FIXNUM);
    
    PortDescriptor *port;
    Data_Get_Struct(self, PortDescriptor, port);
    int parity = FIX2INT(int_parity);
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
    Check_Type(intDataBits, T_FIXNUM);
    PortDescriptor *port;
    Data_Get_Struct(self, PortDescriptor, port);
    int dataBits = FIX2INT(intDataBits);
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
    Check_Type(intStopBits, T_FIXNUM);
    
    PortDescriptor *port;
    Data_Get_Struct(self, PortDescriptor, port);
    int stopBits = FIX2INT(intStopBits);
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
    Check_Type(intFlow, T_FIXNUM);
    PortDescriptor *port;
    Data_Get_Struct(self, PortDescriptor, port);
    int flow = FIX2INT(intFlow);
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
    Check_Type(rb_timeout, T_FIXNUM);
    PortDescriptor *port;
    Data_Get_Struct(self, PortDescriptor, port);
    long timeout = FIX2LONG(rb_timeout);
    
    port->settings.Timeout_Millisec = timeout;
    port->toBeUpdated |= T_TimeOut;
    
    updateSettings(port);
}

/*
 * Get connection timeout
 *
 * @return [Fixnum] the timeout value
 * @see Impl#timeout
 */
VALUE getTimeout(VALUE self)
{
    PortDescriptor *port;
    Data_Get_Struct(self, PortDescriptor, port);
    
    return INT2FIX(port->settings.Timeout_Millisec);
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

extern "C" void Init_rs_232_native(void)
{
    const char rootModName[] = "Rs232";
    const char implClassName[] = "Native";
    const char constantsModName[] = "Constants";
    const char VERSION[] = "2.0.0";
    
    // define root Rs232 module
    const VALUE root = rb_define_module(rootModName);
    
    // define impl ruby class
    const VALUE impl = rb_define_class_under(root, implClassName, rb_cObject);
    
    // define module Constants under Native
    const VALUE constants = rb_define_module_under(root, constantsModName);
    
    // initialize constants in to module Native::Constants
    Constants_Init(constants);
    
    // define native version constant
    rb_define_const(impl, "NATIVE_VERSION", rb_str_new2(VERSION));
    
    rb_define_alloc_func(impl, allocateStruct);
    
    rb_define_method(impl, "initialize", RUBY_METHOD_FUNC(initializeStruct), 1);
    
    rb_define_method(impl, "baud_rate=", RUBY_METHOD_FUNC(setBaudRate), 1);
    rb_define_method(impl, "baud_rate", RUBY_METHOD_FUNC(getBaudRate), 0);
    
    rb_define_method(impl, "parity=", RUBY_METHOD_FUNC(setParity), 1);
    rb_define_method(impl, "parity", RUBY_METHOD_FUNC(getParity), 0);
    
    rb_define_method(impl, "data_bits=", RUBY_METHOD_FUNC(setDataBits), 1);
    rb_define_method(impl, "data_bits", RUBY_METHOD_FUNC(getDataBits), 0);
    
    rb_define_method(impl, "stop_bits=", RUBY_METHOD_FUNC(setStopBits), 1);
    rb_define_method(impl, "stop_bits", RUBY_METHOD_FUNC(getStopBits), 0);
    
    rb_define_method(impl, "flow_control=", RUBY_METHOD_FUNC(setFlowControl), 1);
    rb_define_method(impl, "flow_control", RUBY_METHOD_FUNC(getFlowControl), 0);
    
    rb_define_method(impl, "timeout=", RUBY_METHOD_FUNC(setTimeout), 1);
    rb_define_method(impl, "timeout", RUBY_METHOD_FUNC(getTimeout), 0);
    
    rb_define_method(impl, "open", RUBY_METHOD_FUNC(openIO), 0);
    rb_define_method(impl, "close", RUBY_METHOD_FUNC(closeIO), 0);
    rb_define_method(impl, "flush", RUBY_METHOD_FUNC(flushIO), 0);
    rb_define_method(impl, "open?", RUBY_METHOD_FUNC(isOpenIO), 0);
    
    rb_define_method(impl, "write", RUBY_METHOD_FUNC(writeIO), 1);
    rb_define_method(impl, "read", RUBY_METHOD_FUNC(readIO), 1);
    rb_define_method(impl, "available?", RUBY_METHOD_FUNC(bytesAvailableIO), 0);
    
    rb_define_method(impl, "line_status", RUBY_METHOD_FUNC(lineStatusIO), 0);
    rb_define_method(impl, "set_rts", RUBY_METHOD_FUNC(setRtsIO), 1);
    rb_define_method(impl, "set_dtr", RUBY_METHOD_FUNC(setDtrIO), 1);
}
