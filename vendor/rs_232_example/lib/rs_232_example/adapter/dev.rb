require 'rs_232'

module Rs232Example
  module Adapter
    class Dev < Generic
      attr_reader :interface
      # == Top level module ::CommPort constants
      #
      # :VERSION,
      #
      # :BAUD_110,
      # :BAUD_300,
      # :BAUD_600,
      # :BAUD_1200,
      # :BAUD_2400,
      # :BAUD_4800,
      # :BAUD_9600,
      # :BAUD_19200,
      # :BAUD_38400,
      # :BAUD_57600,
      # :BAUD_115200,
      #
      # :DATA_BITS_5,
      # :DATA_BITS_6,
      # :DATA_BITS_7,
      # :DATA_BITS_8,
      #
      # :PAR_NONE,
      # :PAR_ODD,
      # :PAR_EVEN,
      #
      # :STOP_BITS_1,
      # :STOP_BITS_3,
      #
      # :FLOW_OFF,
      # :FLOW_HARDWARE,
      # :FLOW_XONXOFF,
      #
      # :Impl
      #


      # == constructor with default params
      #
      def initialize(port, &block)
        @interface = CommPort::Rs232.new(port)
        super
        connect
      end

      # Open and configure interface
      #
      # @return [Bool]
      #
      def connect
        @interface.open

        notify_with '%s has been received call to %s...' % [self, __method__]

        @interface.baud_rate    = CommPort::BAUD_115200
        @interface.data_bits    = CommPort::DATA_BITS_8
        @interface.parity       = CommPort::PAR_NONE
        @interface.stop_bits    = CommPort::STOP_BITS_1
        @interface.flow_control = CommPort::FLOW_OFF

        @open = open?
      end

      # == Write function implementation
      #
      # @param [String] bytes
      # @return [Int]
      #
      def write(bytes)
        @interface.write(bytes)
      end

      # == Closing interface and freeing structures
      #
      #  @return  [Bool]
      #
      def close
        debug '%s has been received call to %s...' % [self, __method__]

        @interface.close
        @open = open?
        !open?
      end

      # == Flashing buffer function
      #
      def flush
        debug '%s has been received call to %s...' % [self, __method__]

        @interface.flush
      end

      # @return [Bool]
      #
      def open?
        @interface && !@interface.closed?
      end

      # == read() implementation example
      #
      # @param +count+ [Int]
      # @param +blocking+ [Bool]
      #
      # @return [String]
      #
      # === Alternative implementation:
      # @usage:
      #
      #  +timeout+ = blocking_value ? 15000 : 0
      #  +@interface.timeout+ = +timeout+
      #  +@interface.read( +count+ )+
      #
      def read(count, blocking = false)
        array = []

        bytes_count = (count == -1) ? @interface.available? : count

        if blocking
          bytes = read_io_until(count, count)
          array.push bytes if bytes
        else
          bytes_count.times do
            byte = @interface.read(1)
            array.push byte if byte
          end
        end
        array.empty? ? nil : array.join
      end

      private

      # == simulate blocking function
      #
      # @param +count+ [Int]
      # @param +up_to+ [Int]
      #
      # no direct ruby usage
      #
      def block_io_until(count, up_to)
        while @interface.available? < count && up_to > 0
          up_to -= 1
        end
        up_to > 0
      end

      # == simulate blocking function
      #
      # @param +count+ [Int]
      # @param +up_to+ [Int]
      #
      # no direct ruby usage
      #
      def read_io_until(count, up_to)
        until block_io_until(count, up_to)
          sleep 0.001
        end
        read(count)
      end

    end
  end
end