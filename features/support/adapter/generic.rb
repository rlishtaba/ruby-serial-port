require 'monitor'

module Adapter

  class Generic
    include MonitorMixin
    include Interface
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
    end

    def allow_reading
      @rxd = true
    end

    def rx(int, blocking = false)
      byte = read(int, blocking)
      if byte
        logger.debug "RX [#{byte.length}][#{@in.object_id}]: #{byte.inspect}"
      end
      byte
    end

    def tx(bytes)
      int = write(bytes)
      logger.debug "TX [#{int}][#{@out.object_id}]: #{bytes.inspect}"
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