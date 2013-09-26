//
//  shared.h
//  rs-232
//
//  Created by Roman Lishtaba on 9/20/13.
//  Copyright (c) 2013 Roman Lishtaba. All rights reserved.
//

#ifndef rs_232_initializer____FILEEXTENSION___
#define rs_232_initializer____FILEEXTENSION___

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)

#   include "windows/port.h"

#else

#   include "posix/port.h"

#endif

#include "structs.h"

VALUE initializeStruct(VALUE, VALUE);

void updateSettings(PortDescriptor *port);

VALUE isClosedIO(VALUE);

VALUE openIO(VALUE);

VALUE closeIO(VALUE);

VALUE bytesAvailableIO(VALUE);

VALUE flushIO(VALUE);

VALUE writeIO(VALUE, VALUE);

VALUE readIO(VALUE, VALUE);

VALUE lineStatusIO(VALUE);

VALUE setRtsIO(VALUE, VALUE);

VALUE setDtrIO(VALUE, VALUE);

VALUE readErrorNo(VALUE);

#endif