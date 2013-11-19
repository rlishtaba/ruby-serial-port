#
#Copyright (c) 2013, Ingenico Inc.
#
#Permission to use, copy, modify, and/or distribute this software for any purpose with or without fee is hereby granted,
#provided that the above copyright notice and this permission notice appear in all copies.
#                                                                                                                                                                                                          *
#THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES WITH REGARD TO THIS SOFTWARE INCLUDING ALL
#IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY SPECIAL, DIRECT,
#INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER
#IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR
#PERFORMANCE OF THIS SOFTWARE.
#

require "rs_232/version"
require "rs_232.so"

#== Adapter implementation example, no event only read on-demand:
#
#  @usage:
#
#  instantiate adapter
#  +adapter+ = +Serial.new("COM3")+ #=> [Object]
#
#  write string
#  +adapter.tx("Hello, World\n")+ #=> 13
#
#  read all available bytes
#  +adapter.rx(-1)+ #=> "Bye bye cruel world\n"
#
#
class Serial
  attr_reader :interface
  include CommPort

  # == constructor with default params
  #  by default port will be configured with:
  #
  #  @baud_rate = 115200  # BAUD_115200
  #  @data_bits = 8       # DATA_BITS_8
  #  @parity = 0          # PAR_NONE
  #  @stop_bits = 1       # STOP_1
  #  @flow_control = 0    # FLOW_OFF
  #
  #
  def initialize(port)
    @interface = Rs232.new(port)
    connect
    $stdout.puts "*** Rs232 instance has been initialized. Build v#{CommPort::VERSION}"
  end

  # Open and configure interface
  #
  # @return [Bool]
  #
  def connect
    @interface.open
    # custom configuration should be there if required
    # @interface.baud_rate    = BAUD_115200
    # @interface.data_bits    = DATA_BITS_8
    # @interface.parity       = PAR_NONE
    # @interface.stop_bits    = STOP_1
    # @interface.flow_control = FLOW_OFF
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
    @interface.close
    @open = open?
    !open?
  end

  # == Flashing buffer function
  #
  def flush
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
    array       = []
    
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