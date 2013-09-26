//
//  port.h
//  rs-232
//
//  Created by Roman Lishtaba on 9/23/13.
//  Copyright (c) 2013 Roman Lishtaba. All rights reserved.
//

#ifndef rs_232_port_h____FILEEXTENSION___
#define rs_232_port_h____FILEEXTENSION___

#   include <ruby.h>
#   include <ruby/io.h>
#   include <windows.h>
#   include <fcntl.h>
#   include <io.h>
#   include <stdio.h>
#   include <string.h>
#   include "structs.h"

#define WIN_PATTERN "\\\\.\\%s"

void setBaudRate(VALUE, VALUE);

VALUE getBaudRate(VALUE);

void setParity(VALUE, VALUE);

VALUE getParity(VALUE);

void setDataBits(VALUE, VALUE);

VALUE getDataBits(VALUE);

void setStopBits(VALUE, VALUE);

VALUE getStopBits(VALUE);

void setFlowControl(VALUE, VALUE);

VALUE getFlowControl(VALUE);

void setTimeout(VALUE, VALUE);

void setSettings(VALUE);

#endif
