require 'rs_232/version'
require 'rs_232_native.so'
require 'forwardable'

module Rs232
  # public accessible factory method
  #
  # @example
  #
  #   > port = Rs232.new('/dev/tty.ACM0', baud_rate: 9600)
  #   #=> <#Rs232::Impl @port='/dev/tty.ACM0'>
  #   > port.open?
  #   #=> false
  #   > port.connect
  #   #=> <#Rs232::Impl @port='/dev/tty.ACM0'>
  #   port.pending_bytes
  #   #=> 15
  #   port.read(15)
  #   #=> 'Hello, World!!!'
  #
  def new_serial_port(port, opts = {}, &block)
    Impl.new(port, opts, &block)
  end

  # the following class represents ruby public interface
  # to native Rs232 implementation
  #
  # There no public instantiation, can be instantiate through
  # the factory method @see Rs232.new
  #
  class Impl
    include Rs232::Constants

    STD_OPTS = {
        baud_rate: BAUD_115200,
        parity: PAR_NONE,
        data_bits: DATA_BITS_8,
        stop_bits: STOP_BITS_1,
        flow_control: FLOW_OFF,
        timeout: 10
    }.freeze

    extend Forwardable

    def_delegators :@impl,
                   :read,
                   :write,
                   :flush,
                   :close,
                   :open?,
                   :set_rts,
                   :set_dtr

    def initialize(name, opts = {})
      @impl = Rs232::Native.new(name)
      @opts = STD_OPTS.merge(opts).freeze
      freeze
      yield self if block_given?
    end

    # @raise RuntimeError in case of open error
    def connect
      return self if open?
      @impl.open.tap do |io|
        io.baud_rate = @opts[:baud_rate]
        io.parity = @opts[:parity]
        io.data_bits = @opts[:data_bits]
        io.stop_bits = @opts[:stop_bits]
        io.flow_control = @opts[:flow_control]
        io.timeout = @opts[:timeout]
      end
      self
    end

    def settings
      {}.tap { |o|
        o[:baud_rate] = @impl.baud_rate
        o[:parity] = @impl.parity
        o[:data_bits] = @impl.data_bits
        o[:stop_bits] = @impl.stop_bits
        o[:flow_control] = @impl.flow_control
        o[:timeout] = @impl.timeout
        o[:line_status] = @impl.line_status
      }.freeze
    end

    def open?
      @impl.open?
    end

    def close
      return !open unless open?
      0 == @impl.close
    end
  end

  private_constant :Impl
end
