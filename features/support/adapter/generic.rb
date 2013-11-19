#
# Copyright (c) 2013, Ingenico Inc.
#
# Permission to use, copy, modify, and/or distribute this software for any purpose with or without fee is hereby granted,
# provided that the above copyright notice and this permission notice appear in all copies.
#                                                                                                                                                                                                          *
# THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES WITH REGARD TO THIS SOFTWARE INCLUDING ALL
# IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY SPECIAL, DIRECT,
# INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER
# IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR
# PERFORMANCE OF THIS SOFTWARE.
#

require 'monitor'

module Adapter

  class Generic
    include MonitorMixin
    include RsLogger

    attr_accessor :event

    def initialize(*args, &block)
      Thread.abort_on_exception = true
      unless instance_variables.include?(:@rxd)
        @rxd = true
      end
      @event = block
      super(*args)
      run
    end

    def reading_allowed?
      @rxd
    end

    def defer_reading
      @rxd = false
      !reading_allowed?
    end

    def allow_reading
      @rxd = true
    end

    def rx(int, blocking = false)
      byte = read(int, blocking)
      if byte
        logger.debug "RX [#{byte.length}]: #{byte.inspect}"
      end
      byte
    end

    def tx(bytes)
      int = write(bytes)
      logger.debug "TX [#{int}]: #{bytes.inspect}"
      int
    end

    def restart_rx_thread
      allow_reading
      run
    end

    def run
      Thread.new do
        loop do
          rx(1, false) if reading_allowed?
          sleep(0.005)
        end
      end
    end

  end

end