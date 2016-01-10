require 'monitor'

module Rs232Example
  module Adapter
    class Generic
      include MonitorMixin
      attr_accessor :logger

      def initialize(*_args, &_block)
        Thread.abort_on_exception = true
        @rxd                      = true unless instance_variables.include?(:@rxd)
        super()
        @logger = Rs232Example.logger
        run
      end

      attr_writer :notifier

      attr_reader :notifier

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
        debug "RX [#{byte.length}]: #{byte.inspect}" if byte
        byte
      end

      def tx(bytes)
        int = write(bytes)
        debug "TX [#{int}]: #{bytes.inspect}"
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

      protected

      def debug(message)
        if @logger.respond_to? :debug
          @logger.debug(message)
        else
          $stdout.puts message
        end
      end
    end
  end
end
