[![Build Status](https://travis-ci.org/rlishtaba/ruby-rs-232.svg?branch=master)](https://travis-ci.org/rlishtaba/ruby-rs-232)

# Ruby Serial Port implementation as C Native Extension. [ RS-232 ]

Rubygem offering simple API in order to start using Serial Port communication in your project running on Linux, Mac OS X or Windows.

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
   > include Rs232
   > port = new_serial_port('/dev/tty.ACM0', baud_rate: 9600)
   #=> #<Rs232::Impl @port='/dev/tty.ACM0'>
   > port.open?
   #=> false
   > port.connect # rasing IOError in case of port couldn't be opened.
   #=> #<Rs232::Impl @port='/dev/tty.ACM0'> 
   > port.pending_bytes
   #=> 15
   > port.read(15)
   #=> 'Hello, World!!!'
   > port.write("Hi")
   #=> 2
   > port.close
   #=> true
   > port.open?
   #=> false
```

## Contributing

Bug reports and pull requests are welcome on GitHub at https://github.com/rlishtaba/ruby-rs-232. This project is intended to be a safe, welcoming space for collaboration, and contributors are expected to adhere to the [Contributor Covenant](contributor-covenant.org) code of conduct.

## License

The gem is available as open source under the terms of the [MIT License](http://opensource.org/licenses/MIT).
