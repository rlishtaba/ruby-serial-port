#
# Copyright (c) 2013, Ingenico Inc.
#
# Permission to use, copy, modify, and/or distribute this software for any purpose with or without fee is hereby granted,
# provided that the above copyright notice and this permission notice appear in all copies.
#                                                                                                                                                                                                          *
# THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES WITH REGARD TO THIS SOFTWARE INCLUDING ALL
# IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY SPECIAL, DIRECT,
# INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER
# IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR
# PERFORMANCE OF THIS SOFTWARE.
#

require 'cucumber'
require 'cucumber/formatter/unicode'
require File.expand_path("../../../lib/rs_232", __FILE__)
require File.expand_path("../adapter", __FILE__)

# # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # #
#
# relative path location method
#
def expand_path(path)
  File.expand_path(path, File.dirname(__FILE__))
end


# # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # #
#
# ENV
#
config = expand_path '../config/config.yml'
if File.file? config
  require 'yaml'
  env = YAML.load File.read config
  env.each do |key, value|
    if ENV['DEBUG'] or env['DEBUG']
      if ENV[key]
        puts "Set `#{key}` to `#{ENV[key]}`."
      else
        puts "Set `#{key}` to default `#{value}`."
      end
    end

    ENV[key] ||= value.to_s if value
  end
else
  if ENV['DEBUG']
    puts "Please check `features/support/config` folder for existing file `config.yml`"
    puts
  end
end

# # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # #
#
# Load only if bundled console
#

unless $0 =~ /cucumber/i
  runtime = Cucumber::Runtime.new
  runtime.load_programming_language('rb')
end


# # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # #
#
# logger impl
#

class LogFormatter < ::Logger::Formatter

  def call(severity, time, progname, msg)
    "#{format_datetime(time)}[TID:#{$$}] [EXT::#{severity}]: #{msg}\n"
  end

  private

  def format_datetime(time)
    time.strftime("%Y-%m-%d %H:%M:%S.") << "%06d " % time.usec
  end

end

def logger
  @logger ||= begin
    l           = ::Logger.new($stdout)
    l.level     = Logger::DEBUG
    l.formatter = LogFormatter.new
    l
  end
end

# - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

def serial_port
  if ENV["SERIAL_PORT"].nil?
    $stdout.write "Enter serial port name: "
    ENV["SERIAL_PORT"] = $stdin.gets.chomp
  end
  ENV["SERIAL_PORT"]
end

# - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

def adapter
  @adapter ||= Adapter::Dev.new(serial_port)
end

# - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

def transmit(string)
  adpter.tx(string)
end
