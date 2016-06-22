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

#include "Constants.h"

void Constants_Init(VALUE namespace)
{
    rb_define_const(namespace, "BAUD_110", INT2FIX(BAUD110));
    rb_define_const(namespace, "BAUD_300", INT2FIX(BAUD300));
    rb_define_const(namespace, "BAUD_600", INT2FIX(BAUD600));
    rb_define_const(namespace, "BAUD_1200", INT2FIX(BAUD1200));
    rb_define_const(namespace, "BAUD_2400", INT2FIX(BAUD2400));
    rb_define_const(namespace, "BAUD_4800", INT2FIX(BAUD4800));
    rb_define_const(namespace, "BAUD_9600", INT2FIX(BAUD9600));
    rb_define_const(namespace, "BAUD_19200", INT2FIX(BAUD19200));
    rb_define_const(namespace, "BAUD_38400", INT2FIX(BAUD38400));
    rb_define_const(namespace, "BAUD_57600", INT2FIX(BAUD57600));
    rb_define_const(namespace, "BAUD_115200", INT2FIX(BAUD115200));
    
    rb_define_const(namespace, "DATA_BITS_5", INT2FIX(DATA_5));
    rb_define_const(namespace, "DATA_BITS_6", INT2FIX(DATA_6));
    rb_define_const(namespace, "DATA_BITS_7", INT2FIX(DATA_7));
    rb_define_const(namespace, "DATA_BITS_8", INT2FIX(DATA_8));
    
    rb_define_const(namespace, "PAR_NONE", INT2FIX(PAR_NONE));
    rb_define_const(namespace, "PAR_ODD", INT2FIX(PAR_ODD));
    rb_define_const(namespace, "PAR_EVEN", INT2FIX(PAR_EVEN));
    
    rb_define_const(namespace, "STOP_BITS_1", INT2FIX(STOP_1));
    rb_define_const(namespace, "STOP_BITS_3", INT2FIX(STOP_2));
    
    rb_define_const(namespace, "FLOW_OFF", INT2FIX(FLOW_OFF));
    rb_define_const(namespace, "FLOW_HARDWARE", INT2FIX(FLOW_HARDWARE));
    rb_define_const(namespace, "FLOW_XONXOFF", INT2FIX(FLOW_XONXOFF));
}
