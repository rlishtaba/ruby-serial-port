require 'monitor'

module Adapter

  class Generic
    include MonitorMixin

    DEFAULT_NOTIFIER = ->(message) { $stdout.puts message }

    attr_accessor :notifier

    def initialize(*args, &block)
      Thread.abort_on_exception = true
      @rxd                      = true unless instance_variables.include?(:@rxd)
      @notifier                 = block || DEFAULT_NOTIFIER
      super()
      run
    end

    def notifier=(value)
      @notifier = value
    end

    def notifier
      @notifier
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
        notify_with "RX [#{byte.length}]: #{byte.inspect}"
      end
      byte
    end

    def tx(bytes)
      int = write(bytes)
      notify_with "TX [#{int}]: #{bytes.inspect}"
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

    private

    def notify_with(message)
      @notifier[message]
    end

  end

end