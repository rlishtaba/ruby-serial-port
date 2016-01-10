[![Build Status](https://travis-ci.org/rlishtaba/ruby-rs-232.svg?branch=master)](https://travis-ci.org/rlishtaba/ruby-rs-232)

# Ruby Serial Port implementation as C Native Extension. [ RS-232 ]

This is a RS-232 implementation as a Ruby C Native Extension.

## Installation

Add this line to your application's Gemfile:

    gem 'rs_232'

And then execute:

    $ bundle

Or install it yourself as:

    $ gem install rs_232

## Usage

See `examples` folder for details.

```ruby
    class SerialPortAdapter
      include CommPort
    
      attr_reader :interface
      private :interface
    
      # constructor with default params
      # by default port will be configured with:
      #
      #  baud_rate = 115200  # BAUD_115200
      #  data_bits = 8       # DATA_BITS_8
      #  parity = 0          # PAR_NONE
      #  stop_bits = 1       # STOP_BITS_1
      #  flow_control = 0    # FLOW_OFF
      #
      #  see other public constants on CommPort namespace
      #
      def initialize(port, options = {})
        @port = port
        @hardware = {
            baud_rate: options.fetch(:baud_rate) { BAUD_115200 }.to_i,
            data_bits: options.fetch(:data_bits) { DATA_BITS_8 }.to_i,
            parity: options.fetch(:parity) { PAR_NONE }.to_i,
            stop_bits: options.fetch(:stop_bits) { STOP_BITS_1 }.to_i,
            flow_control: options.fetch(:flow_control) { FLOW_OFF }.to_i
        }.freeze
        @timeouts = {
            connecting_timeout: options.fetch(:connecting_timeout) { 15 }.to_i,
            sending_timeout: options.fetch(:sending_timeout) { 5 }.to_i,
            receiving_timeout: options.fetch(:receiving_timeout) { 60 }.to_i
        }.freeze
        @open = false
        @interface = Rs232.new(port)
        connect
      end
    
      def connect
        return if open?
        interface.connecting_timeout = @timeouts[:connecting_timeout] if interface.respond_to?(:connecting_timeout)
        interface.open
        configure_interface @hardware
        @open = open?
      end
    
      def write(bytes)
        interface.write(bytes)
      end
    
      def close
        return unless open?
        flush
        interface.close
        @open = open?
        !open?
      end
    
      def flush
        interface.flush
      end
    
      def open?
        interface && !interface.closed?
      end
    
      def recv(count)
        array = []
        chunk = read_io_until(count, count)
        array.push chunk if chunk
        array.empty? ? nil : array.join
      end
    
      def recv_nonblock(count)
        array = []
        chunks_count = (count == -1) ? interface.available? : count
        chunks_count.times do
          chunk = interface.read(1)
          array.push chunk if chunk
        end
        array.empty? ? nil : array.join
      end
    
      def read(count, blocking = false)
        blocking ? recv(count) : recv_nonblock(count)
      end
    
      private
    
      def configure_interface(options)
        interface.baud_rate = options[:baud_rate]
        interface.data_bits = options[:data_bits]
        interface.parity = options[:parity]
        interface.stop_bits = options[:stop_bits]
        interface.flow_control = options[:flow_control]
      end
    
      def block_io_until(count, up_to)
        up_to -= 1 while interface.available? < count && up_to > 0
        up_to > 0
      end
    
      def read_io_until(count, up_to)
        sleep 0.001 until block_io_until(count, up_to)
        read(count)
      end
    end

```

## Contributing

Bug reports and pull requests are welcome on GitHub at https://github.com/rlishtaba/ruby-rs-232. This project is intended to be a safe, welcoming space for collaboration, and contributors are expected to adhere to the [Contributor Covenant](contributor-covenant.org) code of conduct.

## License

The gem is available as open source under the terms of the [MIT License](http://opensource.org/licenses/MIT).
