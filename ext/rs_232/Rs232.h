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

#pragma once

#ifdef __cplusplus
extern "C" {
#endif
    
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
    
#   include "windows/Port.h"
    
#else
    
#   include "posix/Port.h"
    
#endif
    
#include "Structs.h"
    
    VALUE initializeStruct(VALUE, VALUE);
    
    void updateSettings(PortDescriptor *port);
    
    VALUE isOpenIO(VALUE);
    
    VALUE openIO(VALUE);
    
    VALUE closeIO(VALUE);
    
    VALUE bytesAvailableIO(VALUE);
    
    VALUE flushIO(VALUE);
    
    VALUE writeIO(VALUE, VALUE);
    
    VALUE readIO(VALUE, VALUE);
    
    VALUE lineStatusIO(VALUE);
    
    VALUE setRtsIO(VALUE, VALUE);
    
    VALUE setDtrIO(VALUE, VALUE);
    
#ifdef __cplusplus
}
#endif