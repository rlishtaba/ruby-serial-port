# Rs232

Native implementation of the Rs-232 conneciton type

## Installation

Add this line to your application's Gemfile:

    gem 'ruby-rs-232'

And then execute:

    $ bundle

Or install it yourself as:

    $ gem install ruby-rs-232

## Usage


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
    @interface ||= Rs232.new(port)
  end
    
  #
  # other adapter methods here ...
  # 
  # adapter example placed in the lib folder
  #
   
end  

== Windows

@adapter = Serial.new("COM3") 

== Linux 

@adapter = Serial.new("/dev/tty.usb00000")

== Darwin

@adapter = Serial.new("/dev/ttyACM0")  



## Contributing
