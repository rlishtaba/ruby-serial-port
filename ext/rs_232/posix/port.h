//
//  port.h.h
//  rs-232
//
//  Created by Roman Lishtaba on 9/23/13.
//  Copyright (c) 2013 Roman Lishtaba. All rights reserved.
//

#ifndef rs_232_port_h____FILEEXTENSION___
#define rs_232_port_h____FILEEXTENSION___

#   include <ruby.h>
#   include <stdio.h>
#   include <string.h>
#   include <unistd.h>
#   include <fcntl.h>
#   include <errno.h>
#   include <termios.h>
#   include <sys/ioctl.h>
#   include "structs.h"


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
