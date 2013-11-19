//
//  constants.c
//  rs-232
//
//  Created by Roman Lishtaba on 9/2/13.
//  Copyright (c) 2013 Roman Lishtaba. All rights reserved.


#include "constants.h"

void Constants_Init(VALUE root)
{
    rb_define_const(root, "VERSION", rb_str_new2(VERSION));

    rb_define_const(root, "BAUD_110", INT2FIX(BAUD110));
    rb_define_const(root, "BAUD_300", INT2FIX(BAUD300));
    rb_define_const(root, "BAUD_600", INT2FIX(BAUD600));
    rb_define_const(root, "BAUD_1200", INT2FIX(BAUD1200));
    rb_define_const(root, "BAUD_2400", INT2FIX(BAUD2400));
    rb_define_const(root, "BAUD_4800", INT2FIX(BAUD4800));
    rb_define_const(root, "BAUD_9600", INT2FIX(BAUD9600));
    rb_define_const(root, "BAUD_19200", INT2FIX(BAUD19200));
    rb_define_const(root, "BAUD_38400", INT2FIX(BAUD38400));
    rb_define_const(root, "BAUD_57600", INT2FIX(BAUD57600));
    rb_define_const(root, "BAUD_115200", INT2FIX(BAUD115200));

    rb_define_const(root, "DATA_BITS_5", INT2FIX(DATA_5));
    rb_define_const(root, "DATA_BITS_6", INT2FIX(DATA_6));
    rb_define_const(root, "DATA_BITS_7", INT2FIX(DATA_7));
    rb_define_const(root, "DATA_BITS_8", INT2FIX(DATA_8));

    rb_define_const(root, "PAR_NONE", INT2FIX(PAR_NONE));
    rb_define_const(root, "PAR_ODD", INT2FIX(PAR_ODD));
    rb_define_const(root, "PAR_EVEN", INT2FIX(PAR_EVEN));

    rb_define_const(root, "STOP_BITS_1", INT2FIX(STOP_1));
    rb_define_const(root, "STOP_BITS_3", INT2FIX(STOP_2));


    rb_define_const(root, "FLOW_OFF", INT2FIX(FLOW_OFF));
    rb_define_const(root, "FLOW_HARDWARE", INT2FIX(FLOW_HARDWARE));
    rb_define_const(root, "FLOW_XONXOFF", INT2FIX(FLOW_XONXOFF));

}