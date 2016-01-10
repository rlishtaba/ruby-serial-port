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
        @options = options
        @open = false
        @interface = Rs232.new(port)
        connect
      end
    
      def connect
        return if open?
        can_configure_timeout = interface.respond_to?(:connecting_timeout)
        interface.connecting_timeout = @options.fetch(:connecting_timeout, 60) if can_configure_timeout
        interface.open
        configure_interface!
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
    
      def configure_interface!
        interface.baud_rate = @options.fetch(:baud_rate, BAUD_115200).to_i
        interface.data_bits = @options.fetch(:data_bits, DATA_BITS_8).to_i
        interface.parity = @options.fetch(:parity, PAR_NONE).to_i
        interface.stop_bits = @options.fetch(:stop_bits, STOP_BITS_1).to_i
        interface.flow_control = @options.fetch(:flow_control, FLOW_OFF).to_i
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
