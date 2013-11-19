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
